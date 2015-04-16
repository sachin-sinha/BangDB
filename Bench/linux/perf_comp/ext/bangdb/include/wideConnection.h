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

#ifndef WIDECONNECTION_H_
#define WIDECONNECTION_H_

#include "wideConnection_impl.h"

namespace bangdb
{

class wideConnection_impl;
class bangdb_txn;

class wideConnection {
public:
	wideConnection(wideConnection_impl *_wconn);

	int put(FDT *key, FDT *val, const char* index_name, FDT *index_val);

	int put(LONG_T key, FDT *val, const char* index_name, FDT *index_val);

	resultset *scan(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf);

	resultset *scan(const char *index_name, const char *skey, const char *ekey, scan_filter *sf);

	resultset *scan(const char *index_name, const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset *scan_doc(const char *index_name, FDT *skey, FDT *ekey, scan_filter *sf);

	resultset *scan_doc(const char *index_name, const char *skey, const char *ekey, scan_filter *sf);

	resultset *scan_doc(const char *index_name, LONG_T skey, LONG_T ekey, scan_filter *sf);

	resultset *scan_doc(const char *json_filter, int json_filter_len);

	//inserts a json doc with a key provided by the user, hence the insert_options flag as well
	int put_doc(const char *key, const char *json_str, insert_options flag);

	int put_doc(LONG_T key, const char *json_str, insert_options flag);

	//the db will create uniqie id(ts) and use it as key to store doc, will return id or -1 for error
	LONG_T put_doc(const char *json_str);

	int put_line(const char *line);

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

	virtual ~wideConnection();

#ifdef _TEST_WIDE_CONNECTION_
	/* begin - needed for test, we may switch off for release */

	char* get(const char *key);

	char* get(const char *key, bangdb_txn *txn_handle);

	FDT* get(FDT *key, bangdb_txn *txn_handle);

	FDT* get(FDT *key);

	FDT *get(LONG_T key);

	int get(const char *key, int keylen, DATA_VAR *data);

	int get(const char *key, int keylen, DATA_VAR *data, bangdb_txn *txn_handle);

	int get(LONG_T key, DATA_VAR *data);

	int get(LONG_T key, DATA_VAR *data, bangdb_txn *txn_handle);

	//int get_long(LONG_T key, LONG_T *val);

	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag);

	FILEOFF_T put(const char *key, int keylen, DATA_VAR *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(const char *key, const char *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag);

	FILEOFF_T put(LONG_T key, const char *val, insert_options flag);

	FILEOFF_T put(const char *key, const char *val, insert_options flag);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag, bangdb_txn *txn_handle);

	FILEOFF_T put(LONG_T key, FDT *val, insert_options flag, bangdb_txn *txn_handle);

	//FILEOFF_T put(LONG_T key, LONG_T val, insert_options flag);


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


	resultset* scan(const char *skey, const char *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, bangdb_txn *txn_handle, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf, DATA_VAR *dv);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf, DATA_VAR *dv);


	FILEOFF_T count(const char *skey, const char *key, scan_filter *sf = NULL);

	FILEOFF_T count(FDT *skey, FDT *key, scan_filter *sf = NULL);

	LONG_T count(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

#endif


private:
	wideConnection_impl *wconn;
};
}
#endif /* WIDECONNECTION_H_ */
