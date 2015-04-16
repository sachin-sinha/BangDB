/*
 * transaction_manager.h
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

#ifndef TRANSACTION_MANAGER_H_
#define TRANSACTION_MANAGER_H_

#include "txn_node_table.h"

namespace bangdb
{

struct txn_node;
class connection;

class transaction_manager {
public:

	virtual LONG_T init_new_tran() = 0;

	virtual txn_node *get_txn_node(LONG_T unique_id) = 0;

	virtual bool validate_tran(txn_node *tnode) = 0;

	virtual LONG_T commit_tran(txn_node *tnode) = 0;

	virtual void abort_tran(txn_node *tnode) = 0;

	virtual FILEOFF_T update_db(txn_node *tnode) = 0;

	virtual void update_rs(connection *conn, resultset *rs, LONG_T unique_id, FDT *skey, FDT *ekey, scan_filter *sf, short sort_id, short _findPos) = 0;

	virtual int read_val_from_ws(connection* conn, FDT *key, LONG_T unique_id, FDT **val) = 0;

	virtual int read_val_from_ws_dvar(connection* conn, FDT *key, LONG_T unique_id, DATA_VAR *val) = 0;

	virtual void add_key_to_rs(connection* conn, FDT *key, LONG_T unique_id) = 0;

	virtual int add_keyval_to_ws(connection* conn, FDT *key, FDT *val, SHORT_T flag, LONG_T unique_id) = 0;

	virtual int close_transaction_manager() = 0;

	virtual ~transaction_manager() {}
};

}
#endif /* TRANSACTION_MANAGER_H_ */
