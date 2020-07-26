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

#ifndef BANGDBPROXY_H_
#define BANGDBPROXY_H_

#include "resultset.h"
#include "bangdbtxn.h"
#include "bangdb-client.h"
#include "tableenv.h"
#include "bangdbEnv.h"
namespace bangdb_client
{
class bangdb_txn;

struct scan_hdr
{
	int count;
	int data_size;
	int dat_buf_len;	//length of data (or alloc mem size)
	int skip_count;
	short table_type;
	short sort_id;
	short last_evk_len;	//this tells if levk is present or not
	short skey_op;	//default GTE
	short ekey_op;	//default LTE
	bool moreToCome;
	bool copy_levk;		//this helps in clearing the levk, just set in fmap that's all

	char x1[3];	//for mem alignment
	bool sortflag;

	scan_hdr()
	{
		//memset(this, 0, sizeof(*this));
		reset();
	}

	void reset()
	{
		count = 0;
		data_size = 0;
		dat_buf_len = 0;
		table_type = 0;
		sort_id = 0;
		last_evk_len = 0;
		moreToCome = false;
		copy_levk = false;
		sortflag = false;

		skey_op = GTE;
		ekey_op = LTE;
		skip_count = 0;

		memset(x1, 0, 3);
	}

	void set(resultset *rs, int _dat_buf_len, scan_filter *sf)
	{
		count = rs->count();
		data_size = rs->dataSize();
		dat_buf_len = _dat_buf_len;
		table_type = rs->getmap()->get_table_type();
		sort_id = rs->getmap()->get_sort_id();
		last_evk_len = 0;
		moreToCome = rs->moreDataToCome();
		copy_levk = rs->getmap()->get_copy_levk();
		sortflag = rs->getmap()->get_sort_flag();

		if(sf)
		{
			skey_op = sf->skey_op;
			ekey_op = sf->ekey_op;
			skip_count = sf->skip_count;
		}
	}
};

const int SCAN_HDR_SZ = sizeof(scan_hdr);

struct bangdb_db_description
{
	char name[MINLINE];
	table_env tenv;
	bangdb_db_description()
	{

	}
	void set_desc(char *dbname, int len, table_env_hdr *teh)
	{
		memcpy(name, dbname, len);
		name[len] = 0;
		teh->setFromHDr(&tenv);
	}

	void set_name(char *dbname, int len)
	{
		memcpy(name, dbname, len);
		name[len] = 0;
	}

	void set_table_env(table_env_hdr *teh)
	{
		teh->setFromHDr(&tenv);
	}
};
/*
 * The proxy calls the functions on behalf of connections and returns the values. It also returns the errno properly set
 */
class bangdbproxy {
public:

	static int createdatabase(int sfd, char *name, db_transaction_type transaction_type, bool retry);

	static int verifydatabase(int sfd, char *name, db_transaction_type transaction_type, bool retry);

	static int createtable(int sfd, char *name, SHORT_T openflag, table_env *tenv, bangdb_primitive_data_type dataType, int *fid, bool retry);

	static int opentable(int sfd, char *name, SHORT_T openflag, bangdb_primitive_data_type dataType, int *fid, bool retry);

	static int verifytable(int sfd, char *name, SHORT_T openflag, table_env *tenv, int *fid, bool retry);

	static int closedatabase(int sfd, bangdb_close_type dbclose, bool retry);

	static int closetable(int sfd, ULONG_T tid, bangdb_close_type dbclose, bool retry);

	static int droptable(int sfd, char *tablename, bool retry);

	static int getSockConnection(char *host, char *port);

	static int getConnection(int sfd, char *host, char *port, ULONG_T tid, bangdb_table_type _tbl_type);

	static int closeSockConnection(int sfd);

	static int closeConnection(int sfd, ULONG_T tid, bangdb_table_type _tbl_type);

	static int dumpdata(int sfd, bool retry);

	static int dumptabledata(int sfd, ULONG_T tid, bool retry);

	static int get(int sfd, FDT *key, FDT **val, char *recvbuf, ULONG_T tid, int subType, DATA_VAR *dv, bool retry);

	static int get(int sfd, LONG_T key, LONG_T *val, char *recvbuf, ULONG_T tid, bool retry);

	static int get(int sfd, FDT *key, LONG_T *val, char *recvbuf, ULONG_T tid, bool retry);

	static int put(int sfd, FDT *key, FDT *val, insert_options flag, ULONG_T tid, int subType, bool retry);

	static int put(int sfd, FDT *key, FDT *val, char *idxName, FDT *idxVal, ULONG_T tid, int subType, bool retry);

	static int put(int sfd, char *json_str, insert_options flag, ULONG_T tid, bool retry);

	static int del(int sfd, FDT *key, ULONG_T tid, int subType, bool retry);

	static resultset* scan(int sfd, FDT *skey, FDT *ekey, scan_filter *sf, char *recvbuf, ULONG_T tid, int subType, DATA_VAR *dv, int *errocde, bool _allow_duplicate, bool retry);

	static resultset* scan(int sfd, char *idxName, FDT *skey, FDT *ekey, scan_filter *sf, char *recvbuf, ULONG_T tid, int subType, DATA_VAR *dv, int *errocde, bool _allow_duplicate, bool retry);

	static int get(int sfd, FDT *key, FDT **val, bangdb_txn *txn, char *recvbuf, ULONG_T tid, int subType, DATA_VAR *dv, bool retry);

	static int put(int sfd, FDT *key, FDT *val, insert_options flag, bangdb_txn *txn, ULONG_T tid, int subType, bool retry);

	static int del(int sfd, FDT *key, bangdb_txn *txn, ULONG_T tid, int subType, bool retry);

	static resultset* scan(int sfd, FDT *skey, FDT *ekey, bangdb_txn *txn, scan_filter *sf, char *recvbuf, ULONG_T tid,  int subType, DATA_VAR *dv, int *errocde, bool _allow_duplicate, bool retry);

	static FILEOFF_T count(int sfd, FDT *skey, FDT *ekey, scan_filter *sf, char *recvbuf, ULONG_T tid, int subType, bool retry);

	static int begin_transaction(bangdb_txn *txn, bool retry);

	static LONG_T commit_transaction(bangdb_txn *txn, bool retry);

	static int abort_transaction(bangdb_txn *txn, bool retry);

	static int set_autocommit(int sfd, bool flag, ULONG_T tid, bool retry);

	static SHORT_T getdbtype();

	static SHORT_T getidxtype(ULONG_T tid);

	static table_env *describe_table(int sfd, char *tblname, int *errcode, bool retry);

	static int describe_database(int sfd, char *recvbuf, bangdb_db_description **dbdes, int *errcode, bool retry);

	static int add_index(int sfd, char *idx_name, table_env *tenv, ULONG_T table_id, int subType, int idxType, bool retry);

	static int drop_index(int sfd, char *idx_name, ULONG_T table_id, bool retry);

	/* analytics helpers */
	static int create_swtable(int sfd, char *name, table_env *tenv, int ttlsec, bool archive, int *fid, bool retry);

	static int create_swEntityCount(int sfd, char *name, int swTime, int swExpiry, int nEntity, bool retry);

	static int create_swEntity(int sfd, char *name, int len, bangdb_window_type swType, bangdb_count_type countType, ULONG_T tid, bool retry);

	static int remove_entity(int sfd, char *name, int len, ULONG_T tid, bool retry);

	static int create_topk(int sfd, char *topkName, int swSizeSec, int k, bool desc, char *uniqueBy, bool retry);

	static int init_sw(int sfd, ULONG_T tid, int subType, bool retry);

	static int close_sw(int sfd, ULONG_T tid, int subType, bool retry);

	static int sw_put(int sfd, char *key, int len, insert_options flag, ULONG_T tid, bool retry);

	static int sw_put_idx(int sfd, char *str, int slen, char *idxName, int idxNamelen, char *idxkey, int idxkeylen, insert_options flag, ULONG_T tid, bool retry);

	static int sw_scan(int sfd, int period, int lag, char *recvbuf, resultset **result, ULONG_T from_time, ULONG_T tid, int subType, bool retry);

	static int sw_entity_add(int sfd, char *ename, int elen, char *s, int l, ULONG_T tid, bool retry);

	static int sw_entity_add_create(int sfd, char *ename, int elen, char *s, int l, bangdb_window_type swType, bangdb_count_type countType, ULONG_T tid, bool retry);

	static LONG_T sw_entity_count(int sfd, char *name, int span, ULONG_T tid, int subType, bool retry);

	static int sw_entity_count_list(int sfd, char *recvbuf, char **result, ULONG_T tid, int subType, bool retry);

	static int topk_put(int sfd, long score, char *data, int datalen, char *uniqueParam, int paramlen, ULONG_T tid, bool retry);

	static int topk_get(int sfd, int k, char *recvbuf, void **result, ULONG_T tid, int subType, bool retry);

	//dummy call which makes with invalid optype, this is to measure the server performance only for network case
	static int make_dummy_call(int sfd);

	static int print_error_present(int ecode);

	static bool isErrorCodeEqual(int err, int flag);

	static int getFlagFromErrorCode(int err);

private:

	static resultset* _format_scan_msg_buf(char *mbuf, bool _pre_alloc_buf, DATA_VAR *dv, scan_filter *sf, bool _allow_duplicate);
	static resultset* _format_scan_msg_dynamic(char *mbuf, int buflen, bool _pre_alloc_buf, DATA_VAR *dv, scan_filter *sf, bool _allow_duplicate);
	static int _format_db_description(char *recvbuf, int ntbl, bangdb_db_description **desdb);
	static int _parse_error_code(int err, int succ_code, int err_code);
	static void Memcpy(char **dest, char *src, int srclen);
	static bool _isLongScanSubType(int subType);
	static bool _isLongCountSubType(int subType);
};
}
#endif /* BANGDBPROXY_H_ */
