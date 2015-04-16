/*
 * 	database.h
 *
 *  Libbangdb library
 *
 *  Copyright (C) 2011 Sachin Sinha All rights reserved.
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
 *
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "basehdr.h"
#include "table.h"
#include "wideTable.h"
#include "swTable.h"
#include "swEntityCount.h"
#include "bangdbtxn.h"
namespace bangdb_client
{
class table;
class wideTable;
class wideTable_impl;
struct table_item_wrap;
struct wideTable_item_wrap;
class table_impl;
class swTable;
class swEntityCount;
class transaction_context;
class bangdb_txn;

class database
{
public:

	//todo:add db_env -> mainly for host, port etc... may include tran_type as well
	database(const char *databasename, bangdbEnv *_env, db_transaction_type transaction_type, const char *user, const char *pwd);

	table* gettable(const char *name, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	wideTable* getWideTable(const char *name, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	table* getPrimitiveTable(const char *name, bangdb_primitive_data_type dataType = PRIMITIVE_LONG, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	void begin_transaction(bangdb_txn *txn);

	LONG_T commit_transaction(bangdb_txn *txn);

	void abort_transaction(bangdb_txn *txn);

	int closetable(const char *rname, bangdb_close_type tblclose = DEFAULT_AT_CLIENT);

	int closetable(table *tbl, bangdb_close_type tblclose = DEFAULT_AT_CLIENT);

	int closetable(wideTable *tbl, bangdb_close_type tblclose = DEFAULT_AT_CLIENT);

	void closedatabase(bangdb_close_type dbclose = DEFAULT_AT_CLIENT);

	int dumpdata();

	void cleanup();

	char* getdbname();

	int get_num_tables();

	char *getdbdir();

	int get_table_name_list(char ***list);

	void free_table_name_list(char **list, int nt);

	int get_tran_type();

	char *get_dbmetadata(int *fd);

	table_env *get_table_meta(char *tablename, bangdb_table_type *_tbl_type);

	~database();

private:

	table* _gettable(const char *name, bangdb_open_type openflag, table_env *tenv, bangdb_primitive_data_type dataType, bangdb_table_type _tbl_type = NORMAL_TABLE);

	table_impl* _tableexists(char *tbl);

	wideTable_impl* _wideTableexists(char *tbl);

	bool _isadmin();

	char *dbname;

	bangdbEnv *env;

	//table_env *gtable_env;

	//hash_tbl<table_item> *dbtbls;
	table_item_wrap *dbtbls;

	//hash_tbl<wideTable_item> *dbwtbls;
	wideTable_item_wrap *dbwtbls;

	db_transaction_type tran_type;

	pthread_mutex_t dbmutex;

	friend class table_impl;

	friend class wideTable_impl;

	friend class swTable;

	friend class swEntityCount;
};
}
#endif /* DATABASE_H_ */
