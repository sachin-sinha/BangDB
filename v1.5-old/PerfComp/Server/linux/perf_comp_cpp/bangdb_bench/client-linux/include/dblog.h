/*
 * dblog.h
 *
 *  Created on: 18-Jul-2014
 *      Author: sachin
 */

#ifndef DBLOG_H_
#define DBLOG_H_

#include "bangdb.h"
#include "light_lock.h"
#include "timestamp.h"


//#define _DBLOG_STAT_

namespace bangdb_client
{

class db_log {
public:
	db_log(const char *logpath, const char *dbname, int logsizemb);

	int init();

	void log_info(const char *log, int loglen);

	int flush(char *uptoaddr = 0);

	void shutdown();

	int close_log();

	virtual ~db_log();

private:

	int _init();

	int _split(bool force = false);

	int _log_info(char *log, int loglen);

	int _logflushbulk(char *uptoaddr);

	int _logdumptodisk(char *fromaddr, int totlen);

	char *_get_log_file_name(bool cur = false);

	bool _shouldsplit();

	//checks if the page buffer should be flushed to disk or not based on the amount of info filled in the dptbl
	bool _shouldbufflushed();

	int openlog(char *logfname, int oflag);

	int rename_log(char *oldlog, char *newlog);

	//checks if the background threads should exit or not, infact notify that system is shutting down
	bool _shouldexit() { return shouldexit; }

	//mark that all threads should exit now
	void _setexit() { shouldexit = true; }

	int _inithousekeep();

	//thread entry function for regular checking and splitting of log if needed
	static void* _threadlog_split_flush(void *arg);

	//to create and monitor various background threads of log
	static void* _background(void *arg);

	bool shouldexit;						//flag for all the threads, a notification that all threads should not exit as shutting down

	bool bgexited;

	bool initdone;

	int logfd;

	char *logpath;

	char *dbname;

	char *logfname;

	char *endaddr;

	char *currentpos;

	char *baseaddr;

	char *lastflushedpos;

	BUFFER_T logshmsz;

	int sleep_time;

	pthread_t logtid;

	light_mutex_lock _flush_lock;

	light_mutex_lock _write_lock;

	//some stat vars
#ifdef _DBLOG_STAT_
	void print_stat();
	LONG_T flushed_checked;
	LONG_T log_flushed;
	LONG_T split_checked;
	LONG_T split_done;
	LONG_T split_done_foreground;
#endif
};
}
#endif /* DBLOG_H_ */
