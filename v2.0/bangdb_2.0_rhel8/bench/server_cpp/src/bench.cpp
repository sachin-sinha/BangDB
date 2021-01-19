/*
 * bench.cpp
 *
 *  Created on: 18 Aug 2020
 *      Author: sachin sinha
 */


#include "bangdb_bench.h"

int main(int argc, char *argv[])
{
	if(argc < 5)
	{
		printf("----------------------------------------------------------------------------\n");
		printf("usage: bangdb_bench <kv/doc/stream> <num_threads> <num_items> <put/get/scan/all/overlap> [factor(optional define only with overlap)]\n");
		printf("       factor > 1; the factor defines how much read and write\n");
		printf("       1/factor part write and rest read. ex; factor = 3, 33 percent write and 67 percent read\n");
		printf("----------------------------------------------------------------------------\n");
		printf("\nRunning the default test for kv (key value) with 32 threads (connections), put and get 1000000 items\n");
		bangdb_bench("kv", 32, 1000000, "all", 0);
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
		if((factor = atoi(argv[5])) < 1)
		{
			printf("factor must be greater than 1\n");
			exit(0);
		}
	}

	bangdb_bench(argv[1], atoi(argv[2]), atoi(argv[3]), argv[4], factor);

	return 0;
}
