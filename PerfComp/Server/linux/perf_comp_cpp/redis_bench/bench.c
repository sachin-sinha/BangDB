/*
 * bench.cpp
 *
 */


#include "redis_server_bench.h"

int main(int argc, char *argv[])
{
	int factor = 0;
	if(argc < 4)
	{
		printf("----------------------------------------------------------------------------\n");
		printf("usage: bangdb_bench <num_threads> <num_items> <put/get/all/overlap> [factor(optional define only with overlap)]\n");
		printf("       factor > 1; the factor defines how much read and write\n");
		printf("       1/factor part write and rest read. ex; factor = 3, 33 percent write and 67 percent read\n");
		printf("----------------------------------------------------------------------------\n");
		printf("\nRunning the default test with 100 connections, put and get 1000000 items\n");
		redis_server_bench(100, 1000000, (char*)"all", 0);
		exit(0);
	}

	if(strncmp(argv[3], "overlap", 7) == 0)
	{
		if(argc != 5)
		{
			printf("please provide factor for the overlap\n");
			exit(0);
		}
		if((factor = atoi(argv[4])) < 1)
		{
			printf("factor must be greater than 1\n");
			exit(0);
		}
	}

	redis_server_bench(atoi(argv[1]), atoi(argv[2]), argv[3], factor);

	return 0;
}
