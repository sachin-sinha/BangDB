/*
 * common.h
 *
 *      Author: sachin sinha
 */
#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

#include "include/BangDBDatabase.h"
#include "include/BangDBUtils.h"
#include "include/BangDBCommon.h"

#define MAX_INDEX_TEST 2147483647
#define FIXED_NUM_KEYS 5
#define FIXED_NUM_VALS 4

#define INPUT_KEY 	"my key"
#define INPUT_VAL 	"test val"

char *INPUT_KEY_TEST[]	=	{ (char*)"article_key_", (char*)"Item_num_", (char*)"userid-", (char*)"sku_rack_num_", (char*)"purchase_ref" };

char *INPUT_VAL_TEST[] =	{	(char*)"All our knowledge has its origins in our perceptions",

								(char*)"For once you have tasted flight you will walk the earth with your eyes turned skywards, for there you have been and there you will long to return.",

								(char*)"I have offended God and mankind because my work didn't reach the quality it should have.",

								(char*)"The young specialist in English Lit, ...lectured me severely on the fact that in every century people have thought they understood the Universe , \
								at last and in every century they were proved to be wrong. It follows that the one thing we can say about our modern 'knowledge' is that it is wrong.\
								... My answer to him was, ... when people thought the Earth was flat, they were wrong. When people thought the Earth was spherical they were wrong.\
								But if you think that thinking the Earth is spherical is just as wrong as thinking the Earth is flat, then your view is wronger than both \
								of them put together."
							};

using namespace std;
using namespace BangDB_Client;

int my_rand(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

unsigned int _seqgen(unsigned int id)
{
	return id;
}

unsigned int _randomgen(unsigned int id)
{
	id += ~(id<<15);
	id ^=  (id>>10);
	id +=  (id<<3);
	id ^=  (id>>6);
	id += ~(id<<11);
	id ^=  (id>>16);

    return id%MAX_INDEX_TEST;
}
unsigned int _semirandomgen(unsigned int id)
{
	static int num_key_count = 10;
	static unsigned int num[10];
	if(num_key_count == 10)
	{
		int i = 10;
		for(; i>7; i--)
		{
			num[10-i] = _seqgen(id++);
		}
		for(; i>0; i--)
		{
			num[10-i] = _randomgen(id++);
		}
		num_key_count = i;
	}
	return num[++num_key_count];
}
unsigned int _hash(unsigned int id)
{
	return _seqgen(id);
	//return _semirandomgen(id);
	//return _randomgen(id);
}

char *getkey(unsigned int i)
{
	//return _randomgen(i);
	return Itoa(i);
}

char *getval(unsigned int i)
{
	char *ai = Itoa(i);
	char *v = Strncat((char*)INPUT_VAL, ai);
	delete[] ai;
	return v;
}

char *getdoc(unsigned int i)
{
	string x(INPUT_VAL_TEST[i%3]);
	string s = "{\"name\":\"sachin sinha\", \"val\":\"" + x + "\"}";
	return Strncpy(s.c_str());
}

char *getcomplexkey(unsigned int i)
{
	char *ai = Itoa(_hash(i));
	char *key = Strncat(ai, INPUT_KEY_TEST[i%FIXED_NUM_KEYS]);
	delete[] ai;
	return key;
}
char *getcomplexval(unsigned int i)
{
	char *ai = Itoa(i);
	char *val = Strncat(INPUT_VAL_TEST[i%FIXED_NUM_VALS], ai);
	delete[] ai;
	return val;
}

struct threadarg
{
	void *tbl;
	int nstart;
	int nend;
	int factor;
	int ncomplete;
};
#define MAX_TEST_THREADS 128
threadarg targs[MAX_TEST_THREADS];

void init_threadargs()
{
	for(int i = 0; i<MAX_TEST_THREADS; i++)
	{
		targs[i].tbl = NULL;
		targs[i].nstart = targs[i].nend = targs[i].factor = targs[i].ncomplete = 0;
	}
}

int progress_report(threadarg *targs, int dim);
int delay = 5;
void* progress_update(void *arg)
{
	int num_threads = *(long*)arg;
	while(progress_report(targs, num_threads) != 0)
		usleep(delay*1000000);	
	return (void*)0;	
}

int progress_report(threadarg *targs, int dim)
{
	static int count = 0;
	long nprogress, ntotal;
	double npercentage;
	nprogress = ntotal = npercentage = 0;
	for(int i = 0; i<dim; i++)
	{
		nprogress += targs[i].ncomplete;
		ntotal += (targs[i].nend - targs[i].nstart);
	}
	if(ntotal >0l)
	{
		npercentage = ((double)nprogress*100)/(double)ntotal;
		if(npercentage < 100)
		{
			printf("%d\t%f\n", count, npercentage);
			count = count + delay;
			//fflush(stdout);
			return 1;
		}
		else
		{
			printf("\rDone!\n");
			return 0;
		}
	}
	return 1;
}

#endif /* COMMON_H_ */
