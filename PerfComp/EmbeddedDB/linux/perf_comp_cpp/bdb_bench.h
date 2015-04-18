/*
 * bdb_bench.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sachin
 */

#ifndef BDB_BENCH_H_
#define BDB_BENCH_H_
#include "common.h"
#include "ext/bdb/include/db.h"

#define BDB_BUFFER_SIZE_BYTES 1500*1024*1024	//in bytes
#define BDB_BUFFER_SIZE_GB 0
#define BDB_LOG_FILE_SIZE 256*1024*1024

#ifdef _TXN_TEST_
#define TXN_FLAGS	(DB_INIT_LOCK | DB_INIT_LOG | DB_INIT_TXN | DB_INIT_MPOOL | DB_CREATE | DB_THREAD | DB_PRIVATE)
#define OPEN_FLAGS (DB_CREATE | DB_THREAD | DB_AUTO_COMMIT);
#else
#define TXN_FLAGS	(DB_INIT_LOCK | DB_INIT_MPOOL | DB_CREATE | DB_THREAD | DB_PRIVATE)
#define OPEN_FLAGS (DB_CREATE | DB_THREAD);
#endif

DB_ENV *envp;
DB *dbp;
u_int32_t flags,env_flags;
DBTYPE type;

int bdb_put(threadarg *ta)
{
	DB_TXN *txn;
	DBT dkey, ddata;
	char *key, *val;
	int val_len, s = ta->nstart, n = ta->nend;

	bool successflag = true;

	for(int i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);
		val_len = strlen(val);

		memset(&dkey, 0, sizeof (DBT));
		memset(&ddata, 0, sizeof (DBT));
		dkey.data = key;
		dkey.size = strlen(key);
		ddata.data = (void*)val;
		ddata.size = val_len;
		txn = NULL;
#ifdef _TXN_TEST_
		envp->txn_begin(envp, NULL, &txn, 0);
#endif

		if(dbp->put(dbp, txn, &dkey, &ddata, DB_NOOVERWRITE) < 0)
			successflag = false;

#ifdef _TXN_TEST_
		txn->commit(txn, 0);
#endif

		delete[] key;
		delete[] val;
		ta->ncomplete++;
	}

	if(successflag)
		return 0;
	return -1;
}

int bdb_get(threadarg *ta)
{
	DB_TXN *txn;
	DBT dkey, ddata;

	char data[128];
	int dat_len = 128;
	char *key, *val;
	int val_len, retval = 0, s = ta->nstart, n = ta->nend;

	bool successflag = true;

	for(int i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);

		val_len = strlen(val);

		memset(&dkey, 0, sizeof (DBT));
		memset(&ddata, 0, sizeof (DBT));

		dkey.data = key;
		dkey.size = strlen(key);
		ddata.data = data;
		ddata.ulen = dat_len;
		ddata.flags = DB_DBT_USERMEM;
		txn = NULL;
#ifdef _TXN_TEST_
		envp->txn_begin(envp, NULL, &txn, 0);
#endif

		if(dbp->get(dbp, txn, &dkey, &ddata, 0) == DB_NOTFOUND)
		{
			printf("DB_NOTFOUND error\n");
			successflag = false;
		}
		else if(memcmp(ddata.data, val, val_len) != 0)
			retval = 1;

#ifdef _TXN_TEST_
		txn->commit(txn, 0);
#endif

		delete[] key;
		delete[] val;
		ta->ncomplete++;
	}

	if(successflag)
		return retval;
	return -1;
}

int bdb_getput(threadarg *ta)
{
	int x, y, w = 0, r = 0, val_len, no_write = 0, no_read = 0, s = ta->nstart, n = ta->nend, factor = ta->factor;
	int base_write = s + ((factor-1)*(n-s))/factor, retval = 0;
	printf("the s=%d and n = %d and base_write = %d\n", s, n, base_write);

	DB_TXN *txn;
	DBT dkey, ddata;
	char *key, *val;

	char data[128];
	int dat_len = 128;
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
			memset(&dkey, 0, sizeof (DBT));
			memset(&ddata, 0, sizeof (DBT));
			dkey.data = key;
			dkey.size = strlen(key);
			ddata.data = (void*)val;
			ddata.size = val_len;
			txn = NULL;
#ifdef _TXN_TEST_
			envp->txn_begin(envp, NULL, &txn, 0);
#endif

			if(dbp->put(dbp, txn, &dkey, &ddata, DB_OVERWRITE_DUP) < 0)
			{
				no_write++;
				successflag = false;
			}
#ifdef _TXN_TEST_
			txn->commit(txn, 0);
#endif

			delete[] key;
			delete[] val;
			ta->ncomplete++;
		}
		else
		{
			//read
			r++;
			y = my_rand(s, base_write);
			key = getkey(y);
			val = getval(y);

			val_len = strlen(val);
			memset(&dkey, 0, sizeof (DBT));
			memset(&ddata, 0, sizeof (DBT));

			dkey.data = key;
			dkey.size = strlen(key);
			ddata.data = data;
			ddata.ulen = dat_len;
			ddata.flags = DB_DBT_USERMEM;
			txn = NULL;
#ifdef _TXN_TEST_
			envp->txn_begin(envp, NULL, &txn, 0);
#endif
			if(dbp->get(dbp, txn, &dkey, &ddata, 0) == DB_NOTFOUND)
			{
				no_read++;
				successflag = false;
			}
			else if(memcmp(ddata.data, val, val_len) != 0)
				retval = 1;
#ifdef _TXN_TEST_
			txn->commit(txn, 0);
#endif
			delete[] key;
			delete[] val;
			ta->ncomplete++;
		}
	}
	printf("Write = %d and Read = %d | noWrite = %d and noRead = %d\n", w, r, no_write, no_read);
	if(successflag)
		return retval;
	return -1;
}

void *bdb_threadfuncput(void *arg)
{
	threadarg* ta = (threadarg*)arg;
	off_t retval = bdb_put(ta);
	return (void*)retval;
}
void *bdb_threadfuncget(void *arg)
{
	threadarg* ta = (threadarg*)arg;
	off_t retval = bdb_get(ta);
	return (void*)retval;
}
void *bdb_threadfunc_getput(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bdb_getput(ta);
	return (void*)retval;
}

int bdb_bench_getput(int num_threads, int num_items, int factor)
{
	printf("[%d percent write and %d percent read performance test for BDB] by inserting %d items using %d threads\n",100/factor, (100*factor - 100)/factor, num_items, num_threads);
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

		targs[i].nstart = s, targs[i].nend = s+nitems, targs[i].ncomplete = 0;
		if((ret = bdb_put(&targs[i])) < 0)
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
		targs[i].tbl = NULL;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = factor;
		targs[i].ncomplete = 0;

		if(pthread_create(&thrds[i], &attr, bdb_threadfunc_getput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BDB getput, qutting");
			exit(-1);
		}
		s += (num_items/num_threads);
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for writing 20 percent and reading 80 percent of %d items by %d threads for BDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

int bdb_bench_put(int num_threads, int num_items)
{
	printf("[PUT- performance test for BDB] by inserting %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0;
	time_eval te;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

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
		targs[i].factor = 0;
		targs[i].ncomplete = 0;
		if(pthread_create(&thrds[i], &attr, bdb_threadfuncput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in BDB PUT, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BDB PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for inserting %d items by %d threads for BDB is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}
int bdb_bench_get(int num_threads, int num_items)
{
	printf("[GET- performance test for BDB] by retrieving %d items using %d threads\n", num_items, num_threads);
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

	//create threads and run
	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = NULL;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = 0;
		targs[i].ncomplete = 0;
		if(pthread_create(&thrds[i], &attr, bdb_threadfuncget, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in bdb GET, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in BDB GET");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	te.end_counting();

	printf("Overall time taken for getting %d items by %d threads for BDB  is;\n", num_items, num_threads);
	te.print_time();

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	if(successflag)
		return (int)retval;
	return -1;
}

 void bdb_bench(int num_threads, int num_items, char *ops, int factor)
 {
     	int ret = 0, env_opt;
    	char *db_dir = (char*)"bdb_test", *db_name = (char*)"bdbtest.db";
     	char path[300];

     	flags = OPEN_FLAGS;
     	type = DB_BTREE;
     	env_opt = DB_REGION_INIT;

	envp = NULL;
    	ret = db_env_create(&envp, 0);
    	if (ret != 0) {
		fprintf(stderr, "Error creating environment handle: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
    	// Create path if not exists 
    	snprintf(path, 300, "mkdir -p %s", db_dir);
    	if (system (path)) {
		printf("Could not create the path %s\n", path);
		exit(-1);
    	}
	ret = envp->set_cachesize(envp, BDB_BUFFER_SIZE_GB, BDB_BUFFER_SIZE_BYTES, 1);
	if (ret != 0) {
		fprintf(stderr, "Error setting cache size: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
    	ret = envp->set_lk_max_locks(envp, 100000);
    	if (ret != 0) {
		fprintf(stderr, "Error setting max locks: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
        ret = envp->set_lk_max_objects(envp, 100000);	
    	if (ret != 0) {
		fprintf(stderr, "Error setting max objects: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
	env_opt |= DB_TXN_NOSYNC;

	ret = envp->set_flags(envp, env_opt, 1);
    	if (ret != 0) {
		fprintf(stderr, "Error setting flags: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
	ret = envp->log_set_config(envp, DB_LOG_AUTO_REMOVE, 1);
    	if (ret != 0) {
		fprintf(stderr, "Error setting log auto remove: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
	ret = envp->set_lg_bsize(envp, 10*1024*1024);
    	if (ret != 0) {
		fprintf(stderr, "Error setting log block size: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
	ret = envp->set_lg_max(envp, BDB_LOG_FILE_SIZE);
    	if (ret != 0) {
		fprintf(stderr, "Error setting log file size: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }

		
	/* Open env */
    	ret = envp->open(envp, db_dir, TXN_FLAGS, 0);
    	if (ret != 0) {
		fprintf(stderr, "Error opening environment: %s\n",
			db_strerror(ret));
		exit(-1);
    	}
	dbp = NULL;
	ret = db_create(&dbp, envp, 0);
    	if (ret != 0) {
		fprintf(stderr, "Error creating db: %s\n",
			db_strerror(ret));
		exit(-1);
   	 }
	ret = dbp->set_pagesize(dbp, 8192);
	if(ret != 0) {
		fprintf(stderr, "Error setting the pageszie: %s\n",
			db_strerror(ret));
		exit(-1);
	}
	printf("Opening %s, %d, %d\n", db_name, type, flags);
	ret = dbp->open(dbp, NULL, db_name, NULL, type, flags, 0);
	if (ret != 0) {
		printf("error in opening db\n");
		exit(-1);
    	}
	
    	if(strncmp(ops, "put", 3) == 0)
     	{
     		if((ret = bdb_bench_put(num_threads, num_items)) < 0)
     			printf("Error in running the BDB bench for PUT\n");
     	}
    	else if(strncmp(ops, "get", 3) == 0)
     	{
     		if((ret = bdb_bench_get(num_threads, num_items)) < 0)
     			printf("Error in running the BDB bench for GET\n");
     	}
     	else if(strncmp(ops, "all", 3) == 0)
     	{
		if((ret = bdb_bench_put(num_threads, num_items)) < 0)
     			printf("Error in running the BDB bench for PUT\n");
     		if((ret = bdb_bench_get(num_threads, num_items)) < 0)
     			printf("Error in running the BDB bench for GET\n");
     	}
    	else if(strncmp(ops, "overlap", 7) == 0)
    	{
    		if((ret = bdb_bench_getput(num_threads, num_items, factor)) < 0)
    			printf("Error in running the BDB bench for overlap read and write\n");
    	}
     	else
     		printf("Error in specifying the opertion type(put/get/all/overlap) for BDB bench\n");

    	if(dbp)
		dbp->close(dbp, 0);
	if(envp)
	    	envp->close(envp, 0);

	if(ret != -1)
	{
		printf("The BDB bench test was successful\n");
		if(ret == 1)
			printf("There were expected or unexptected mismatches in the retrieved values\n");
	}
	else
		printf("There were errors in BDB bench test\n");
}

#endif /* BDB__BENCH_H_ */
