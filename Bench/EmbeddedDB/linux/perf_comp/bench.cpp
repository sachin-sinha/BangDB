/*
 * bench.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: sachin
 */

#include "bangdb_bench.h"
#include "leveldb_bench.h"
#include "bdb_bench.h"


int main(int argc, char *argv[])
{
	if(argc < 5)
	{
		printf("----------------------------------------------------------------------------\n");
		printf("usage: bangdb_bench <bangdb/leveldb/bdb> <num_threads> <num_items> <put/get/all/overlap> [factor(optional define only with overlap)]\n");
		printf("----------------------------------------------------------------------------\n");
		exit(0);
	}
	int factor = 0;
	if(strncmp(argv[4], "overlap", 7) == 0)
	{
		if(argc != 6)
		{
			printf("please provide factor for the overlap\n");
			exit(0);
		}
		factor = atoi(argv[5]);
	}
#ifdef LARGE_VALUE_TEST
	populate_largebuf();
	printf("test for large buf\n");
#endif

	if(strncmp("bangdb", argv[1], 6) == 0)
		bangdb_bench(atoi(argv[2]), atoi(argv[3]), argv[4], factor);
	else if(strncmp("leveldb", argv[1], 7) == 0)
		leveldb_bench(atoi(argv[2]), atoi(argv[3]), argv[4], factor);
	else if(strncmp("bdb", argv[1], 3) == 0)
		bdb_bench(atoi(argv[2]), atoi(argv[3]), argv[4], factor);

	return 0;
}
