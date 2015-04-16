/*
 * swTableUnit.h
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

#ifndef SWTABLEUNIT_H_
#define SWTABLEUNIT_H_

#include "database.h"
#include "hash_tbl.h"
#include "timestamp.h"

namespace bangdb
{

struct index_keysize
{
	char *name;
	table_env tenv;
	~index_keysize()
	{
		delete[] name;
		name = NULL;
	}
};

class swTableUnit {
public:
	swTableUnit(database *db, const char *tableName, table_env *tenv, int ttlsec);
	void addIndex(const char *idxName, table_env *tenv);
	int createTable();
	wideConnection *getConnection();
	void closeTable(bangdb_close_type flag);
	ULONG_T getCreateTimeStamp();
	void start();
	bool hasExpired();
	bool shouldSwitch();
	bool isStarted();
	void get_full_archive_path(char **fpath, char **new_path);
	void get_full_archive_path2(char **fpath, char **new_path);
	FILEOFF_T getnextlsn();
	virtual ~swTableUnit();
private:
	database *_db;
	wideTable *_table;
	wideConnection *_conn;
	char *_tableName;
	table_env *_tenv;
	hash_tbl<index_keysize> *_indexMap;
	long _ttlsec;
	long _buffersec;
	ULONG_T createTS;	//time in microsec
	bool started;
};
}
#endif /* SWTABLEUNIT_H_ */
