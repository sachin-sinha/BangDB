/*
 * 	connection.h
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

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "bangdbproxy.h"
#include "hash_tbl.h"
#include "bangdbtxn.h"
namespace bangdb_client
{
class connection;
class table_impl;
class wideTable_impl;
class bangdb_txn;

/*
class connection;
class table_impl;
class wideTable_impl;
*/
struct connection_item
{
	connection *conn;
	connection_item()
	{
		conn = NULL;
	}
	connection_item(connection *_conn)
	{
		conn = _conn;
	}
};

struct table_item
{
	table_impl *tbl;
	SHORT_T fid;
	table_item()
	{
		tbl = NULL;
		fid = 0;
	}
	table_item(table_impl *_tbl, SHORT_T _fid)
	{
		tbl = _tbl;
		fid = _fid;
	}
};

struct table_item_wrap
{
	hash_tbl<table_item> *dbtbls;
	light_mutex_lock _lock;
	table_item_wrap(int size)
	{
		dbtbls = new hash_tbl<table_item>(size);
	}
	void clean(bool flag = true)
	{
		dbtbls->clean(flag);
		delete dbtbls;
	}
	void begin_iterate()
	{
		dbtbls->begin_iterate();
	}
	table_item *getnext()
	{
		return dbtbls->getnext();
	}
	int count()
	{
		return dbtbls->count();
	}
	table_item *find_object(ULONG_T uid)
	{
		return dbtbls->find_object(uid);
	}
	int add_object(ULONG_T uid, table_item *obj)
	{
		return dbtbls->add_object(uid, obj);
	}
	table_item *del_object(ULONG_T uid)
	{
		return dbtbls->del_object(uid);
	}
	void lock(bool flag = true)
	{
		_lock.lock();
		if(flag)
			dbtbls->lock();
	}
	void unlock(bool flag = true)
	{
		_lock.unlock();
		if(flag)
			dbtbls->unlock();
	}
};

struct wideTable_item
{
	wideTable_impl *wtbl;
	wideTable_item()
	{
		wtbl = NULL;
	}
	wideTable_item(wideTable_impl *_wtbl)
	{
		wtbl = _wtbl;
	}
};

struct wideTable_item_wrap
{
	hash_tbl<wideTable_item> *dbtbls;
	light_mutex_lock _lock;
	wideTable_item_wrap(int size)
	{
		dbtbls = new hash_tbl<wideTable_item>(size);
	}
	void clean(bool flag = true)
	{
		dbtbls->clean(flag);
		delete dbtbls;
	}
	void begin_iterate()
	{
		dbtbls->begin_iterate();
	}
	wideTable_item *getnext()
	{
		return dbtbls->getnext();
	}
	int count()
	{
		return dbtbls->count();
	}
	wideTable_item *find_object(ULONG_T uid)
	{
		return dbtbls->find_object(uid);
	}
	int add_object(ULONG_T uid, wideTable_item *obj)
	{
		return dbtbls->add_object(uid, obj);
	}
	wideTable_item *del_object(ULONG_T uid)
	{
		return dbtbls->del_object(uid);
	}
	void lock(bool flag = true)
	{
		_lock.lock();
		if(flag)
			dbtbls->lock();
	}
	void unlock(bool flag = true)
	{
		_lock.unlock();
		if(flag)
			dbtbls->unlock();
	}
};

class connection
{
public:

	connection(const char *host, const char *port, INT_T _connid, hash_tbl<connection_item> *_tblconn, db_transaction_type transaction_type, table_env *tenv, ULONG_T tableid);

	void init(int sfd);

	int get(const char *key, int keylen, char **val, int *vallen);

	int get(const char *key, int keylen, char **val, int *vallen, bangdb_txn *txn);

	int get(const char *key, int keylen, DATA_VAR *data);

	int get(const char *key, int keylen, DATA_VAR *data, bangdb_txn *txn);

	int get(LONG_T key, DATA_VAR *data);

	int get(LONG_T key, DATA_VAR *data, bangdb_txn *txn);

	char* get(const char *key);

	char* get(const char *key, bangdb_txn *txn);

	FDT* get(FDT *key);

	FDT* get(FDT *key, bangdb_txn *txn);

	FDT *get_data(LONG_T key);


	int put(const char *key, int keylen, DATA_VAR *val, insert_options flag);

	int put(const char *key, int keylen, DATA_VAR *val, insert_options flag, bangdb_txn *txn);

	int put(const char *key, const char *val, insert_options flag, bangdb_txn *txn);

	int put(FDT *key, FDT *val, insert_options flag, bangdb_txn *txn);

	int put(const char *key, const char *val, insert_options flag);

	int put(FDT *key, FDT *val, insert_options flag);

	int put(LONG_T key, FDT *val, insert_options flag);

	int put(LONG_T key, const char *val, insert_options flag);

	int put(LONG_T key, FDT *val, insert_options flag, bangdb_txn *txn);


	int del(const char *key, bangdb_txn *txn);

	int del(FDT *key, bangdb_txn *txn);

	int del(LONG_T key, bangdb_txn *txn);

	int del(const char *key);

	int del(FDT *key);

	int del(LONG_T key);

	int del(const int key);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn, scan_filter *sf = NULL);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	resultset* scan(int skey, int ekey, scan_filter *sf = NULL);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);


	LONG_T count(const char *skey, const char *key, scan_filter *sf = NULL);

	LONG_T count(FDT *skey, FDT *key, scan_filter *sf = NULL);

	LONG_T count();

	LONG_T count(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	LONG_T count(int skey, int ekey, scan_filter *sf = NULL);


	void set_autocommit(bool flag);

	SHORT_T getdbtype();

	SHORT_T getidxtype();

	int closeconnection();

	int getsocketfd();

	INT_T getconnid();

	void setsocketfd(int _socketfd);

	int make_simple_call();

#ifdef BPOOL_DEBUG_MODE
	void testdeadlock();
#endif

	~connection();

private:

	/***********************************************/
	/*** only used by prim connection **************/
	int get(LONG_T key, LONG_T *val);

	int get(int key, int *val);

	int get_long(FDT *key, LONG_T *val);

	int get_long(const char *key, LONG_T *val);

	int put(LONG_T key, LONG_T val, insert_options flag);

	int put(int key, int val, insert_options flag);

	int put(const char *key, LONG_T val, insert_options flag);

	int put(FDT *key, LONG_T val, insert_options flag);

	resultset* _scan(FDT *skey, FDT *ekey, int subType, DATA_VAR *dv, bangdb_txn *txn, scan_filter *sf);

	resultset* _scan(FDT *skey, FDT *ekey, int subType, DATA_VAR *dv, scan_filter *sf);

	FILEOFF_T _count(FDT *skey, FDT *ekey, int subType, scan_filter *sf);

	bool _verify_tran_sanity();

	bool _check_for_nullable(bangdb_txn *txn);

	bool _check_for_nullable(const char *kv);

	bool _check_for_nullable(FDT* kv);

	bool _check_for_nullable(const char *k, const char *v);

	bool _check_for_nullable(FDT *k, FDT *v);

	void _verify_scan_filter(scan_filter *sf);

	char *hostname;

	char *portnum;

	int socketfd;

	char *recvbuf;

	table_env *te;

	bool conn_state;

	bool auto_commit;

	short keysz;

	db_transaction_type tran_type;

	INT_T connid;

	hash_tbl<connection_item> *tblconn;

	ULONG_T tid;

	friend class primConnection;
};
}
#endif /* CONNECTION_H_ */
