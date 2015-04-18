/*
 * bangdbtxn.h
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

#ifndef BANGDBTXN_H_
#define BANGDBTXN_H_

#include "database.h"
#include "light_lock.h"
namespace bangdb_client
{
#ifndef _BANGDB_SERVER_CLIENT_
#define _BANGDB_SERVER_CLIENT_
#endif

class database;
class connection;

class bangdb_txn {
public:
	bangdb_txn();
	bool is_active();
#ifdef _BANGDB_SERVER_CLIENT_
	LONG_T get_unique_id();
	int getsockfd();
	void setsockfd(int _sfd);
	void set_unique_id(LONG_T id);
	void lock();
	void unlock();
	void close();
	void reset();
#endif
	virtual ~bangdb_txn();
private:
#ifndef _BANGDB_SERVER_CLIENT_
	LONG_T get_unique_id();
	void set_unique_id(LONG_T id);
	void reset();
	friend class database;
	friend class connection;
#endif
	LONG_T uid;
#ifdef _BANGDB_SERVER_CLIENT_
	int sfd;
	light_mutex_lock _lock;
#endif
};
}
#endif /* BANGDBTXN_H_ */
