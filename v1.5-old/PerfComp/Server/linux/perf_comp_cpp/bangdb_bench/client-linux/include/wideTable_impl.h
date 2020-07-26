/*
 * wideTableimpl.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb-client library
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

#ifndef WIDETABLEIMPL_H_
#define WIDETABLEIMPL_H_

#include "wideConnection.h"
#include "database.h"
namespace bangdb_client
{
class database;
class wideConnection;
struct wideConnection_item;
struct table_item_wrap;
struct wideTable_item_wrap;
struct wideConnection_item_wrap;
class bangdbEnv;

class wideTable_impl {
public:
	wideTable_impl(const char *rname, bangdbEnv *_env, table_item_wrap *_dbtbls, wideTable_item_wrap *_dbwtbls, table_env *tenv, db_transaction_type transaction_type);

	//always crates index with following property BTREE, INMEM_PERSIST, QUASI_LEXICOGRAPH, SORT_ASCENDING, log = off
	int addIndex_str(char *idx_name, int idx_size, bool allowDuplicates);

	int addIndex_num(char *idx_name, bool allowDuplicates);

	//user can define the index/table property
	int addIndex(char *idx_name, table_env *tenv);

	int dropIndex(char *idx_name);

	wideConnection* getWideConnection(bool runAtServer);

	int closeconnection(wideConnection *conn);

	int closeAllConnections(bool runAtServer);

	int dumpdata(bool optimistic = true);

	char* getname();

	int getindextype();

	int closetable(bangdb_close_type tableclose);

	void add_reference();

	int dec_reference();

	bangdbEnv *getBangDBEnv();

	virtual ~wideTable_impl();

private:
	int _addIndex(char *idx_name, table_env *tenv, int idxType);
	char *tablename;
	bangdbEnv *env;
	table_env *te;
	atomic_t ref_count;
	atomic_t connid;
	db_transaction_type tran_type;
	pthread_mutex_t tbllock;
	table_item_wrap *dbtbls;
	//hash_tbl<wideTable_item> *dbwtbls;
	wideTable_item_wrap *dbwtbls;
	hash_tbl<wideConnection_item> *tblconn;
	ULONG_T tid;
	friend class database;
};
}
#endif /* WIDETABLEIMPL_H_ */
