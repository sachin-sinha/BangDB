/*
 * wideConnection.h
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

#ifndef WIDECONNECTION_IMPL_H_
#define WIDECONNECTION_IMPL_H_

#include "connection.h"
#include "hash_tbl.h"
#include "light_lock.h"
#include "wideTable_impl.h"
#include "timestamp.h"

namespace bangdb
{

class wideTable_impl;
class bangdb_txn;
class connection;

struct wideConnection_item
{
	connection *conn;
	wideConnection_item()
	{
		conn = NULL;
	}

	wideConnection_item(connection *_conn)
	{
		conn = _conn;
	}
};

struct wideConnection_item_wrap
{
	hash_tbl<wideConnection_item> *conn_list;
	light_mutex_lock _lock;
	wideConnection_item_wrap(int size)
	{
		conn_list = new hash_tbl<wideConnection_item>(size);
	}
	void clean(bool flag = true)
	{
		conn_list->clean(flag);
		delete conn_list;
	}
	void clean_items(bool flag = true)
	{
		conn_list->clean_items(flag);
	}
	void begin_iterate()
	{
		conn_list->begin_iterate();
	}
	wideConnection_item *getnext()
	{
		return conn_list->getnext();
	}
	int count()
	{
		return conn_list->count();
	}
	wideConnection_item *find_object(ULONG_T uid)
	{
		return conn_list->find_object(uid);
	}
	int add_object(ULONG_T uid, wideConnection_item *obj)
	{
		return conn_list->add_object(uid, obj);
	}
	wideConnection_item *del_object(ULONG_T uid)
	{
		return conn_list->del_object(uid);
	}
	void lock(bool flag = true)
	{
		_lock.lock();
		if(flag)
			conn_list->lock();
	}
	void unlock(bool flag = true)
	{
		_lock.unlock();
		if(flag)
			conn_list->unlock();
	}
};

class wideConnection_impl {
public:

	wideConnection_impl(wideTable_impl *_wtbl, connection *_main_conn, wideConnection_item_wrap *_conn_list);

	int put(FDT *key, FDT *val, const char* index_name, FDT *index_val);

	int put(LONG_T key, FDT *val, const char* index_name, FDT *index_val);

	resultset *scan(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf);

	resultset *scan(const char *index_name, const char *skey, const char *ekey, scan_filter *sf);

	resultset *scan(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan(const char *index_name, const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf);

	resultset *scan_doc(const char *index_name, const char *skey, const char *ekey, scan_filter *sf);

	resultset *scan_doc(const char *index_name, LONG_T skey, LONG_T ekey, scan_filter *sf);

	int put_doc(const char *key, const char *json_str, insert_options flag);

	int put_doc(LONG_T key, const char *json_str, insert_options flag);

	LONG_T put_doc(const char *json_str);

	resultset *scan_doc(const char *json_filter, int json_filter_len);

	FILEOFF_T count();

	void set_autocommit(bool flag);

	SHORT_T getdbtype();

	SHORT_T getidxtype();

	SHORT_T getidxsize();

	iqindex* getidx();

	char* getindexname();

	ULONG_T get_table_hash_id();

	INT_T getconnid();

	int closeconnection();

	void add_ref();

	int dec_ref();

	void set_forced_close(bool flag = true);

	virtual ~wideConnection_impl();

#ifdef _TEST_WIDE_CONNECTION_

	char* get(const char *key, bangdb_txn *txn_handle);

	FDT* get(FDT *key, bangdb_txn *txn_handle);

	char* get(const char *key);

	FDT* get(FDT *key);

	FDT *get(LONG_T key);

	int get(const char *key, int keylen, DATA_VAR *data);

	int get(const char *key, int keylen, DATA_VAR *data, bangdb_txn *txn_handle);

	int get(LONG_T key, DATA_VAR *data);

	int get(LONG_T key, DATA_VAR *data, bangdb_txn *txn_handle);



	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag);

	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(const char *key, const char *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(LONG_T, LONG_T val, insert_options flag);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag);

	FILEOFF_T put(LONG_T key, const char *val, insert_options flag);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(const char *key, const char *val, insert_options flag);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag, bangdb_txn *txn_handle);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn_handle, scan_filter *sf = NULL);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);


	FILEOFF_T del(const char *key, bangdb_txn *txn_handle);

	FILEOFF_T del(FDT *key, bangdb_txn *txn_handle);

	FILEOFF_T del(LONG_T key, bangdb_txn *txn_handle);

	FILEOFF_T del(FDT *key);

	FILEOFF_T del(const char *key);

	FILEOFF_T del(LONG_T key);

	FILEOFF_T del(int key);


	FILEOFF_T count(const char *skey, const char *key, scan_filter *sf = NULL);

	FILEOFF_T count(FDT *skey, FDT *key, scan_filter *sf = NULL);

	LONG_T count(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	//int get_long(LONG_T key, LONG_T *val);

#endif

private:

	int _numOfKeys(char *nk);

	int _separateKeys(char *nk, char *keys[], int n);

	void _clearKeys(char **keys, int i);

	void _slice_idx(DATA_VAR *dv);

	void _extend_size(DATA_VAR *dv, resultset *rs);

	connection *main_conn;
	//hash_tbl<wideConnection_item> *conn_list;
	wideConnection_item_wrap *conn_list;
	connection **idx_list;
	atomic_t conn_count;
	int nindx;
	wideTable_impl *wtbl;
	bool force_close;
	light_mutex_lock _lock;
};
}
#endif /* WIDECONNECTION_IMPL_H_ */
