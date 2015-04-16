/*
 * connection.h
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

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "iqindex.h"
#include "iqbpool.h"
#include "iqlog.h"
#include "transaction_manager.h"
#include "hash_tbl.h"
#include "light_lock.h"
#include "bangdbtxn.h"
//#include "row.h"

namespace bangdb
{

class transaction_manager;
class connection;
class table_impl;
class wideTable_impl;
class bangdb_txn;

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


	connection(char *idxname, INT_T _connid, hash_tbl<connection_item> *_tblconn, int indexfd, int datafd, int dirctfd, iqbpool *bptr, iqlog *flg, transaction_manager *tmgr, SHORT_T openflg, table_env *tenv, SHORT_T _fid);

	int init(bool isfirst);


	int get(const char *key, int keylen, char **val, int *vallen);

	int get(const char *key, int keylen, char **val, int *vallen, bangdb_txn *txn_handle);

	int get(const char *key, int keylen, DATA_VAR *data);

	int get(const char *key, int keylen, DATA_VAR *data, bangdb_txn *txn_handle);

	int get(LONG_T key, DATA_VAR *data);

	int get(LONG_T key, DATA_VAR *data, bangdb_txn *txn_handle);

	char* get(const char *key);

	char* get(const char *key, bangdb_txn *txn_handle);

	FDT* get(FDT *key);

	FDT* get(FDT *key, bangdb_txn *txn_handle);

	FDT *get_data(LONG_T key);


	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag);

	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(const char *key, const char *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(const char *key, const char *val, insert_options flag);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag);

	FILEOFF_T put(LONG_T key, const char *val, insert_options flag);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag, bangdb_txn *txn_handle);


	FILEOFF_T del(const char *key, bangdb_txn *txn_handle);

	FILEOFF_T del(FDT *key, bangdb_txn *txn_handle);

	FILEOFF_T del(LONG_T key, bangdb_txn *txn_handle);

	FILEOFF_T del(const char *key);

	FILEOFF_T del(FDT *key);

	FILEOFF_T del(LONG_T key);

	FILEOFF_T del(int key);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	resultset* scan(int skey, int ekey, scan_filter *sf = NULL);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);


	LONG_T count(const char *skey, const char *key, scan_filter *sf = NULL);

	LONG_T count(FDT *skey, FDT *key, scan_filter *sf = NULL);

	LONG_T count();

	LONG_T count(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	LONG_T count(int skey, int ekey, scan_filter *sf = NULL);


	resultset *read_all_data(resultset *rs, scan_filter *sf);

	resultset *read_all_data_doc(resultset *rs, scan_filter *sf);

	resultset *read_all_data_prebuf(resultset *rs, scan_filter *sf);

	resultset *read_all_data_doc_prebuf(resultset *rs, scan_filter *sf);

	void set_autocommit(bool flag);

	SHORT_T getdbtype();

	SHORT_T getidxtype();

	SHORT_T getidxsize();

	iqindex* getidx();

	char* getindexname();

	ULONG_T get_table_hash_id();

	table_env *get_table_env_ref();

	INT_T getconnid();

	short get_sort_id();

	int closeconnection();

#ifdef BPOOL_DEBUG_MODE
	//test function for deadlock
	void testdeadlock();
#endif

	iqlog *get_log();

	virtual ~connection();


private:
	/***********************************************/
	/*** only used by prim connection **************/
	int get(LONG_T key, LONG_T *val);

	int get(int key, int *val);

	int get_long(FDT *key, LONG_T *val);

	int get_long(const char *key, LONG_T *val);

	FILEOFF_T put(LONG_T key, LONG_T val, insert_options flag);

	FILEOFF_T put(int key, int val, insert_options flag);

	FILEOFF_T put(const char *key, LONG_T val, insert_options flag);

	FILEOFF_T put(FDT *key, LONG_T val, insert_options flag);

	/***********************************************/
	char* _get(const char *key);

	int _get(const char *key, int keylen, DATA_VAR *data);

	int _get(const char *key, int keylen, DATA_VAR *data, bangdb_txn *txn_handle);

	FILEOFF_T _put(const char *key, const char *val, insert_options flag);

	FILEOFF_T _del(const char *key);

	resultset* _scan(const char *skey, const char *ekey, scan_filter *sf);

	FDT* _get(FDT *key);

	FILEOFF_T _put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T _del(FDT *key);

	resultset* _scan(FDT *skey, FDT *ekey, scan_filter *sf);

	resultset* _scan(FDT* skey, FDT* ekey, scan_filter *sf, DATA_VAR *dv);

	bool _check_for_nullable(bangdb_txn *txn_handle);

	bool _check_for_nullable(const char *kv);

	bool _check_for_nullable(FDT* kv);

	bool _check_for_nullable(const char *k, const char *v);

	bool _check_for_nullable(FDT *k, FDT *v);

	void _verify_scan_filter(scan_filter *sf);

	int _init(bool isfirst);

	int _init_idx(bool isfirst);

	int _init_wide(bool isfirst);

	int _init_fixed(bool isfirst);

	//the flag which denotes if the index is being created or opened first time so that accordingly index can be initialized
	SHORT_T openflag;

	SHORT_T idxsz;

	SHORT_T fid;

	bangdb_table_type table_type;

	bool auto_commit;

	//index file descriptor
	int idxfd;

	//data file descriptor
	int datfd;

	//dir file descriptor
	int dirfd;

	ULONG_T table_hash_id;

	INT_T connid;

	hash_tbl<connection_item> *tblconn;

	//name of the index
	char *indexname;

	//index
	iqindex *idx;

	//pointer to bpool
	iqbpool *bp;

	//pointer to flog
	iqlog *fg;

	//pointer to the transaction manager, global one (created by table)
	transaction_manager *tm;

	table_env *tbl_env;

	//lock to ensure only on thread executes the connection's init function
	pthread_mutex_t connlock;

	friend class primConnection;
};
}
#endif /* CONNECTION_H_ */
