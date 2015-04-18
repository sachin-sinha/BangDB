/*
 * redis_bench.h
 *
 */

#include "common.h"
#include "hiredis/hiredis.h"

redisContext * getConnection()
{
	redisContext *c;

	const char *hostname = "127.0.0.1";
	int port = 6379;

	c = redisConnect(hostname, port);
	if (c == NULL || c->err) {
		if (c) {
			printf("Connection error: %s\n", c->errstr);
			redisFree(c);
		} else {
			printf("Connection error: can't allocate redis context\n");
		}
		exit(1);
	}
	return c;
}

redisContext **getConnections(int n)
{
	redisContext **c = malloc(sizeof(redisContext*)*n);
	int i = 0;
	for(; i < n; i++)
		c[i] = getConnection();
	return c;
}

void freeConnection(redisContext *c)
{
	redisFree(c);
}

void freeConnections(redisContext **c, int n)
{
	int i = 0;
	for(; i < n; i++)
		redisFree(c[i]);
	free(c);
}

int redis_server_get(struct threadarg *ta)
{
	redisContext *c = (redisContext*)ta->tbl;
	redisReply *reply;

	int s = ta->nstart, n = ta->nend, val_len, retval = 0, i;
	char *key, *val;
	int count = 0, mismatch = 0;

	bool successflag = true;
	for(i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);
		val_len = strlen(val);
		
		reply = (redisReply*)redisCommand(c, "GET %s", key);

		if(reply && !reply->str)
		{
			//printf("null retrieved for i=%d \n",i);
			count++;
			successflag = false;
		}
		else if(reply->str && memcmp(reply->str, val, val_len) != 0)
		{
			//printf("mismatch\n");
			retval = 1;
			mismatch++;
		}

		freeReplyObject(reply);
		free(key);
		free(val);

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

int redis_server_put(struct threadarg *ta)
{
	redisContext *c = (redisContext*)ta->tbl;
	redisReply *reply;
	
	int s = ta->nstart, n = ta->nend, i;
	char *key, *val;

	bool successflag = true;
	int count = 0;

	for(i = s; i<n; i++)
	{
		key = getkey(i);
		val = getval(i);

		reply = (redisReply*)redisCommand(c,"SET %s %s", key, val);

		if(reply && memcmp(reply->str, "OK", 2) != 0)
		{
			successflag = false;
			count++;
		}

		freeReplyObject(reply);
		free(key);
		free(val);

		ta->ncomplete++;
	}

	if(count > 0)
		printf("could not insert %d keys\n", count);

	if(successflag)
		return 0;
	return -1;
}

int redis_server_getput(struct threadarg *ta)
{
	redisContext *c = (redisContext*)ta->tbl;
	redisReply *reply;
	
	int s = ta->nstart, n = ta->nend, factor = ta->factor, x, y, w = 0, r = 0, val_len, no_write = 0, no_read = 0, retval = 0, i;
	int base_write = s + ((factor-1)*(n-s))/factor;

	char *key, *val;
	bool successflag = true;

	for(i = s; i<n; i++)
	{
		x = my_rand(1, factor);
		if(x == factor)
		{
			//write
			w++;
			y = my_rand(base_write, n);
			key = getkey(y);
			val = getval(y);

			reply = (redisReply*)redisCommand(c,"SET %s %s", key, val);
			if(reply && memcmp(reply->str, "OK", 2) != 0)
			{
				successflag = false;
			}
			freeReplyObject(reply);
			free(key);
			free(val);

		}
		else
		{
			//read
			r++;
			y = my_rand(s, base_write);
			key = getkey(y);
			val = getval(y);
			val_len = strlen(val);

			reply = (redisReply*)redisCommand(c, "GET %s", key);

			if(reply && !reply->str)
			{
				no_read++;
			}
			else if(reply && memcmp(reply->str, val, val_len) != 0)
			{
				//printf("mismatch\n");
				retval = 1;
			}

			freeReplyObject(reply);
			free(key);
			free(val);

		}
		ta->ncomplete++;
	}
	printf("Write = %d and Read = %d | noWrite = %d and noRead = %d\n", w, r, no_write, no_read);
	if(successflag)
		return retval;
	return -1;
}

void *redis_server_threadfuncput(void *arg)
{
	struct threadarg *ta = (struct threadarg*)arg;
	off_t retval = redis_server_put(ta);
	//delete ta;
	return (void*)retval;
}

void *redis_server_threadfuncget(void *arg)
{
	struct threadarg *ta = (struct threadarg*)arg;
	off_t retval = redis_server_get(ta);
	//delete ta;
	return (void*)retval;
}

void *redis_server_threadfunc_getput(void *arg)
{
	struct threadarg *ta = (struct threadarg*)arg;
	off_t retval = redis_server_getput(ta);
	//delete ta;
	return (void*)retval;
}

int redis_server_bench_getput(int num_threads, int num_items, int factor)
{
	printf("[%d percent write and %d percent read performance test for redis] by inserting %d items using %d threads\n", 100/factor, (100*factor-100)/factor, num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	struct time_eval te;
	int s = 0, nitems, ret;long retval = 0, i;
	redisContext **c = getConnections(num_threads);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	//first insert some items based on factor for better read by threads
	for(i = 0; i<num_threads; i++)
	{
		nitems = ((num_items/num_threads)*(factor-1))/factor;
		printf("writing from %d upto %d for nitems = %d\n", s, s+nitems, nitems);
		
		struct threadarg temp_ta;
		temp_ta.tbl = (void*)c[i]; temp_ta.nstart = s; temp_ta.nend = s+nitems; temp_ta.ncomplete = 0;
		if((ret = redis_server_put(&temp_ta)) < 0)
			successflag = false;
		s += (num_items/num_threads);
	}

	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}

	s = 0;
	start_counting(&te);

	for(i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)c[i];
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].factor = factor;
		targs[i].ncomplete = 0;

		if(pthread_create(&thrds[i], &attr, redis_server_threadfunc_getput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in redis getput, qutting");
			exit(-1);
		}
		s += (num_items/num_threads);
	}

	//wait for all threads to join
	for(i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in redis PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	end_counting(&te);

	printf("Overall time taken for writing and reading of %d items by %d threads for redis is;\n", num_items, num_threads);
	print_time(&te);

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	freeConnections(c, num_threads);

	if(successflag)
		return (int)retval;
	return -1;
}

int redis_server_bench_put(int num_threads, int num_items)
{
	printf("[PUT- performance test for redis] by inserting %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0, i;
	struct time_eval te;
	redisContext **c = getConnections(num_threads);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//background thread for counting
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}	

	start_counting(&te);

	for(i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)c[i];
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;		

		if(pthread_create(&thrds[i], &attr, redis_server_threadfuncput, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in redis PUT, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(i = 0; i<num_threads; i++)
	{	
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in redis PUT");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	end_counting(&te);

	printf("Overall time taken for inserting %d items by %d threads for redis is;\n", num_items, num_threads);
	print_time(&te);

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining the background progress update thread");

	freeConnections(c, num_threads);

	if(successflag)
		return (int)retval;
	return -1;
}

int redis_server_bench_get(int num_threads, int num_items)
{
	printf("[GET- performance test for BangdDB] by retrieving %d items using %d threads\n", num_items, num_threads);
	pthread_t thrds[num_threads], backg_thrd;
	pthread_attr_t attr;
	bool successflag = true;
	void *status;
	int s = 0;long retval = 0, i;
	struct time_eval te;
	redisContext **c = getConnections(num_threads);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	//start background thread for progress update
	if(pthread_create(&backg_thrd, &attr, progress_update, (void*)&num_threads) != 0)
	{
		printf("error in creating background thread for progress update");
		exit(-1);
	}

	start_counting(&te);

	for(i = 0; i<num_threads; i++)
	{
		targs[i].tbl = (void*)c[i];
		targs[i].nstart = s;
		targs[i].nend = s + (num_items/num_threads);
		targs[i].ncomplete = 0;		

		if(pthread_create(&thrds[i], &attr, redis_server_threadfuncget, (void*)&targs[i]) != 0)
		{
			printf("error in creating thread in redis GET, qutting");
			exit(-1);
		}
		s += num_items/num_threads;
	}

	//wait for all threads to join
	for(i = 0; i<num_threads; i++)
	{
		if(pthread_join(thrds[i], &status) != 0)
			printf("error in joining thread in redis GET");
		if((long)status == -1)
			successflag = false;
		else
			retval = (long)status;
	}

	end_counting(&te);

	printf("Overall time taken for getting %d items by %d threads for redis is;\n", num_items, num_threads);
	print_time(&te);

	if(pthread_join(backg_thrd, &status) != 0)
		printf("error in joining background thread for progress update");

	freeConnections(c, num_threads);

	if(successflag)
		return (int)retval;
	return -1;
}

void redis_server_bench(int num_threads, int num_items, char *ops, int factor)
{
	int retval = 0;

	if(strncmp(ops, "put", 3) == 0)
	{
		if((retval = redis_server_bench_put(num_threads, num_items)) < 0)
			printf("Error in running the redis bench for PUT\n");
	}
	else if(strncmp(ops, "get", 3) == 0)
	{
		if((retval = redis_server_bench_get(num_threads, num_items)) < 0)
			printf("Error in running the redis bench for GET\n");
	}
	else if(strncmp(ops, "all", 3) == 0)
	{
		if((retval = redis_server_bench_put(num_threads, num_items)) < 0)
			printf("Error in running the redis bench for PUT\n");
		if((retval = redis_server_bench_get(num_threads, num_items)) < 0)
			printf("Error in running the redis bench for GET\n");
	}
	else if(strncmp(ops, "overlap", 7) == 0)
	{
		if((retval = redis_server_bench_getput(num_threads, num_items, factor)) < 0)
			printf("Error in running the redis bench for overlap read and write\n");
	}
	/*else if(strncmp(ops, "simple", 6) == 0)
	{
		if((retval == redis_server_bench_simple(c, num_threads, num_items)) < 0)
			printf("Error in running the redis bench for simple calls\n");
	}*/
	else
		printf("Error in specifying the opertion type(put/get/all/overlap) for redis bench\n");

	if(retval != -1)
	{
		printf("The redis bench test was successful\n");
		if(retval == 1)
			printf("There were expected or unexptected mismatches in the retrieved values\n");
	}
	else
		printf("There were errors in redis bench test\n");
}
