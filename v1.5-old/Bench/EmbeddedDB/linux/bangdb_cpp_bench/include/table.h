/*
 * table.h
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

#ifndef TABLE_H_
#define TABLE_H_

#include "table_impl.h"
#include "primConnection.h"

namespace bangdb
{

class primConnection;
class table_impl;

class table
{
public:
	table(table_impl *_tbl);

	connection* getconnection();

	primConnection* getPrimConnection();

	int closeconnection(connection *conn);

	int dumpdata(bool optimistic = true);

	char* getname();

	char* gettabledir();

	char* getindexfilename();

	char* getdatfilename();

	char* getdirfilename();

	int getindextype();

	void set_forced_close(bool flag);

	int closetable(bangdb_close_type tableclose = DEFAULT);

	table_impl *get_table_impl();

#ifdef _BANGDB_SERVER_HDR_

	void printstats();

	bool verify_table_env(table_env *t_env);

	int simple_close();

	int* get_file_fds();

	iqlog *getlog();

	FILEOFF_T getnextlsn();

	//void add_reference();

	//int dec_reference();

#endif

	virtual ~table();
private:
	table_impl *tbl;
};
}
#endif /* TABLE_H_ */
