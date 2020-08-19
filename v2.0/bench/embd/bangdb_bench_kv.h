/*
 * bangdb_bench_kv.h
 *
 *  Created on: 19-Aug-2020
 *      Author: sachin
 */

#ifndef BANGDB_BENCH_KV_H_
#define BANGDB_BENCH_KV_H_

#include "common.h"

using namespace BangDB;

int bangdb_get(threadarg *ta)
{
	BangDBTable *tbl = (BangDBTable*)ta->tbl;

	if(!tbl)
	{
		printf("table null error\n");
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

		if(tbl->get(&ikey, &ival) < 0)
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
		ikey.free();
		delete[] val;

		ta->ncomplete++;
	}

	if(count > 0)
		printf("could not read %d keys\n", count);
	if(mismatch > 0)
		printf("mismatch in read for %d keys\n", mismatch);

	if(successflag)
		return retval;

	return -1;
}

int bangdb_scan(threadarg *ta)
{
	BangDBTable *tbl = (BangDBTable*)ta->tbl;

	if(!tbl)
	{
		printf("table null error\n");
		return -1;
	}

	int s = ta->nstart, n = ta->nend, nc = 0, nitr = 0;
	ResultSet *rs = NULL;
	ScanFilter sf;
	char *k1 = getkey(s);
	char *k2 = getkey(n);
	FDT skey(k1, strlen(k1)), ekey(k2, strlen(k2));

	while(true)
	{
		rs = tbl->scan(rs, &skey, &ekey, &sf);
		if(!rs)
			break;
		nc += rs->count();
		++nitr;
		ta->ncomplete += nc;
	}

	skey.free();
	ekey.free();

	printf("scanned [ %d ] items in [ %d ] iterations\n", nc, nitr);

	if(nc != n - s)
	{
		printf("num of items scanned didn't match, exp [ %d ], scanned [ %d ]\n", n-s, nc);
		return -1;
	}
	return 0;
}

int bangdb_put(threadarg *ta)
{
	BangDBTable *tbl = (BangDBTable*)ta->tbl;

	if(!tbl)
	{
		printf("tbl null error\n");
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

		if(tbl->put(&ikey, &ival, INSERT_UNIQUE) < 0)
		{
			successflag = false;
			count++;
		}

		ikey.free();
		ival.free();

		ta->ncomplete++;
	}

	if(count > 0)
		printf("could not insert %d keys\n", count);

	if(successflag)
		return 0;
	return -1;
}
/* un comment for server if wanna run simple call else leave it */
int bangdb_simple(threadarg *ta)
{
	BangDBTable *tbl = (BangDBTable*)ta->tbl;

	if(!tbl)
	{
		printf("tbl null error\n");
		return -1;
	}
	int s = ta->nstart, n = ta->nend;

	bool successflag = true;
	int count = 0;

	for(int i = s; i<n; i++)
	{
		ta->ncomplete++;
	}

	if(count > 0)
		printf("could not make simple calls for %d keys\n", count);

	if(successflag)
		return 0;
	return -1;
}

int bangdb_getput(threadarg *ta)
{
	BangDBTable *tbl = (BangDBTable*)ta->tbl;
	if(!tbl)
	{
		printf("tbl null error\n");
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

			if((ret=tbl->put(&ikey, &ival, INSERT_UPDATE)) < 0)
			{
				successflag = false;
			}
			if(ret == 1)
				no_write++;
			ikey.free();
			ival.free();
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

			if(tbl->get(&ikey, &out) < 0)
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
			ikey.free();
			delete[] val;
		}
		ta->ncomplete++;
	}

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

void *bangdb_threadfuncscan(void *arg)
{
	threadarg *ta = (threadarg*)arg;
	off_t retval = bangdb_scan(ta);
	return (void*)retval;
}

int bangdb_bench_getput(BangDBTable *tbl, int num_threads, int num_items, int factor)
{
	printf("[%d percent write and %d percent read performance test for BangDB] by inserting %d items using %d threads\n", 100/factor, (100*factor-100)/factor, num_items, num_threads);
	bool successflag = true;
	BangDBTimer timer;
	BangDBThread thrds[num_threads], backg_thrd;
	int s = 0, ret, status;
	long iops;

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

	backg_thrd.setArg(&num_threads);
	backg_thrd.runJoinable(progress_update);

	s = 0;
	timer.start();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = factor;
		targs[i].ncomplete = 0;
		thrds[i].setArg(&targs[i]);
		thrds[i].runJoinable(bangdb_threadfunc_getput);
		s += (num_items/num_threads);
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if((status = thrds[i].join()) < 0)
			printf("error in joining thread in BangDB PUT");
		if(status == -1)
			successflag = false;
	}

	timer.stop();

	printf("Overall time taken for writing and reading of %d items by %d threads for BangDB is;\n", num_items, num_threads);
	timer.printElapsedTime();
	iops = timer.runtime(1) > 0 ? ((long)num_items*1000)/timer.runtime(1) : num_items;

	if((status = backg_thrd.join()) < 0)
		printf("error in joining background thread for progress update");

	if(successflag)
	{
		printf("Average throughput for get and put = %ld ops/sec\n", iops);
		return (int)status;
	}
	return -1;
}

int bangdb_bench_simple(BangDBTable *tbl, int num_threads, int num_items)
{
	printf("[SIMPLE CALL- performance test for BangDB] by inserting %d items using %d threads\n", num_items, num_threads);
	bool successflag = true;
	int s = 0, retval = 0;
	long iops;
	BangDBTimer timer;
	BangDBThread thrds[num_threads], backg_thrd;

	backg_thrd.setArg(&num_threads);
	backg_thrd.runJoinable(progress_update);

	timer.start();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;
		thrds[i].setArg(&targs[i]);
		thrds[i].runJoinable(bangdb_threadfunc_simple);
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if((retval = thrds[i].join()) < 0)
			printf("error in joining thread in BangDB SIMPLE CALL");
		if(retval == -1)
			successflag = false;
	}

	timer.stop();

	printf("Overall time taken for making simple call %d items by %d threads for BangDB is;\n", num_items, num_threads);
	timer.printElapsedTime();
	iops = timer.runtime(1) > 0 ? ((long)num_items*1000)/timer.runtime(1) : num_items;

	if((retval = backg_thrd.join()) < 0)
		printf("error in joining background thread for progress update");

	if(successflag)
	{
		printf("Average throughput for simple = %ld ops/sec\n", iops);
		return retval;
	}
	return -1;
}

int bangdb_bench_put(BangDBTable *tbl, int num_threads, int num_items)
{
	printf("[PUT- performance test for BangDB] by inserting %d items using %d threads\n", num_items, num_threads);
	bool successflag = true;
	int s = 0, retval = 0;
	long iops;
	BangDBTimer timer;
	BangDBThread thrds[num_threads], backg_thrd;

	backg_thrd.setArg(&num_threads);
	backg_thrd.runJoinable(progress_update);

	timer.start();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;
		thrds[i].setArg(&targs[i]);
		thrds[i].runJoinable(bangdb_threadfuncput);
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if((retval = thrds[i].join()) < 0)
			printf("error in joining thread in BangDB PUT");
		if(retval == -1)
			successflag = false;
	}

	timer.stop();

	printf("Overall time taken for inserting %d items by %d threads for BangDB is;\n", num_items, num_threads);
	timer.printElapsedTime();
	iops = timer.runtime(1) > 0 ? ((long)num_items*1000)/timer.runtime(1) : num_items;

	if((retval = backg_thrd.join()) < 0)
		printf("error in joining background thread for progress update");

	if(successflag)
	{
		printf("Average throughput = %ld ops/sec\n", iops);
		return (int)retval;
	}
	return -1;
}

int bangdb_bench_get(BangDBTable *tbl, int num_threads, int num_items)
{
	printf("[GET- performance test for BangdDB] by retrieving %d items using %d threads\n", num_items, num_threads);
	bool successflag = true;
	int s = 0, retval = 0;
	long iops;
	BangDBTimer timer;
	BangDBThread thrds[num_threads], backg_thrd;

	backg_thrd.setArg(&num_threads);
	backg_thrd.runJoinable(progress_update);

	timer.start();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;
		thrds[i].setArg(&targs[i]);
		thrds[i].runJoinable(bangdb_threadfuncget);
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if((retval = thrds[i].join()) < 0)
			printf("error in joining thread in BangDB GET");
		if(retval == -1)
			successflag = false;
	}

	timer.stop();

	printf("Overall time taken for getting %d items by %d threads for BangDB is;\n", num_items, num_threads);
	timer.printElapsedTime();
	iops = timer.runtime(1) > 0 ? ((long)num_items*1000)/timer.runtime(1) : num_items;

	if((retval = backg_thrd.join()) < 0)
		printf("error in joining background thread for progress update");

	if(successflag)
	{
		printf("Average throughput get = %ld ops/sec\n", iops);
		return (int)retval;
	}
	return -1;
}

int bangdb_bench_scan(BangDBTable *tbl, int num_threads, int num_items)
{
	printf("[SCAN- performance test for BangdDB] by retrieving %d items using %d threads\n", num_items, num_threads);
	bool successflag = true;
	int s = 0, retval = 0;
	long iops;
	BangDBTimer timer;
	BangDBThread thrds[num_threads], backg_thrd;

	backg_thrd.setArg(&num_threads);
	backg_thrd.runJoinable(progress_update);

	timer.start();

	for(int i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)tbl;
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;
		thrds[i].setArg(&targs[i]);
		thrds[i].runJoinable(bangdb_threadfuncscan);
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(int i = 0; i<num_threads; i++)
	{
		if((retval = thrds[i].join()) < 0)
			printf("error in joining thread in BangDB SCAN");
		if(retval == -1)
			successflag = false;
	}

	timer.stop();

	printf("Overall time taken for getting %d items by %d threads for BangDB is;\n", num_items, num_threads);
	timer.printElapsedTime();
	iops = timer.runtime(1) > 0 ? ((long)num_items*1000)/timer.runtime(1) : num_items;

	if((retval = backg_thrd.join()) < 0)
		printf("error in joining background thread for progress update");

	if(successflag)
	{
		printf("Average throughput scan = %ld ops/sec\n", iops);
		return (int)retval;
	}
	return -1;
}

#endif /* BANGDB_BENCH_KV_H_ */
