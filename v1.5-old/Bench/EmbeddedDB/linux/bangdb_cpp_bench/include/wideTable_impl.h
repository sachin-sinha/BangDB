/*
 * wideTable_impl.h
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

#ifndef WIDETABLE_IMPL_H_
#define WIDETABLE_IMPL_H_

#include "wideConnection.h"
#include "wideConnection_impl.h"
#include "database.h"

namespace bangdb
{

class database;
class wideConnection;
class wideConnection_impl;
struct wideConnection_item_wrap;
struct wideTable_item_wrap;
struct table_item_wrap;
class table_impl;

class wideTable_impl {
public:

	wideTable_impl(database *_db, char *tbl_name, table_item_wrap *_dbtbls, wideTable_item_wrap *_dbwtbls);

	//always crates index with following property BTREE, INMEM_PERSIST, QUASI_LEXICOGRAPH, SORT_ASCENDING, log = off
	int addIndex_str(char *idx_name, int idx_size, bool allowDuplicates);

	int addIndex_num(char *idx_name, bool allowDuplicates);

	//user can define the index/table property
	int addIndex(char *idx_name, table_env *tenv);

	int dropIndex(char *idx_name);

	wideConnection* getWideConnection();

	void setWideConnection(wideConnection_impl * _wconn);

	int closeconnection(wideConnection *conn);

	int closeAllConnections();

	int dumpdata(bool optimistic = true);

	char* getname();

	char* getdbdir();

	char* gettabledir();

	char* getindexfilename();

	char* getdatfilename();

	char* getdirfilename();

	int get_filename_fd_list(filename_fd_list ***fl);

	int getindextype();

	bool verify_table_env(table_env *t_env);

	int closetable(bangdb_close_type tableclose = DEFAULT);

	int setlog(iqlog *_log);

	iqlog *getlog();

	void add_reference();

	int dec_reference();

	void set_forced_close(bool flag);

	FILEOFF_T getnextlsn();

	int get_fid();

	table_item_wrap *get_table_items();

	table_impl *get_main_table();

	virtual ~wideTable_impl();

private:

	int _addindex(char *idx_name, table_env *tenv);

	//hash_tbl<table_item> *dbtbls;
	table_item_wrap *dbtbls;

	//hash_tbl<wideTable_item> *dbwtbls;
	wideTable_item_wrap *dbwtbls;

	wideConnection_item_wrap *wclist;

	table_impl *main_table;

	database *db;

	char *table_name;

	atomic_t ref_count;

	bool _forced_close;

	bool _open_state;

	wideConnection_impl *wconn;

	light_mutex_lock _lock;

	friend class database;
};
}
#endif /* WIDETABLE_IMPL_H_ */
