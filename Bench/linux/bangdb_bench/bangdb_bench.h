/*
 * bangdb_bench.h
 *
 *      Author: sachin
 */

#ifndef BANGDB_BENCH_H_
#define BANGDB_BENCH_H_

#include "common.h"
#include "include/database.h"

/* for server comment above include and un comment the following */
//#include <bangdb-client/database.h>

using namespace bangdb;

int bangdb_get(threadarg *ta)
{
	table *tbl = (table*)ta->tbl;
	connection *conn = tbl->getconnection();
	if(!conn)
	{
		printf("connection null error, please change the max conn config in bangdb.config, it could be the reason\n");
		return -1;
	}
	int s = ta->nstart, n = ta->nend, val_len, retval = 0;
	FDT ikey, *ival = NULL;
	char *key, *val;
	int count = 0, mismatch = 0;

	bool successflag = true;
	for(int i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);
		val_len = strlen(val);

		ikey.data = key;
		ikey.length = strlen(key);

		if((ival = conn->get(&ikey)) == NULL)
		{
			//printf("null retrieved for i=%d \n",i);
			count++;
			successflag = false;
		}
		else if(memcmp(ival->data, val, val_len) != 0)
		{
			//printf("mismatch\n");
			retval = 1;
			mismatch++;
		}
		
		if(ival)
			ival->free();
		delete ival;
		delete[] key;
		delete[] val;

		ta->ncomplete++;
	}

	conn->closeconnection();
	delete conn;

	if(count > 0)
		printf("could not read %d keys\n", count);
	if(mismatch > 0)
		printf("mismatch in read for %d keys\n", mismatch);

	if(successflag)
		return retval;
	
	return -1;
}

int bangdb_put(threadarg *ta)
{
	table *tbl = (table*)ta->tbl;
	connection *conn = tbl->getconnection();
	if(!conn)
	{
		printf("connection null error, please change the max conn config in bangdb.config, it could be the reason\n");
		return -1;
	}
	int s = ta->nstart, n = ta->nend;
	FDT ikey, ival;
	char *key, *val;

	bool successflag = true;
	int count = 0;

	for(int i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);

		ikey.data = key;
		ikey.length = strlen(key);
		ival.data = val;
		ival.length = strlen(val);
		
		if(conn->put(&ikey, &ival, INSERT_UNIQUE) < 0)
		{
			successflag = false;
			count++;
		}
		
		delete[] key;
		delete[] val;

		ta->ncomplete++;
	}

	conn->closeconnection();
	delete conn;

	if(count > 0)
		printf("could not insert %d keys\n", count);

	if(successflag)
		return 0;
	return -1;
}
/* un comment for server if wanna run simple call else leave it */
int bangdb_simple(threadarg *ta)
{
	table *tbl = (table*)ta->tbl;
	connection *conn = tbl->getconnection();
	if(!conn)
	{
		printf("connection null error, please change the max conn config in bangdb.config, it could be the reason\n");
		return -1;
	}
	int s = ta->nstart, n = ta->nend;

	bool successflag = true;
	int count = 0;

	for(int i = s; i<n; i++)
	{
		/*	
		if(conn->make_simple_call() < 0)
		{
			successflag = false;
			count++;
		}
		*/
		ta->ncomplete++;
	}

	conn->closeconnection();
	delete conn;

	if(count > 0)
		printf("could not make simple calls for %d keys\n", count);

	if(successflag)
		return 0;
	return -1;
}

int bangdb_getput(threadarg *ta)
{
	table *tbl = (table*)ta->tbl;
	connection *conn = tbl->getconnection();
	if(!conn)
	{
		printf("connection null error, please change the max conn config in bangdb.config, it could be the reason\n");
		return -1;
	}
	int s = ta->nstart, n = ta->nend, factor = ta->factor, x, y, w = 0, r = 0, val_len, no_write = 0, no_read = 0, ret, retval = 0;
	int base_write = s + ((factor-1)*(n-s))/factor;

	FDT ikey, ival, *out;
	char *key, *val;
	bool successflag = true;

	for(int i = s; i<n; i++)
	{
		x = my_rand(1, factor);
		if(x == factor)
		{
			//write
			w++;
			y = my_rand(base_write, n);
			key = getkey(y);
			val = getval(y);
			val_len = strlen(val);

			ikey.data = key;
			ikey.length = strlen(key);
			ival.data = (void*)val;
			ival.length = val_len;

			if((ret=conn->put(&ikey, &ival, INSERT_UPDATE)) < 0)
			{
				successflag = false;
			}
			if(ret == 1)
				no_write++;
			delete[] key;
			delete[] val;

		}
		else
		{
			//read
			r++;
			y = my_rand(s, base_write);
			key = getkey(y);
			val = getval(y);
			val_len = strlen(val);

			ikey.data = key;
			ikey.length = strlen(key);

			if((out = conn->get(&ikey)) == NULL)
			{
				no_read++;
			}
			else if(memcmp(out->data, val, val_len) != 0)
			{
				//printf("mismatch\n");
				retval = 1;
			}

			if(out)
				out->free();
			delete out;
			delete[] key;
			delete[] val;

		}
		ta->ncomplete++;
	}

	conn->closeconnection();
	delete conn;

	printf("Write = %d and Read = %d | noWrite = %d and noRead = %d\n", w, r, no_write, no_read);
	if(successflag)
		return retval;
	return -1;
}

void *bangdb_threadfuncput(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bangdb_put(ta);
	return (void*)retval;
}

void *bangdb_threadfunc_simple(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bangdb_simple(ta);
	return (void*)retval;
}

void *bangdb_threadfuncget(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bangdb_get(ta);
	return (void*)retval;
}

void *bangdb_threadfunc_getput(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bangdb_getput(ta);
	return (void*)retval;
}

int bangdb_bench_getput(table *tbl, int num_threads, int num_items, int factor)
{
	printf("[%d percent write and %d percent read performance test for BangDB] by inserting %d items using %d threads\n", 100/factor, (100*factor-100)/factor, num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	time_eval te;
	int s = 0, ret;long retval = 0;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	//first insert some items based on factor for better read by threads
	for(int i = 0; i<num_threads; i++)
	{
		int nitems = ((num_items/num_threads)*(factor-1))/factor;
		printf("writing from %d upto %d for nitems = %d\n", s, s+nitems, nitems);
		
		threadarg temp_ta; 
		temp_ta.tbl = (void*)tbl; temp_ta.nstart = s; temp_ta.nend = s+nitems; temp_ta.ncomplete = 0;
		if((ret = bangdb_put(&temp_ta)) < 0)
			successflag = false;
		s += (num_items/num_threads);
	}

	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}

	s = 0;
	te.start_counting();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = factor;
		targs[i].ncomplete = 0;

		if(pthread_create(&thrds[i], &attr, bangdb_threadfunc_getput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BangDB getput, qutting");
			exit(-1);
		}
		s += (num_items/num_threads);
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BangDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for writing and reading of %d items by %d threads for BangDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

int bangdb_bench_simple(table *tbl, int num_threads, int num_items)
{
	printf("[SIMPLE CALL- performance test for BangDB] by inserting %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0;
	time_eval te;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//background thread for counting
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}	

	te.start_counting();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;		

		if(pthread_create(&thrds[i], &attr, bangdb_threadfunc_simple, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BangDB SIMPLE CALL, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{	
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BangDB SIMPLE CALL");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for making simple call %d items by %d threads for BangDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining the background progress update thread");

	if(successflag)
		return (int)retval;
	return -1;
}

int bangdb_bench_put(table *tbl, int num_threads, int num_items)
{
	printf("[PUT- performance test for BangDB] by inserting %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0;
	time_eval te;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//background thread for counting
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}	

	te.start_counting();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;		

		if(pthread_create(&thrds[i], &attr, bangdb_threadfuncput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BangDB PUT, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{	
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BangDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for inserting %d items by %d threads for BangDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining the background progress update thread");

	if(successflag)
		return (int)retval;
	return -1;
}

int bangdb_bench_get(table *tbl, int num_threads, int num_items)
{
	printf("[GET- performance test for BangdDB] by retrieving %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0;
	time_eval te;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	//start background thread for progress update
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}

	te.start_counting();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;		

		if(pthread_create(&thrds[i], &attr, bangdb_threadfuncget, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BangDB GET, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BangDB GET");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for getting %d items by %d threads for BangDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

void bangdb_bench(int num_threads, int num_items, char *ops, int factor)
{
	int retval = 0;
	database *db;
	table *tbl;

	//create database, table and connection
	db = new database((char*)"mydb");

	if((tbl = db->gettable((char*)"mytable", OPENCREATE)) == NULL)
	{
		printf("table NULL error, quitting");
		exit(-1);
	}

	if(strncmp(ops, "put", 3) == 0)
	{
		if((retval = bangdb_bench_put(tbl, num_threads, num_items)) < 0)
			printf("Error in running the BangDB bench for PUT\n");
	}
	else if(strncmp(ops, "get", 3) == 0)
	{
		if((retval = bangdb_bench_get(tbl, num_threads, num_items)) < 0)
			printf("Error in running the BangDB bench for GET\n");
	}
	else if(strncmp(ops, "all", 3) == 0)
	{
		if((retval = bangdb_bench_put(tbl, num_threads, num_items)) < 0)
			printf("Error in running the BangDB bench for PUT\n");
		if((retval = bangdb_bench_get(tbl, num_threads, num_items)) < 0)
			printf("Error in running the BangDB bench for GET\n");
	}
	else if(strncmp(ops, "overlap", 7) == 0)
	{
		if((retval = bangdb_bench_getput(tbl, num_threads, num_items, factor)) < 0)
			printf("Error in running the BangDB bench for overlap read and write\n");
	}
	/* only for client server case, where user can check the simple perf for just sending and reciveing 
	  * simple static msgs 
	*/
	else if(strncmp(ops, "simple", 6) == 0)
	{
		if((retval == bangdb_bench_simple(tbl, num_threads, num_items)) < 0)
			printf("Error in running the BangDB bench for simple calls\n");
	}
	else
		printf("Error in specifying the opertion type(put/get/all/overlap) for BangDB bench\n");

	tbl->closetable();
	delete tbl;
	db->closedatabase();
	delete db;

	if(retval != -1)
	{
		printf("The BangDB bench test was successful\n");
		if(retval == 1)
			printf("There were expected or unexptected mismatches in the retrieved values\n");
	}
	else
		printf("There were errors in BangDB bench test\n");
}

#endif /* BANGDB_BENCH_H_ */
