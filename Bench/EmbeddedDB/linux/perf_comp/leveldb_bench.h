/*
 * leveldb_bench.h
 *
 *  Created on: Oct 8, 2012
 *      Author: sachin
 */
#ifndef LEVELDB_BENCH_H_
#define LEVELDB_BENCH_H_

#include "common.h"
#include "ext/leveldb/include/c.h"

#define LEVELDB_CACHE_SIZE 1024*1024*1024	//in bytes
#define LEVELDB_BUFFER_SIZE 1024*1024*1024       //in bytes

const char* phase = "";
static void CmpDestroy(void* arg) { }

static int CmpCompare(void* arg, const char* a, size_t alen,
                      const char* b, size_t blen) {
  int n = (alen < blen) ? alen : blen;
  int r = memcmp(a, b, n);
  if (r == 0) {
    if (alen < blen) r = -1;
    else if (alen > blen) r = +1;
  }
  return r;
}

static const char* CmpName(void* arg) {
  return "foo";
}

#define CheckCondition(cond)                                            \
  if (!(cond)) {                                                        \
    fprintf(stderr, "%s:%d: %s: %s\n", __FILE__, __LINE__, phase, err); \
    abort();                                                            \
  }

static void Free(char** ptr) {
  if (*ptr) {
    free(*ptr);
    *ptr = NULL;
  }
}

leveldb_t* db;
leveldb_comparator_t* cmp;
leveldb_cache_t* cache;
leveldb_env_t* env;
leveldb_options_t* options;
leveldb_readoptions_t* roptions;
leveldb_writeoptions_t* woptions;

int ldb_put(threadarg *ta)
{
	char *key, *val;
	bool successflag = true;
	int val_len, s = ta->nstart, n = ta->nend;

	for(int i = s; i<n; i ++)
	{
		key = getkey(i);
		val = getval(i);
#ifndef LARGE_VALUE_TEST
		val_len = strlen(val);
#else
		val_len = LARGE_BUF_LEN;
#endif

		char * err = NULL;
		leveldb_put(db, woptions, (const char*) key, strlen(key), (const char*)val, val_len, &err);
		if (err != NULL)
		{
		  successflag = false;
		}
		delete[] key;
#ifndef LARGE_VALUE_TEST
		delete[] val;
#endif
		ta->ncomplete++;
	}

	if(successflag)
		return 0;
	return -1;
}

int ldb_get(threadarg *ta)
{
	char *key, *val;
	int val_len, retval = 0, s = ta->nstart, n = ta->nend;

	bool successflag = true;

	for(int i = s; i < n; i++)
	{
		key = getkey(i);
		val = getval(i);
#ifndef LARGE_VALUE_TEST
		val_len = strlen(val);
#else
		val_len = LARGE_BUF_LEN;
#endif
		char * err = NULL;
		char *result;
		size_t sz;
		result = leveldb_get(db, roptions, (const char *) key, strlen(key), &sz, &err);
		if(!result)
			successflag = false;
		else if(memcmp(result,val, val_len) != 0)
			retval = 1;

		free(result);
		delete[] key;
#ifndef LARGE_VALUE_TEST
		delete[] val;
#endif
		ta->ncomplete++;
	}

	if(successflag)
		return retval;
	return -1;
}

int ldb_getput(threadarg *ta)
{
	int x, y, w = 0, r = 0, val_len, no_write = 0, no_read = 0, s = ta->nstart, n = ta->nend, factor = ta->factor;
	int base_write = s + ((factor-1)*(n-s))/factor;int retval = 0;
	printf("the s=%d and n = %d and base_write = %d\n", s, n, base_write);

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
#ifndef LARGE_VALUE_TEST
			val_len = strlen(val);
#else
			val_len = LARGE_BUF_LEN;
#endif

			char * err = NULL;
			leveldb_put(db, woptions, (const char*) key, strlen(key), (const char*)val, val_len, &err);
			if (err != NULL)
			{
				no_write++;
			 	successflag = false;
			}
			delete[] key;
#ifndef LARGE_VALUE_TEST
			delete[] val;
#endif
			ta->ncomplete++;
		}
		else
		{
			//read
			r++;
			y = my_rand(s, base_write);
			key = getkey(y);
			val = getval(y);
#ifndef LARGE_VALUE_TEST
			val_len = strlen(val);
#else
			val_len = LARGE_BUF_LEN;
#endif
			char * err = NULL;
			char *result;
			size_t sz;
			result = leveldb_get(db, roptions, (const char *) key, strlen(key), &sz, &err);
			if(!result)
			{
				no_read++;
				successflag = false;
			}
			else if(memcmp(result,val, val_len) != 0)
				retval = 1;

			free(result);
			delete[] key;
#ifndef LARGE_VALUE_TEST
			delete[] val;
#endif
			ta->ncomplete++;
		}
	}
	printf("Write = %d and Read = %d | noWrite = %d and noRead = %d\n", w, r, no_write, no_read);
	if(successflag)
		return retval;
	return -1;
}


void *ldb_threadfuncput(void *arg)
{
	threadarg* ta = (threadarg*)arg;
	off_t retval = ldb_put(ta);
	return (void*)retval;
}
void *ldb_threadfuncget(void *arg)
{
	threadarg* ta = (threadarg*)arg;
	off_t retval = ldb_get(ta);
	return (void*)retval;
}

void *ldb_threadfunc_getput(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = ldb_getput(ta);
	return (void*)retval;
}
int ldb_bench_getput(int num_threads, int num_items, int factor)
{
	printf("[%d percent write and %d percent read performance test for LevelDB] by inserting %d items using %d threads\n",100/factor, (100*factor-100)/factor,  num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	time_eval te;long retval = 0;
	int s = 0, ret;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	//first insert some items based on factor for better read by threads
	for(int i = 0; i<num_threads; i++)
	{
		int nitems = ((num_items/num_threads)*(factor-1))/factor;
		printf("writing from %d upto %d for nitems = %d\n", s, s+nitems, nitems);
		targs[i].nstart = s, targs[i].nend = s+nitems, targs[i].ncomplete = 0;
		if((ret = ldb_put(&targs[i])) < 0)
			successflag = false;
		s += (num_items/num_threads);
	}

	//background thread for counting
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}

	s = 0;
	te.start_counting();

	for(int i = 0; i<num_threads; i++)
	{
		threadarg *targ = new threadarg;
		targs[i].tbl = NULL;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = factor;

		if(pthread_create(&thrds[i], &attr, ldb_threadfunc_getput, (void*)targ) != 0)
		{
			printf("error in creating thread in LevelDB getput, qutting");
			exit(-1);
		}
		s += (num_items/num_threads);
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in LevelDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for writing 20 percent and reading 80 percent of %d items by %d threads for LevelDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

int ldb_bench_put(int num_threads, int num_items)
{
	printf("[PUT- performance test for LevelDB] by inserting %d items using %d threads\n", num_items, num_threads);
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
		targs[i].tbl = NULL;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		
		if(pthread_create(&thrds[i], &attr, ldb_threadfuncput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in LevelDB PUT, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in LevelDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for inserting %d items by %d threads for LevelDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}
int ldb_bench_get(int num_threads, int num_items)
{
	printf("[GET- performance test for LevelDB] by retrieving %d items using %d threads\n", num_items, num_threads);
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

	//create threads and run for conn
	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = NULL;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		if(pthread_create(&thrds[i], &attr, ldb_threadfuncget, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in LevelDB GET, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in LevelDB GET");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for getting %d items by %d threads for LevelDB  is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

 void leveldb_bench(int num_threads, int num_items, char *ops, int factor)
 {
    char* dbname = (char*)"leveldb_test";
    char* err = NULL;
    int retval = 0;

    cmp = leveldb_comparator_create(NULL, CmpDestroy, CmpCompare, CmpName);
    env = leveldb_create_default_env();

    cache = leveldb_cache_create_lru(LEVELDB_CACHE_SIZE);

    options = leveldb_options_create();
    leveldb_options_set_comparator(options, cmp);
    leveldb_options_set_error_if_exists(options, 0);
    leveldb_options_set_cache(options, cache);
    leveldb_options_set_env(options, env);
    leveldb_options_set_info_log(options, NULL);
    leveldb_options_set_write_buffer_size(options, LEVELDB_BUFFER_SIZE);
    leveldb_options_set_paranoid_checks(options, 0);
    leveldb_options_set_max_open_files(options, 200);
    leveldb_options_set_block_size(options, 8192);
    leveldb_options_set_block_restart_interval(options, 8);
    leveldb_options_set_compression(options, (0)?leveldb_snappy_compression:leveldb_no_compression);
    roptions = leveldb_readoptions_create();
    leveldb_readoptions_set_verify_checksums(roptions, 0);
    leveldb_readoptions_set_fill_cache(roptions, 0);

    woptions = leveldb_writeoptions_create();
    leveldb_writeoptions_set_sync(woptions, 0);

    leveldb_options_set_create_if_missing(options, 1);
    db = leveldb_open(options, dbname, &err);
    CheckCondition(err == NULL);
    Free(&err);

    printf("db %p\n", db);


    if(strncmp(ops, "put", 3) == 0)
    {
    	if((retval = ldb_bench_put(num_threads, num_items)) < 0)
    		printf("Error in running the LevelDB bench for PUT\n");
    }
    else if(strncmp(ops, "get", 3) == 0)
    {
    	if((retval = ldb_bench_get(num_threads, num_items)) < 0)
    		printf("Error in running the LevelDB bench for GET\n");
    }
    else if(strncmp(ops, "all", 3) == 0)
    {
	if((retval = ldb_bench_put(num_threads, num_items)) < 0)
    		printf("Error in running the LevelDB bench for PUT\n");
    	if((retval = ldb_bench_get(num_threads*sysconf( _SC_NPROCESSORS_ONLN ), num_items)) < 0)
    		printf("Error in running the LevelDB bench for GET\n");
    }
	else if(strncmp(ops, "overlap", 7) == 0)
	{
		if((retval = ldb_bench_getput(num_threads, num_items, factor)) < 0)
			printf("Error in running the LevelDB bench for overlap read and write\n");
	}
    else
    	printf("Error in specifying the opertion type(put/get/all/overlap) for LevelDB bench\n");

    printf("ldb db close \n");
    printf("db %p\n", db);
    leveldb_close(db);
    leveldb_options_destroy(options);
    leveldb_readoptions_destroy(roptions);
    leveldb_writeoptions_destroy(woptions);
    leveldb_cache_destroy(cache);
    leveldb_comparator_destroy(cmp);
    leveldb_env_destroy(env);

	if(retval != -1)
	{
		printf("The LevelDB bench test was successful\n");
		if(retval == 1)
			printf("There were expected or unexptected mismatches in the retrieved values\n");
	}
	else
		printf("There were errors in LevelDB bench test\n");
}

#endif /* LEVELDB_BENCH_H_ */
