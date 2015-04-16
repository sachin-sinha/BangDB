/*
 * database.h
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

#ifndef DATABASE_H_
#define DATABASE_H_

#include "table.h"
#include "wideTable.h"
#include "bangdbtxn.h"

namespace bangdb
{

class table;
class wideTable;
class bangdb_txn;
struct wideTable_item_wrap;
struct table_item_wrap;
class table_impl;
class iqfreelist;
class wideTable_impl;

class database
{
public:
	//call to connect to NETWORK_INMEM_PERSIST db, over network, for in proc one just put NULL for host and port
	database(const char *databasename, const char *configpath = NULL, db_transaction_type transaction_type = DB_TRANSACTION_NONE, const char *dbpath = NULL, const char *dblogpath = NULL, bool _repl_done = false);

	//open flag, 0 for creat if not created else open, 1 for creat and trunc and 2 for open, idx and db types read from config file
	table* gettable(const char *name, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	wideTable* getWideTable(const char *name, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	table* getPrimitiveTable(const char *name, bangdb_primitive_data_type dataType = PRIMITIVE_LONG, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	//gets and stores the start_tn and puts a free txn_node to the progress_table (hashed by the txn unique id)
	void begin_transaction(bangdb_txn *txn);

	//starts the validation process and finally commits and returns actual tid for the transaction, also puts the node to cache table and list
	//on error it returns -1, which means user should restart the transaction
	FILEOFF_T commit_transaction(bangdb_txn *txn_handle);

	//simply clears the memory and puts the txn node to the free list
	void abort_transaction(bangdb_txn *txn_handle);

	int get_num_tables();

	int dumpdata();

	//close table, by name
	int closetable(const char *tblname, bangdb_close_type tblclose = DEFAULT);

	//close table, by table itself
	int closetable(table *tbl, bangdb_close_type tblclose = DEFAULT);

	int closetable(wideTable *tbl, bangdb_close_type tblclose = DEFAULT);

	//closes the database, must call in the end
	void closedatabase(bangdb_close_type dbclose = DEFAULT);

	//use with caution, it deletes all the files and the dir in the db dir, useful mostly for test purposes
	void cleanup();

	char *getdbdir();

	int get_table_name_list(char ***list);

	void free_table_name_list(char **list, int nt);

	int get_tran_type();

	char *get_dbmetadata(int *fd);

	table_env *get_table_meta(const char *tablename, bangdb_table_type *_tbl_type);

	//getters
	char* getdbname() { return dbname; }

private:
	//helper function for initial connection withs server and db file handling
	void _initdb();

	table_impl* _gettable(char *tblname, char *idxname, table_item_wrap *_dbtbls, wideTable_item_wrap *_dbwtbls, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL, bangdb_table_type _tbl_type=NORMAL_TABLE, bool checkNewTable = true, bool _from_open_shared_log_tables = false);

	table_impl* _getIndexTable(char *tblname, char *idxname, table_item_wrap *_dbtbls, bangdb_open_type openflag, table_env *tenv);

	wideTable_impl* _getWideTable(char *name, bangdb_open_type openflag, table_env *t_env, bool checkNewTable = true, bool _from_open_shared_log_tables = false);

	table_impl *_getNormalTable(char *name, bangdb_open_type openflag, table_env *t_env, bool checkNewTable = true, bool _from_open_shared_log_tables = false);

	table* _getFixedTable_abs(char *name, bangdb_open_type openflag, table_env *tenv);

	table* _getPrimitiveTable_abs(char *name, bangdb_open_type openflag, table_env *tenv);

	table* _getPrimitiveTableSmall_abs(char *name, bangdb_open_type openflag, table_env *tenv);

	table_impl *_getFixedTable(char *name, bangdb_open_type openflag, table_env *t_env, bool checkNewTable);

	table_impl *_getPrimitiveTable(char *name, bangdb_open_type openflag, table_env *t_env, bool checkNewTable);

	table_impl *_getPrimitiveTableSmall(char *name, bangdb_open_type openflag, table_env *t_env, bool checkNewTable);

	//helper function for creating metadat file, depending upon existence of the db
	int _createdbmeta();

	//verifying the metadata fordb
	int _verifymeta(int fd);

	//write to meta data file the required stuff
	int _writemeta(int fd);

	void _cleanup_table(char *tblname);

	//verify if table already exists, return table if exists else NULL
	table_impl* _tableexists(char *tbl);

	wideTable_impl* _wideTableExists(char *tbl);

	int _create_buffreelist();

	bool _check_for_nullable(void *txn_handle);

	bool _is_enough_mem(table_env *tenv, bool isfirst);

	table_impl *_get_table_impl (ULONG_T table_id);

	wideTable_impl *_get_wideTable_impl(ULONG_T table_id);

	//opens all existing shared log tables
	int _open_shared_log_tables();

	SHORT_T _increase_tbl_id();

	int _close_log();

	static database *_gdb_bangdb_sigh;

	static void _signal_handler(database *_gdb);

	static void sig_int(int signo);

	static void sig_quit(int signo);

	static void sig_segv(int signo);

	static void sig_bus(int signo);

	static void sig_abrt(int signo);

	static void sig_fpe(int signo);

	static void sig_sys(int signo);

	//fd for db metadata file
	int dbmetafd;

	//used for communication with the server exclusively for db only
	int dbsockfd;

	//flag to indicate if we are connecting to remote server
	bool isNETWORK_INMEM_PERSIST;

	//db transaction type
	SHORT_T db_tran_type;

	//name of the database
	char *dbname;

	//name of the user
	char *username;

	//name of the dbdir that bangdb will create in case it already not exists
	char *dbdir;

	//the db log dir
	char *dblogdir;

	char *dblogbasedir;

	//name of the db meta file name
	char *dbmetafile;

	table_env *gtable_env;

	//tables for the db
	//table **dbtbls;
	//hash_tbl<table_item> *dbtbls;
	table_item_wrap *dbtbls;

	//hash_tbl<wideTable_item> *dbwtbls;
	wideTable_item_wrap *dbwtbls;

	//the global free list
	iqfreelist *free_list;

	//this is for shared log tables, db should close this one and not the shared tables, like free_list
	iqlog *log;

	//pointer to the transaction manager, global one
	transaction_manager *tm;

	//to synchronize the operations that db can perform for any process (ex; changing dbs, etc...)
	pthread_mutex_t dbmutex;

	friend class table_impl;

	friend class wideTable_impl;
};
}
#endif /* DATABASE_H_ */
