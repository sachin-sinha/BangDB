/*
 * table_impl.h
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

#ifndef TABLE_IMPL_H_
#define TABLE_IMPL_H_

#include "connection.h"
#include "iqfreelist.h"
#include "database.h"
#include "primConnection.h"

namespace bangdb
{

class database;
struct table_item_wrap;
struct wideTable_item_wrap;
struct connection_item;
class primConnection;
class transaction_manager;
class connection;

class table_impl
{
public:

	table_impl(database *db, char * _dbdir, char *_dblogdir, char *tbl_name, char *idx_name, table_item_wrap *_dbtbls, wideTable_item_wrap *_dbwtbls, SHORT_T openflg, transaction_manager *_tm, table_env *tenv, bangdb_table_type _tbl_type);

	//initialization of the table_impl, should be called only thru database
	int init(bool newTable, iqfreelist *free_list, iqlog **_log, table_env *gtable_env, bool _from_open_shared_log_tables = false);

	connection* getconnection();

	primConnection* getPrimConnection();

	int closeconnection(connection *conn);

	int dumpdata(bool optimistic = true);

	char* getname();

	char* getdbdir();

	char* gettabledir();

	char* getindexfilename();

	char* getdatfilename();

	char* getdirfilename();

	int get_filename_fd_list(filename_fd_list ***fl, bool doprint = true);

	int getpersisttype();

	int getindextype();

	bangdb_table_type getTableType();

	void printstats();

	int closetable(bangdb_close_type tableclose = DEFAULT);

	bool verify_table_env(table_env *t_env);

	int simple_close();

	int* get_file_fds();

	void setlog(iqlog *_log);

	iqlog *getlog();

	FILEOFF_T getnextlsn();

	void add_reference();

	int dec_reference();

	table_env *get_table_env();

	void set_forced_close(bool flag);

	int get_fid();

	~table_impl();


private:
	int _getlines(int fd);
	int _verifymeta(int fd, bool dontcheck = false);
	void _getfilenames(char* dbdir, char *tbl_name);
	int _remove_idx_files(char *fname);
	int _writemeta(int fd, int num_idx);
	void _setparams();
	int _settablemeta();
	void _cleanup();
	int _create_files(bool lock = true);
	int _close_embedd();
	int _close_inmemr(bool dump);
	int _close_inmemd();
	int _close_inmemd_clean();
	int _append_index_metadata(char *idxname, table_env *t_env);
	int _remove_index_metadata(char *idxName);
	int _get_index_list(table_index_meta ***tim);
	void _free_index_list(table_index_meta **tim, int n);

	int idxfd;
	int datfd;
	int dirfd;
	int metfd;
	atomic_t ref_count;
	atomic_t num_indices;
	SHORT_T fid;
	bangdb_table_type table_type;

	char *dbdir;
	char *dblogtbldir;
	char *dblogtbldir_private;
	char *tabledir;
	char *tablename;
	char *indexname;
	char *indexfilename;
	char *datafilename;
	char *dirfilename;
	char *metadatafilename;
	char **filenames;
	bool inmemrfilesexist;
	bool conn_init;
	bool _forced_close;

	//hash_tbl<table_item> *dbtbls;
	table_item_wrap *dbtbls;
	//hash_tbl<wideTable_item> *dbwtbls;
	wideTable_item_wrap *dbwtbls;
	hash_tbl<connection_item> *tblconn;

	SHORT_T openflag;
	SHORT_T logstatus;
	SHORT_T dbclose;
	SHORT_T nusers;
	atomic_t connid;
	INT_T bpsz[3];
	int filefd[4];
	iqbpool *bp;
	iqlog *fg;
	transaction_manager *tm;
	table_env *tbl_env;
	database *dbase;
	pthread_mutex_t tbllock;
	friend class database;
	friend class wideTable_impl;
};
}
#endif /* TABLE_IMPL_H_ */
