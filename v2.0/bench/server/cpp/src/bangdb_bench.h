/*
 * bangdb_bench.h
 *
 *      Author: sachin
 */

#ifndef BANGDB_BENCH_H_
#define BANGDB_BENCH_H_

#include "common.h"
#include "bangdb_bench_kv.h"
#include "bangdb_bench_doc.h"

using namespace BangDB_Client;

void bangdb_bench(const char *testtype, int num_threads, int num_items, const char *ops, int factor)
{
	int retval = 0, test_type = 1;
	BangDBEnv *env;
	BangDBDatabase *db;
	BangDBTable *tbl;

	//create BangDBDatabase, BangDBTable and connection
	DBParam dpm;
	dpm.setTransactionType(DB_TRANSACTION_NONE);
	env = new BangDBEnv(&dpm);
	db = new BangDBDatabase("mydb", env, &dpm);

	if(strncmp(testtype, "kv", 2) == 0)
		test_type = 1;
	else if(strncmp(testtype, "doc", 3) == 0)
		test_type = 2;
	else if(strncmp(testtype, "stream", 6) == 0)
		test_type = 3;

	TableEnv tenv;

	if(test_type == 1)
	{
		tenv.setTableType(NORMAL_TABLE);
		tenv.setKeySize(12);
		if((tbl = db->getTable((char*)"mykvtable", &tenv, OPENCREATE)) == NULL)
		{
			printf("BangDBTable NULL error, quitting");
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
		else if(strncmp(ops, "scan", 4) == 0)
		{
			if((retval = bangdb_bench_scan(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for SCAN\n");
		}
		else if(strncmp(ops, "all", 3) == 0)
		{
			if((retval = bangdb_bench_put(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for PUT\n");
			if((retval = bangdb_bench_get(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for GET\n");
			if((retval = bangdb_bench_scan(tbl, num_threads, num_items)) < 0)
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
			if((retval = bangdb_bench_simple(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for simple calls\n");
		}
		else
			printf("Error in specifying the opertion type(put/get/all/overlap) for BangDB bench\n");
	}
	else if(test_type == 2)
	{
		tenv.setTableType(WIDE_TABLE);
		tenv.setKeySize(12);
		if((tbl = db->getTable((char*)"mydoctable", &tenv, OPENCREATE)) == NULL)
		{
			printf("BangDBTable NULL error, quitting");
			exit(-1);
		}

		if(strncmp(ops, "put", 3) == 0)
		{
			if((retval = bangdb_bench_putdoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for PUT\n");
		}
		else if(strncmp(ops, "get", 3) == 0)
		{
			if((retval = bangdb_bench_getdoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for GET\n");
		}
		else if(strncmp(ops, "scan", 4) == 0)
		{
			if((retval = bangdb_bench_scandoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for SCAN\n");
		}
		else if(strncmp(ops, "all", 3) == 0)
		{
			if((retval = bangdb_bench_putdoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for PUT\n");
			if((retval = bangdb_bench_getdoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for GET\n");
			if((retval = bangdb_bench_scandoc(tbl, num_threads, num_items)) < 0)
				printf("Error in running the BangDB bench for GET\n");
		}
		else if(strncmp(ops, "overlap", 7) == 0)
		{
			if((retval = bangdb_bench_getputdoc(tbl, num_threads, num_items, factor)) < 0)
				printf("Error in running the BangDB bench for overlap read and write\n");
		}
	}
	else if(test_type == 3)
	{
		printf("stream performance is not implemented as yet\n");
		exit(-1);
	}

	tbl->closeTable();
	delete tbl;
	env->closeDatabase(db);
	delete db;
	delete env;

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
