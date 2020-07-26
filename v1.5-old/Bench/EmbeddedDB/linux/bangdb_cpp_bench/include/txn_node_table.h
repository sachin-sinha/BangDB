/*
 * txn_node_table.h
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

#ifndef TXN_NODE_TABLE_H_
#define TXN_NODE_TABLE_H_

#include "connection.h"

namespace bangdb
{

class connection;

//for active list clone, it contains the keys for wset only for active list
struct active_node
{
	connection *conn;
	FDT *key;
	active_node *next;

	void clean();

	void copy(FDT *k, connection *_conn);
	active_node(FDT *_key, connection *_conn);
	active_node();
};

struct rw_set
{
	SHORT_T optype;
	ULONG_T table_hash_id;
	connection *conn;
	FDT *key;
	FDT *val;
	rw_set *next;

	rw_set();

	rw_set(SHORT_T _optype, FDT *_key, FDT *_val, rw_set *_next, connection *_conn);

	void clean();
};

struct txn_node
{
	LONG_T tid;
	LONG_T start_tn;
	rw_set *rs;
	rw_set *ws;
	txn_node *list_next;
	txn_node *list_prev;
	txn_node *table_next;
	txn_node *table_prev;

	void init(LONG_T id = -1);

	void clean_rw_set(rw_set *_set);
};

const int TXN_ACTIVE_NODE_SZ = sizeof(active_node);
const int TXN_RW_SET_SZ = sizeof(rw_set);
const int TXN_NODE_SZ = sizeof(txn_node);


class txn_node_table {
public:
	txn_node_table(int _table_size, LONG_T minmax_id);

	void add_to_table(txn_node *tn);

	txn_node *get_from_table(LONG_T id);

	void remove_from_table(txn_node *tn);

	txn_node *remove_from_table(LONG_T id);

	void add_to_list(txn_node *tn);

	void remove_from_list(txn_node *tn);

	txn_node *get_list();

	active_node *clone_active_list();

	void free_clone_active_list(active_node *active_set);

	void add_to_table_and_list(txn_node *tn);

	void remove_from_table_and_list(txn_node *tn);

	void remove_from_table_and_list(LONG_T id);

	void lock_table();

	void unlock_table();

	void lock_list();

	void unlock_list();

	void lock_table_read();

	void lock_table_write();

	void unlock_table_rw();

	int get_num_list_items();

	LONG_T get_max_id();

	int close_table_list();

	virtual ~txn_node_table();

private:
	ULONG_T _hashid(LONG_T id);

	void _init_table();

	void _clean_list();

	void _set_max_id(LONG_T id);

	void _init_max_id(LONG_T id);

	void _print_err_msg(char *str, txn_node *tn);

	#define _get_txn_tbl_slot(bnum)			((txn_node*)(_tbl->getslot((_hashid(bnum)%table_size))))

	int table_size;

	int nitems_list;

	char *table_buf;

	int buf_size;

	atomic_FILEOFF_T max_id;

	membuf *_tbl;

	txn_node *_list;

	pthread_mutex_t _table_lock;

	pthread_mutex_t _list_lock;

	pthread_rwlock_t _rwlock;
};
}
#endif /* TXN_NODE_TABLE_H_ */
