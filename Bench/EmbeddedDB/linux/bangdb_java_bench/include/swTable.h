/*
 * swTable.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb library
 *
 *  Copyright (C) 2015 IQLECT All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SWTABLE_H_
#define SWTABLE_H_

#include "swTableUnit.h"

/*
 * swTable has timestamp as key
 */

namespace bangdb
{

class swTable {
public:
	swTable(database *db, const char *tableName, table_env *tenv, int ttlsec, bool archive = false);
	void addIndex(const char *idxName, table_env *tenv);
	int initialize();
	wideConnection *getConnection();
	wideConnection *getActiveConnection();
	wideConnection *getPassiveConnection();
	int put(const char *str, int len, insert_options iop);
	int put(const char *str, int len, const char *idx, const char *idxkey);
	int put(const char *str, int len, const char *idx, const char *idxkey, int idxkeylen);
	/*
	 * scan for period sec means from cur - period upto current
	 */
	resultset *scan(int period);
	/*
	 * scan for period sec with lag means from (cur - lag - period) upto current - lag
	 */
	resultset *scan(int period, int lag);
	/*
	 * scan for whole ttlsec
	 */
	resultset *scan_full();
	resultset *scan_remaining(ULONG_T from_time, int lag);
	int getTTLSec();
	bool needPassive(int windowsec);
	FILEOFF_T getnextlsn();
	void close();
	virtual ~swTable();
private:
	int _init();
	/*
	 * scan from t1 to t2 sec
	 */
	resultset *_scan(int t1, int t2);
	resultset *_scan(int t1, int t2, FDT *sk, FDT *ek, scan_filter *sf);
	resultset *_scan(int t1, int t2, LONG_T sk, LONG_T ek, scan_filter *sf);
	bool _shouldExit();
	void _archive_table(swTableUnit *tbl);
	void _expire_and_create();
	static void *_handle_background_work(void *arg);
	database *_db;
	swTableUnit *_activeTable;
	swTableUnit *_passiveTable;
	char *_tableName;
	table_env *_tenv;
	int _ttlsec;
	pthread_t _bworker;
	bool _shouldexit;
	bool _exited;
	bool _archive;
	bool _init_done;
};
}
#endif /* SWTABLE_H_ */
