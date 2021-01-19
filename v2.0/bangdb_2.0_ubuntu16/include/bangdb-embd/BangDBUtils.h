/*
 * BangDBUtils.h
 *
 *  Created on: 21-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBTHREAD_H_
#define SRC_BANGDBTHREAD_H_

#include "BangDBCommon.h"

namespace BangDB
{
class BangDBThread
{
public:
	BangDBThread();
	BangDBThread(void *arg);
	void setArg(void *arg);
	int runJoinable(void *(*func)(void*), int thread_stack_size=0);
	int runDetached(void *(*func)(void*), int thread_stack_size=0);
	int join();
	int cancel();
	~BangDBThread();
	long pth;
};
class BangDBTimer
{
public:
	BangDBTimer();
    void start();
    void stop();
    //gran = 0 means sec, 1 means ms, 2 means microsec
    long runtime(int gran);
    void printElapsedTime(const char *str = NULL);
    ~BangDBTimer();
    long pbtm;
};
struct bangdb_udf_val
{
	void *val;
	short len;				// length of val for string, long and double it's 8 or length of string. For array it's len of array
	short type;				// 5 string, 9 long, 11 double, 4 array of string, 3 custom object
	short out_to_del;		// out_to_del = 0 if not to be deleted, else 1
	short out_exp_type;		// expected type of o/p - 5 string, 9 long, 11 double, 4 array of string, 3 custom object
	bangdb_udf_val();
};
}
#endif /* SRC_BANGDBTHREAD_H_ */
