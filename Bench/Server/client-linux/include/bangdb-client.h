/*
 * 	bangdb-client.h
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

#ifndef BANGDB_CLIENT_H_
#define BANGDB_CLIENT_H_

#include "bangdb.h"
namespace bangdb_client
{
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct msg_hdr
{
	short optype;	//the operation type, for return it's filled with the right value which describes success, failure etc for the optype. Need a hash map here
	short info;		//extra info (contextual) that required to be passed, ex; sub optype, datatype, enum values, some count etc...
	int msglen;		//length of the message if required
	FILEOFF_T sync_id;	//could be timestamps, version, sync id, txn id etc...
	ULONG_T tid;	//table id
	msg_hdr()
	{ reset(); }
	void reset()
	{
		optype = info = msglen = sync_id = -1; tid = 0;
	}
};
const int MSG_HDR_SZ = sizeof(msg_hdr);

struct msg_body
{
	int len1;
	int len2;
};

const int MSG_BODY_SZ = sizeof(msg_body);

struct bangdb_msg_data
{
	int len;
};

const int BANGDB_MSG_DATA = sizeof(bangdb_msg_data);

struct table_env_hdr
{
	short db_type;
	short idx_type;
	short key_sz;
	short table_sz_hint;
	short log_sz_mb;
	short table_log_type;
	short table_type;
	short sort_method;
	short sort_direction;
	short key_type;
	short sort_id;
	short prim_data_type;
	short table_subtype;
	bool wal_enabled;
	bool autocommit;
	bool allow_duplicate;

	void setHdr(table_env *tenv)
	{
		db_type = tenv->get_persist_type();
		idx_type = tenv->get_idx_type();
		key_sz = tenv->get_key_size_byte();
		table_sz_hint = tenv->get_table_size_hint();
		log_sz_mb = tenv->get_log_size_mb();
		table_log_type = tenv->get_log_type();
		table_type = tenv->get_table_type();
		wal_enabled = tenv->get_log_state();
		autocommit = tenv->get_autocommit_state();
		sort_method = tenv->get_sort_method();
		sort_direction = tenv->get_sort_direction();
		key_type = tenv->get_key_type();
		sort_id = tenv->get_sort_id();
		prim_data_type = tenv->get_primitive_data_type();
		table_subtype = tenv->get_table_subtype();
		allow_duplicate = tenv->get_allow_duplicate();
	}

	void setFromHDr(table_env *tenv)
	{
		tenv->set_persist_type(db_type);
		tenv->set_idx_type(idx_type);
		tenv->set_key_size_byte(key_sz);
		tenv->set_table_size_hint(table_sz_hint);
		tenv->set_log_size_mb(log_sz_mb);
		tenv->set_log_type(table_log_type);
		tenv->set_table_type(table_type);
		tenv->set_sort_method(sort_method);
		tenv->set_sort_dirction(sort_direction);
		tenv->set_key_type(key_type);
		tenv->set_primitive_data_type(prim_data_type);
		tenv->set_table_subtype(table_subtype);
		tenv->set_log_state(wal_enabled);
		tenv->set_autocommit_state(autocommit);
		tenv->set_allow_duplicate(allow_duplicate);
	}

	void setFromHdrWithCheck(table_env *tenv)
	{
		tenv->set_autocommit_state(autocommit);
		tenv->set_allow_duplicate(allow_duplicate);
		if(idx_type != -1)
			tenv->set_idx_type(idx_type);
		if(key_sz != -1)
			tenv->set_key_size_byte(key_sz);
		if(log_sz_mb != -1)
		{
			tenv->set_log_size_mb(log_sz_mb);
			tenv->set_log_state(wal_enabled);
		}
		if(table_log_type != -1)
			tenv->set_log_type(table_log_type);
		if(db_type != -1)
			tenv->set_persist_type(db_type);
		if(table_sz_hint != -1)
			tenv->set_table_size_hint(table_sz_hint);
		if(key_type != -1)
			tenv->set_key_type(key_type);
		if(sort_direction != -1)
			tenv->set_sort_dirction(sort_direction);
		if(sort_method != -1)
			tenv->set_sort_method(sort_method);
		if(table_type != -1)
			tenv->set_table_type(table_type);
		tenv->set_primitive_data_type(prim_data_type);
		tenv->set_table_subtype(table_subtype);
	}
};

const int TABLE_ENV_HDR_SZ = sizeof(table_env_hdr);

struct scan_filter_hdr
{
	char skey_op;	//default GTE
	char ekey_op;	//default LTE
	short limitby;	//default LIMIT_RESULT_SIZE
	int limit;		//default 2MB (MAX_RESULTSET_SIZE) for LIMIT_RESULT_SETSIZE
	int dat_buf_len;
	int skip_count;
	scan_filter_hdr()
	{
		skey_op = GTE;
		ekey_op = LTE;
		limitby = LIMIT_RESULT_SIZE;
		limit = MAX_RESULTSET_SIZE;
		dat_buf_len = MAX_RESULTSET_SIZE;
		skip_count = 0;
	}
};

const int SCAN_FILTER_HDR_SZ = sizeof(scan_filter_hdr);

struct idxrecinfo
{
private:
	int keylen;
	int datlen;
	FILEOFF_T datoff;
public:
	idxrecinfo() { keylen = datlen = 0; datoff = 0; }
	idxrecinfo(int _keylen, int _datlen, FILEOFF_T _datoff)
	{
		keylen = (_keylen);
		datlen = (_datlen);
		datoff = (_datoff);
	}
	void init(int _keylen, int _datlen, FILEOFF_T _datoff)
	{
		keylen = (_keylen);
		datlen = (_datlen);
		datoff = (_datoff);
	}
	void setkeylen(int _keylen) { keylen = (_keylen); }
	int getkeylen() { return (keylen); }

	void setdatlen(int _datlen) { datlen = (_datlen); }
	int getdatlen() { return (datlen); }

	void setdatoff(FILEOFF_T _datoff) { datoff = (_datoff); }
	FILEOFF_T getdatoff() { return (datoff); }
};
struct idxrecinfo_normal_long
{
private:
	LONG_T key;
	FILEOFF_T datoff;
	int datlen;
public:
	idxrecinfo_normal_long() { key =0; datoff = 0; datlen = 0; }
	idxrecinfo_normal_long(LONG_T _key, int _datlen, FILEOFF_T _datoff)
	{
		key = (_key);
		datoff = (_datoff);
		datlen = (_datlen);
	}
	void init(LONG_T _key, int _datlen, FILEOFF_T _datoff)
	{
		key = (_key);
		datoff = (_datoff);
		datlen = (_datlen);
	}
	void setkey(LONG_T _key) { key = (_key); }
	LONG_T getkey() { return key; }

	void setdatlen(int _datlen) { datlen = (_datlen); }
	int getdatlen() { return (datlen); }

	void setdatoff(FILEOFF_T _datoff) { datoff = (_datoff); }
	FILEOFF_T getdatoff() { return (datoff); }
};

struct idxrecinfo_long
{
private:
	LONG_T key;
	FILEOFF_T datoff;
public:
	idxrecinfo_long() { key = 0; datoff = 0; }
	idxrecinfo_long(LONG_T _key, FILEOFF_T _datoff)
	{
		key = (_key);
		datoff = (_datoff);
	}
	void init(LONG_T _key, FILEOFF_T _datoff)
	{
		key = (_key);
		datoff = (_datoff);
	}
	void setkey(LONG_T _key) { key = (_key); }
	LONG_T getkey() { return (key); }

	void setdatoff(FILEOFF_T _datoff) { datoff = (_datoff); }
	FILEOFF_T getdatoff() { return (datoff); }
};

struct idxrecinfo_int
{
private:
	int key;
	int datoff;
public:
	idxrecinfo_int() { key = 0; datoff = 0; }
	idxrecinfo_int(int _key, int _datoff)
	{
		key = (_key);
		datoff = (_datoff);
	}
	void init(int _key, int _datoff)
	{
		key = (_key);
		datoff = (_datoff);
	}
	void setkey(int _key) { key = (_key); }
	int getkey() { return (key); }

	void setdatoff(int _datoff) { datoff = (_datoff); }
	int getdatoff() { return (datoff); }
};

const int idxrecinfolen = sizeof(idxrecinfo);
const int idxrecinfo_longlen = sizeof(idxrecinfo_long);
const int idxrecinfo_intlen = sizeof(idxrecinfo_int);
const int idxrecinfo_normal_longlen = sizeof(idxrecinfo_normal_long);

#define METAEXTN				".met"
#define IDXEXTN					".idx"
#define DATEXTN					".dat"
#define DIREXTN					".dir"
#define LOGXTN					".log"

#define BANGDB_CONFIG			"bangdb.config"

//the enum to have various opcodes for operations and then we also have an array which gives the description given the id of the optype

enum IQ_SUB_OPTYPE
{
	/* different get for connection & wide connection */
	C_GET,				//for char* FDT* data
	C_GET_PARAM,		//for get which has key len and data len defined
	C_GET_LONG,			//return char* for LONG key
	C_GET_DATAVAR,				//for char* FDT* data
	C_GET_PARAM_DATAVAR,		//for get which has key len and data len defined
	C_GET_LONG_DATAVAR,			//return char* for LONG key

	/* for prim connection */
	PC_GET_LL,
	PC_GET_FL,

	/* put for connection */
	C_PUT,
	C_PUT_DATAVAR,
	C_PUT_LONG,

	/* put for prim connection */
	PC_PUT_LL,
	PC_PUT_FL,

	/* put for wide connection (the wide table specific ones, the normal connection applies here as well) */
	WC_PUT_FIDX,
	WC_PUT_LIDX,
	WC_PUT_DOC,
	WC_PUT_DOC_STR,
	WC_PUT_DOC_LONG,

	/* scan - for all */
	//The request from client will have DATA_VAR info, basically data_buf_len. If 0 then just consider the scan_filter constraints,
	//else apply data_buf_len constraint as well
	C_SCAN_FF,
	C_SCAN_LL,

	/* scan wide connection specific */
	WC_SCAN_IDX,
	WC_SCAN_DOC_FF,
	WC_SCAN_DOC_LL,

	/* del, common for all */
	C_DEL,
	C_DEL_LONG,

	/* count, common for all */
	C_COUNT,
	C_COUNT_FF,
	C_COUNT_LL,

	/* add index */
	ADD_INDEX_STR,
	ADD_INDEX_NUM,
	ADD_INDEX_ENV,

	/* for analytics */
	CREATE_SW_TABLE,
	SW_TABLE_ADD_INDEX,
	SW_TABLE_INIT,
	CLOSE_SW_TABLE,
	SW_PUT,
	SW_PUT_IDX,
	SW_SCAN,
	SW_SCAN_LAG,
	SW_SCAN_FULL,
	SW_SCAN_REM,

	CREATE_SW_ENTITY_COUNT,
	CREATE_SW_ENTITY,
	SW_ENTITY_INIT,
	SW_ENTITY_ADD,
	SW_ENTITY_ADD_CREATE,
	SW_ENTITY_COUNT,
	SW_ENTITY_COUNT_SPAN,
	SW_ENTITY_COUNT_LIST_STR,
	SW_ENTITY_COUNT_LIST_JSON,
	SW_ENTITY_REMOVE,
	SW_ENTITY_SHUTDOWN,

	CREATE_TOPK,
	PUT_TOPK,
	GET_TOPK,
	GET_TOPK_JSON,
	CLOSE_TOPK,
};

//the enum to have various opcodes for operations and then we also have an array which gives the description given the id of the optype
enum IQ_OPTYPE
{
	/* the db op types */
	DB_CREATE_DATABASE,				//0
	DB_CLOSE_DATABASE,
	DB_VERIFY_DATABASE,
	DB_CREATE_DATABASE_ERROR,
	DB_CLOSE_DATABASE_ERROR,
	DB_VERIFY_DATABASE_ERROR,
	DB_CREATE_DATABASE_SUCCESS,
	DB_CLOSE_DATABASE_SUCCESS,
	DB_SLAVE_CLOSE_DATABASE_ERROR,
	DB_VERIFY_DATABASE_SUCCESS,
	DB_DESCRIBE_DATABASE,
	DB_DESCRIBE_DATABASE_ERROR,
	DB_DESCRIBE_DATABASE_SUCCESS,
	DB_DESCRIBE_TABLE,
	DB_DESCRIBE_TABLE_ERROR,
	DB_DESCRIBE_TABLE_SUCCESS,

	DB_CREATE_TABLE,				//16
	DB_CLOSE_TABLE,
	DB_VERIFY_TABLE,
	DB_CREATE_TABLE_ERROR,
	DB_CLOSE_TABLE_ERROR,
	DB_VERIFY_TABLE_ERROR,
	DB_SLAVE_VERIFY_TABLE_ERROR,
	DB_CREATE_TABLE_SUCCESS,
	DB_CLOSE_TABLE_SUCCESS,
	DB_TABLE_ALREADY_CLOSED,
	DB_TABLE_ALREADY_OPEN,
	DB_SLAVE_CLOSE_TABLE_ERROR,
	DB_VERIFY_TABLE_SUCCESS,
	DB_DROP_TABLE,
	DB_DROP_TABLE_SUCCESS,
	DB_DROP_TABLE_ERROR,
	DB_TABLE_DOESNT_EXIST,
	DB_DOESNT_EXIST,
	DB_ALREADY_CLOSED,
	DB_ALREADY_OPEN,
	DB_CREATE_CONN,
	DB_CREATE_CONN_ERROR,
	DB_CREATE_CONN_SUCCESS,
	DB_CLOSE_CONN,
	DB_CLOSE_CONN_ERROR,
	DB_CLOSE_CONN_SUCCESS,
	DB_CONN_OPEN_ERROR,
	DB_JSON_PARSE_ERROR,

	DB_CREATE_SW,				//44
	DB_CREATE_SW_SUCCESS,
	DB_CREATE_SW_ERROR,
	DB_SW_ALREADY_OPEN,
	DB_SW_DOESNT_EXIST,
	DB_SW_ALREADY_CLOSED,
	DB_SW_INIT,
	DB_SW_INIT_SUCCESS,
	DB_SW_INIT_ERROR,
	DB_CLOSE_SW,
	DB_CLOSE_SW_SUCCESS,
	DB_CLOSE_SW_ERROR,
	DB_SW_ENTITY_REMOVE,
	DB_SW_ENTITY_REMOVE_SUCCESS,
	DB_SW_ENTITY_REMOVE_ERROR,

	DB_TABLE_ADD_INDEX,			//59
	DB_TABLE_DROP_INDEX,
	DB_TABLE_ADD_INDEX_SUCCESS,
	DB_TABLE_DROP_INDEX_SUCCESS,
	DB_TABLE_ADD_INDEX_ERROR,
	DB_TABLE_DROP_INDEX_ERROR,

	DB_GET_CONNECTION,					//65
	DB_CLOSE_CONNECTION,
	DB_GET_CONNECTION_ERROR,
	DB_CLOSE_CONNECTION_ERROR,
	DB_GET_CONNECTION_SUCCESS,
	DB_CLOSE_CONNECTION_SUCCESS,

	DB_DUMP_DATA,						//71
	DB_DUMP_DATA_ERROR,
	DB_DUMP_DATA_SUCCESS,

	DB_DUMP_TABLE_DATA,					//74
	DB_DUMP_TABLE_DATA_ERROR,
	DB_DUMP_TABLE_DATA_SUCCESS,

	DB_INSERT_UNIQUE,					//77
	DB_INSERT_UNIQUE_NOROUTE,
	DB_UPDATE_EXISTING,
	DB_UPDATE_EXISTING_NOROUTE,
	DB_INSERT_UPDATE,
	DB_INSERT_UPDATE_NOROUTE,
	DB_INSERT_UNIQUE_ERROR,
	DB_UPDATE_EXISTING_ERROR,
	DB_INSERT_UPDATE_ERROR,
	DB_INSERT_SUCCESS,
	DB_INSERT_ERROR,

	DB_INSERT_UNIQUE_TRAN,				//88
	DB_INSERT_UNIQUE_TRAN_NOROUTE,
	DB_UPDATE_EXISTING_TRAN,
	DB_UPDATE_EXISTING_TRAN_NOROUTE,
	DB_INSERT_UPDATE_TRAN,
	DB_INSERT_UPDATE_TRAN_NOROUTE,
	DB_INSERT_UNIQUE_ERROR_TRAN,
	DB_UPDATE_EXISTING_ERROR_TRAN,
	DB_INSERT_UPDATE_ERROR_TRAN,
	DB_INSERT_SUCCESS_TRAN,
	DB_INSERT_ERROR_TRAN,

	DB_GET_DATA,						//89
	DB_GET_DATA_NOROUTE,
	DB_GET_DATA_ERROR,
	DB_GET_DATA_OVERFLOW_ERROR,
	DB_GET_DATA_LIMIT_ERROR,
	DB_GET_DATA_EXISTS_ERROR,
	DB_GET_DATA_SUCCESS,

	DB_GET_DATA_TRAN,					//96
	DB_GET_DATA_TRAN_NOROUTE,
	DB_GET_DATA_ERROR_TRAN,
	DB_GET_DATA_LIMIT_ERROR_TRAN,
	DB_GET_DATA_EXISTS_ERROR_TRAN,
	DB_GET_DATA_SUCCESS_TRAN,

	DB_DEL_DATA,						//102
	DB_DEL_DATA_NOROUTE,
	DB_DEL_DATA_ERROR,
	DB_DEL_DATA_LIMIT_ERROR,
	DB_DEL_DATA_NOT_EXIST_ERROR,
	DB_DEL_DATA_SUCCESS,

	DB_DEL_DATA_TRAN,					//108
	DB_DEL_DATA_TRAN_NOROUTE,
	DB_DEL_DATA_ERROR_TRAN,
	DB_DEL_DATA_LIMIT_ERROR_TRAN,
	DB_DEL_DATA_NOT_EXIST_ERROR_TRAN,
	DB_DEL_DATA_SUCCESS_TRAN,

	DB_SCAN_DATA,						//114
	DB_SCAN_DATA_NOROUTE,
	DB_SCAN_DATA_ERROR,
	DB_SCAN_DATA_SUCCESS,

	DB_SCAN_DATA_TRAN,					//118
	DB_SCAN_DATA_ERROR_TRAN,
	DB_SCAN_DATA_SUCCESS_TRAN,

	DB_KEY_OUT_OF_RANGE,				//121
	DB_DAT_OUT_OF_RANGE,

	DB_COUNT_DATA,						//123
	DB_COUNT_DATA_NOROUTE,
	DB_COUNT_DATA_ERROR,
	DB_COUNT_DATA_SUCCESS,

	DB_BEGIN_TRANSACTION,				//127
	DB_COMMIT_TRANSACTION,
	DB_ABORT_TRANSACTION,
	DB_BEGIN_TRANSACTION_SUCCESS,
	DB_COMMIT_TRANSACTION_SUCCESS,
	DB_ABORT_TRANSACTION_SUCCESS,
	DB_BEGIN_TRANSACTION_ERROR,
	DB_COMMIT_TRANSACTION_ERROR,
	DB_ABORT_TRANSACTION_ERROR,

	DB_SET_AUTOCOMMIT,					//136
	DB_SET_AUTOCOMMIT_SUCCESS,
	DB_SET_AUTOCOMMIT_ERROR,

	DB_BAD_OPTYPE,						//139

	DB_OP_TYPE_END,						//140

	/* for master slave cofiguration, for network db */
	MS_REGISTER_SLAVE,					//118
	MS_REGISTER_SLAVE_ACK,
	MS_REPL_DISABLED,
	MS_REGISTER_SLAVE_MAX_ERROR,		//170
	MS_SLAVE_NOT_FOUND_ERROR,
	MS_SLAVE_ALREADY_PRESENT,
	MS_MASTER_CONNECT_EVENT,
	MS_TARGET_NOT_MASTER_ERROR,
	MS_BANGDB_ERROR,
	MS_FILE_SEND_ERROR,
	MS_SYNC_OPREC_ERROR,
	MS_SLAVE_IN_SYNC,					//129
	MS_SYNC_SLAVE,					//slave send SYNC request to master
	MS_SYNC_SLAVE_MACK,				//master sends MACK to client with file size it's going to transfer (doesn't put the fd to epoll)
	MS_SYNC_SLAVE_MACK_SACK,		//slave upon receiving MACK, sends MACK_SACK and goes to read loop, master upon receiving MACK_SACK sends the file
	MS_SYNC_SLAVE_OPS_REC,			//once sync done at slave, it sends SLAVE_OPS_REC msg to master, and master then transfers the entire ops record
	MS_SYNC_SLAVE_OPS_REC_MACK,
	MS_SYNC_SLAVE_DONE,				//after receiving all ops rec at slave, slave sends the DONE msg to master and master then stes various flags and puts the
									//fd back to epoll

	MS_SYNC_INVALID_CODE,				//136
	MS_SYNC_CONNECT_ERROR,
	MS_SYNC_SLAVE_TABLE_FINISH,
	MS_SYNC_SLAVE_TABLE,
	MS_SYNC_TABLE_NO_EXIST,
	MS_SYNC_SLAVE_TABLE_GO,
	MS_SYNC_SLAVE_TABLE_NOGO,
	MS_SLAVE_MASTER_LOG_INFO,
	MS_SLAVE_MASTER_LOG_INFO_NOTHING,

	MS_SYNC_SLAVE_NOTHING,				//145
	MS_SYNC_SLAVE_SOMETHING,
	MS_SYNC_SLAVE_SOMETHING_SACK,

	MS_SYNC_METADATA,					//148
	MS_SYNC_METADATA_SACK,
	MS_SYNC_METADATA_ERROR,

	MS_UPDATE_NOT_ALLOWED,				//151
	MS_OPS_RECORD_BUFF_FULL,
	MS_ALL_SLAVES_NOT_IN_SYNC,
	MS_SLAVE_CANT_REPL,

	MS_SYNC_DML,						//155
	MS_SYNC_DML_SUCCESS,
	MS_SYNC_DML_ERROR,

	MS_CONN_CHECK_MSG,					//158

	MS_OP_TYPE_END,						//159

	/* not used in DHT scenario */
	OPTYPE_ERROR,
	MESSAGE_FORMAT_ERROR,					//15
	/* chrod related messages, used in DHT scenario */
	CHORD_CREATE_RING,						//doesn't require routing
	CHORD_CREATE_RING_SUCCESS,
	CHORD_LEAVE_RING,
	CHORD_LEAVE_RING_SUCCESS,
	CHORD_LOCATE_NODE,						//***requires routing
	//CHORD_LOCATE_NODE_NOROUTE,
	CHORD_LOCATE_RETURN_NODE,
	CHORD_LOCATE_NODE_ERROR,				//20
	CHORD_JOIN_NODE,						//***requires routing
	CHORD_JOIN_NODE_SUCCESS,
	CHORD_JOIN_NODE_ERROR,
	//CHORD_JOIN_NODE_NOROUTE,
	CHORD_JOIN_LOCATE_NODE,					//***requires routing
	//CHORD_JOIN_LOCATE_NODE_NOROUTE,
	CHORD_JOIN_LOCATE_RETURN_NODE,
	CHORD_JOIN_LOCATE_NODE_ERROR,
	CHORD_FIXFIN_LOCATE_NODE,				//25 //***requires routing
	//CHORD_FIXFIN_LOCATE_NODE_NOROUTE,
	CHORD_FIXFIN_LOCATE_RETURN_NODE,
	CHORD_FIXFIN_RETURN_NODE_ERROR,
	CHORD_GET_PRED,
	CHORD_RETURN_GETPRED,
	CHORD_REMOTE_NOTIFY,					//30
	CHORD_REMOTE_NOTIFY_SUCCESS,
	CHORD_REMOTE_NOTIFY_ERROR,
	CHORD_GET_NODESTATE,
	CHORD_SET_PRED,
	CHORD_SET_PRED_SUCCESS,
	CHORD_SET_PRED_ERROR,
	CHORD_SET_SUCC,
	CHORD_SET_SUCC_SUCCESS,
	CHORD_SET_SUCC_ERROR,
	CHORD_GET_SUCCLIST,
	CHORD_GET_SUCCLIST_SUCCESS,
	CHORD_ERROR,							//35
	CHORD_ROUTE_ERROR,
	CHORD_SHOW_STATS,
	CHORD_SHOW_STATS_SUCCESS,
	CHORD_MSG_ACK,

	/* the dht related constants will be added later */

	/* finally to mark as end of the enum */
	IQ_OPTYPE_END						//
};

#ifdef BPOOL_DEBUG_MODE
#undef BPOOL_DEBUG_MODE
#endif

/*
namespace USERCONFIG
{
	//type of db (0=EMBED_INMEM_ONLY, 1=EMBED_INMEM_PERSIST, 2=EMBED_FILE, 3=NETWORK_INMEM_PERSIST)
	extern int BANGDB_PERSIST_TYPE;

	//type of indec (0 = EXTHASH, 1 = BTREE)
	extern int BANGDB_INDEX_TYPE;

	//log enabled = 1, disabled = 0
	extern int BANGDB_LOG;

	//page size in bytes
	extern int PAGE_SIZE;

	//dat buffer size in KB (max)
	extern int DAT_SIZE;

	//index size in bytes (max)
	extern int KEY_SIZE;

	//max size of the result set
	extern int MAX_RESULTSET_SIZE;

	//if on, single ops without explicit txn
	extern int BANGDB_AUTOCOMMIT;

	//log buffer size (in MB)
	extern FILEOFF_T LOG_BUF_SIZE;						//256 by default

	//bangdb group id
	extern char BANGDB_GROUP[64];

	//max table a db can have (we should depricate this)
	extern int MAXTABLE;								//32

	//max number of connections a region can have in single client, note: all will share the bpool
	extern int MAXCONN;									//64

	//2nd argument to listen()
	extern int LISTENQ;									//1024

	//Name of the server
	extern char MASTER_SERVER_ID[128];

	//Define some port number that can be used for our examples
	extern int SERV_PORT;								//7888, TCP and UDP

	// the following are required for various calculations of perameters in the db, not set by users

	extern char MASTER_SERV_PORT_STR[8];		 		//7888, TCP and UDP

	extern int BANGDB_GROUP_ID;

	extern int DAT_BUF;

	extern int RECV_BUF_SIZE;

	extern 	int KEY_COMP_FUNCTION_ID;
}
using namespace USERCONFIG;

//used to read the user config
table_env *readuserconfig(char* path);
table_env *set_db_vars();
int keycmp_lexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen);
int keycmp_quasiLexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen);
void init_keycmp();
*/


LONG_T keycmp(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen, short sort_id);
bool isKeyNum(short table_type, short sort_id);

bool isPrimitive(bangdb_table_type tbl_type);
short getPrimitiveDataType(bangdb_table_type tbl_type);
short getPrimitiveTableType(bangdb_primitive_data_type data_type);
bool isNormalPrim(bangdb_table_type tp);
bool isWide(bangdb_table_type tp);
bool isNormal(bangdb_table_type tp);
bangdb_bs_findpos getPos(bool allowDupl, int opval);
int getPosIdx(bool allowDupl, int opval, int pos);
bool isLastKeyInPage(bool allowDupl, bool strtype, char *pk, int pklen, char *ekey, int ekeylen, int sort_id, bangdb_bs_findpos _pos);
}
#endif /* BANGDB_CLIENT_H_ */
