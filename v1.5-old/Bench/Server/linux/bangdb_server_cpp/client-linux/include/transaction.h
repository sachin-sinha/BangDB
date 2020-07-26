/*
 * transaction.h
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

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include "bangdb-client.h"
namespace bangdb_client
{
//class transaction;

class transaction_context
{
private:
	transaction_context(int _sfd);

	int getsocketfd();

	void setsockfd(int _sfd);

	void lock();

	void unlock();

	void close_context();

	int sfd;

	pthread_mutex_t _lock;

	friend class database;

	friend class transaction;
};

//simple wrapper for unique id, helpful in identifying transaction (also in network case)
class transaction {
public:
	transaction(transaction_context *tcontext);

	transaction(LONG_T _unique_id, transaction_context *tcontext);

	LONG_T get_unique_id();

	void set_unique_id(LONG_T _uid);

	int getsockfd();

	void setsockfd(int sfd);

	void lock();

	void unlock();

private:

	LONG_T txn_unique_id;

	transaction_context *tc;
};
}
#endif /* TRANSACTION_H_ */
