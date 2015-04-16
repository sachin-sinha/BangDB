/*
 * primConnection.h
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

#ifndef PRIMCONNECTION_H_
#define PRIMCONNECTION_H_

#include "connection.h"

namespace bangdb
{

class connection;

class primConnection {
public:
	primConnection(connection *_conn);

	int get(LONG_T key, LONG_T *val);

	int get(int key, int *val);

	int get(FDT *key, LONG_T *val);

	int get(const char *key, LONG_T *val);

	FILEOFF_T put(LONG_T key, LONG_T val, insert_options flag);

	FILEOFF_T put(int key, int val, insert_options flag);

	FILEOFF_T put(const char *key, LONG_T val, insert_options flag);

	FILEOFF_T put(FDT *key, LONG_T val, insert_options flag);

	FILEOFF_T del(const char *key);

	FILEOFF_T del(FDT *key);

	FILEOFF_T del(LONG_T key);

	FILEOFF_T del(int key);

	resultset* scan(const char *skey, const char *ekey, scan_filter *sf = NULL);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	resultset* scan(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	resultset* scan(int skey, int ekey, scan_filter *sf = NULL);

	LONG_T count(const char *skey, const char *ekey, scan_filter *sf = NULL);

	LONG_T count(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	LONG_T count();

	LONG_T count(LONG_T skey, LONG_T ekey, scan_filter *sf = NULL);

	LONG_T count(int skey, int ekey, scan_filter *sf = NULL);

	void set_autocommit(bool flag);

	SHORT_T getdbtype();

	SHORT_T getidxtype();

	SHORT_T getidxsize();

	iqindex* getidx();

	char* getindexname();

	ULONG_T get_table_hash_id();

	INT_T getconnid();

	int closeconnection();

	virtual ~primConnection();

private:
	connection *conn;
};
}
#endif /* PRIMCONNECTION_H_ */
