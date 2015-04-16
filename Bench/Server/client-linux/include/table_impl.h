/*
 * 	table_impl.h
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

#ifndef TABLE_IMPL_H_
#define TABLE_IMPL_H_

#include "connection.h"
#include "database.h"
#include "primConnection.h"
#include "hash_tbl.h"
namespace bangdb_client
{
class database;

struct connection_item;
struct table_item_wrap;
struct wideTable_item_wrap;
class connection;
class primConnection;
class bangdbEnv;

class table_impl
{
public:

	table_impl(const char *rname, bangdbEnv *_env, table_item_wrap *_dbtbls, wideTable_item_wrap *_dbwtbls, table_env *tenv, db_transaction_type transaction_type);

	connection* getconnection();

	primConnection* getPrimConnection();

	//this just kills the conn object, hence handled at the table_impl level itself, no network/proxy stuff
	int closeconnection(connection *conn);

	int dumpdata();

	char* getname();

	int getindextype();

	void printstats();

	int closetable(bangdb_close_type tableclose);

	int simple_close();

	void add_reference();

	int dec_reference();

	bangdbEnv *getBangDBEnv();

	~table_impl();

	enum store
	{
		INSERT,
		UPDATE
	};

private:
	connection* _getconnection(bangdb_table_type _tbl_type);
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
	hash_tbl<connection_item> *tblconn;
	ULONG_T tid;
	friend class database;
	friend class wideTable_impl;
};
}
#endif /* TABLE_IMPL_H_ */
