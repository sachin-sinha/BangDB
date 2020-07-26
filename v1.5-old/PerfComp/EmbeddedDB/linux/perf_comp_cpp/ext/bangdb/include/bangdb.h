/*
 * bangdb.h
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

#ifndef BANGDB_H_
#define BANGDB_H_

#include "bheader.h"
#include "pagehdr.h"
#include "logheader.h"
#include "tableenv.h"
#include "bangdb_error_msg.h"

namespace bangdb
{

#define MINLINE					128
#define SHORTLINE 				512
#define MAXLINE 				4096
#define	BUFFSIZE 				8192
#define MAXN 					16384
#define MAXTRY					20
#define BANGDB_DIV_FORMAT_KB 	1024
#define MAX_FILES_IN_DIR		128

#define SEP 					':'
#define SEP_STR					":"
#define SLASH 					'/'
#define KEY_SEP					'.'
#define SPACE 					0
#define BLANK 					' '
#define PTR_SZ 					12
#define INT_SZ 					4
#define FREE_OFF 				0
#define DIRREC_SZ 				8
#define BTREE_PAGE 				1
#define EHASH_PAGE 				0
#define NULL_PAGE 				-9
#define INFINITY_KEY 			"$#&*!%^@"
#define INFINITY_KEY_LONG		-1
#define JSON_DOC_PK				"_pk"

#define GDLEN_SZ 				2
#define DIRLEN_SZ 				PTR_SZ
#define IDXLEN_SZ 				INT_SZ
#define GD_OFF 					PTR_SZ
#define ROOT_OFF 				(INT_SZ+INT_SZ+PTR_SZ)

#define DBSTATUSLEN				 1
#define LSNLEN					14
#define TXNIDLEN				13
#define PAGEIDLEN				 9
#define LOGRECLEN				 9
#define FIDLEN					 3

#define LOGMAXFULL				80
#define OFFSETLEN				PTR_SZ
#define DATSZLEN				 9
#define LOGXTNSZ				 8

#define MIN_CHKPT_TXN			500

#define DPRECSZ					(1+FIDLEN+PAGEIDLEN+LSNLEN+5)

#define TXRECSZ					(TXNIDLEN+LSNLEN+1+4)
#define DPTXRECSZ				DPRECSZ
#define DPTXKEYLEN				(1+FIDLEN+PAGEIDLEN)
#define RECHDRSZ				(LSNLEN+LOGRECLEN+LSNLEN+TXNIDLEN+1+1+FIDLEN+PAGEIDLEN)
#define INRPRTSZ				(DATSZLEN+OFFSETLEN+DATSZLEN)
#define LOGFXDSZ				(RECHDRSZ+INRPRTSZ)

#define MAX_KEYCMP_FUNC 3

const int NDPRECSZ = DPRECSZ;
const int NTXRECSZ = TXRECSZ;
const int NDPTXRECSZ = DPTXRECSZ;
const int NDPTXKEYLEN = DPTXKEYLEN;
const int NRECHDRSZ = RECHDRSZ;
const int NINRPRTSZ = INRPRTSZ;
const int NLOGFXDSZ = LOGFXDSZ;

enum bangdb_persist_type
{
	INMEM_ONLY,
	INMEM_PERSIST,
	PERSIST_ONLY,
};

enum bangdb_index_type
{
	HASH,
	EXTHASH,
	BTREE,
	HEAP
};

enum bangdb_log_type
{
	SHARED_LOG,
	PRIVATE_LOG,
};

enum bangdb_open_type
{
	OPENCREATE,
	TRUNCOPEN,
	JUSTOPEN
};

enum bangdb_state
{
	DBCLOSE,
	DBOPEN
};

enum bangdb_close_type
{
	DEFAULT,
	CONSERVATIVE,
	OPTIMISTIC,
	CLEANCLOSE,
	SIMPLECLOSE,
};

enum insert_options
{
	INSERT_UNIQUE,
	UPDATE_EXISTING,
	INSERT_UPDATE,
	DELETE_EXISTING,
};

enum db_transaction_type
{
	DB_TRANSACTION_NONE,
	DB_OPTIMISTIC_TRANSACTION,
	DB_PESSIMISTIC_TRANSACTION,
};

enum db_transaction_phase
{
	TRAN_READ_PHASE,
	TRAN_VALIDATE_PHASE,
	TRAN_COMMIT_PHASE,
	TRAN_ABORT_PHASE,
};

enum table_size_hint
{
	TINY_TABLE_SIZE,
	SMALL_TABLE_SIZE,
	NORMAL_TABLE_SIZE,
	BIG_TABLE_SIZE,
};

enum bangdb_table_type
{
	NORMAL_TABLE,
	WIDE_TABLE,
	INDEX_TABLE,
	PRIMITIVE_TABLE_INT,
	PRIMITIVE_TABLE_LONG,
	PRIMITIVE_TABLE_STRING,
};

enum bangdb_primitive_data_type
{
	PRIMITIVE_INT,
	PRIMITIVE_LONG,
	PRIMITIVE_STRING,
};

enum bangdb_window_type
{
	NON_SLIDING_WINDOW,
	SLIDING_WINDOW_SPAN,
	SLIDING_WINDOW_UNIT,
};

enum bangdb_count_type
{
	UNIQUE_COUNT,
	NON_UNIQUE_COUNT,
};

enum scan_limit_by
{
	LIMIT_RESULT_SIZE,
	LIMIT_RESULT_ROW,
};

enum scan_operator
{
	GT,
	GTE,
	LT,
	LTE,
};

enum bangdb_key_sort_method
{
	LEXICOGRAPH = 1,
	QUASI_LEXICOGRAPH = 2,
};

enum bangdb_key_sort_direction
{
	SORT_ASCENDING = 3,
	SORT_DESCENDING = 4,
};

enum bangdb_key_type
{
	NORMAL_KEY = 1,
	COMPOSITE_KEY = 3,
	NORMAL_KEY_LONG = 10,
};

enum bangdb_data_ops_flag
{
	FLAG_SET_NONE = 0,
	DATA_READ_DONE = 1,
	MORE_DATA_TO_COME = 2,
	DATA_READ_OVERFLOW = 3,
	DATA_READ_ERROR = 4,
};

enum bangdb_bs_findpos
{
	BS_RANDOM_OCCUR,
	BS_FIRST_OCCUR,
	BS_LAST_OCCUR,
};

enum bangdb_table_subtype
{
	NON_ANALYTICAL_TABLE,
	SW_TABLE,
	SW_ENTITY_COUNT_TABLE,
	SW_TOPK_TABLE,
};

struct db_meta
{
	char db_name[MINLINE];
	ULONG_T db_pwd;
	SHORT_T ntableid;
	int page_size;
};

struct filename_fd_list
{
	char *filename;
	int fd;
	filename_fd_list()
	{
		filename = NULL;
		fd = -1;
	}
	void clear()
	{
		if(filename)
			delete[] filename;
		filename = NULL;
		fd = -1;
	}
};

const int FILENAME_FD_LIST_SZ = sizeof(filename_fd_list);

struct table_meta
{
	char tbl_name[MINLINE];
	SHORT_T log_st;
	SHORT_T log_sz;
	SHORT_T log_tp;
	SHORT_T idx_tp;
	SHORT_T key_sz;
	SHORT_T key_tp;
	SHORT_T db_tp;
	SHORT_T db_close;
	SHORT_T fid;
	SHORT_T tbl_type;
	SHORT_T num_idx;
	SHORT_T sort_method;
	SHORT_T sort_dirction;
	SHORT_T prim_data_type;
	SHORT_T table_sub_type;
	SHORT_T allow_duplicate;
	int nusers;
};

struct table_index_meta
{
	char idx_name[MINLINE];
	SHORT_T idx_tp;
	SHORT_T key_sz;
};

struct master_log_info
{
	FILEOFF_T nextlsn;
	FILEOFF_T nexttxn;
	FILEOFF_T logflushedlsn;
	FILEOFF_T bufflushedlsn;
};

const int MASTER_LOG_INFO_SZ = sizeof(master_log_info);

#define METAEXTN				".met"
#define IDXEXTN					".idx"
#define DATEXTN					".dat"
#define DIREXTN					".dir"
#define LOGXTN					".log"
#define ARCHIVEEXT				".arc."
#define APPLOGEXTN					".applog"

#define BANGDB_CONFIG			"bangdb.config"

#ifdef BPOOL_DEBUG_MODE
#undef BPOOL_DEBUG_MODE
#endif

#define TINY_STACK_SIZE 32

template <class T>
class Stack {
public:
   Stack();
   void push(T i);
   T pop();
private:
   int top;
   T st[TINY_STACK_SIZE];
};

template <class T>
Stack<T>::Stack()
{
	top = -1;
}

template <class T>
void Stack<T>::push(T i)
{
	if(top == (TINY_STACK_SIZE-1))
		return;
	st[++top] = i;
}

template <class T>
T Stack<T>::pop()
{
	if(top < 0)
		return -1;
	return st[top--];
}

struct bangdb_malloc
{
	char *refaddr;
	char *baseaddr;
	char *curraddr;
	char *endaddr;
	int bufsize;

	bangdb_malloc()
	{
		init(NULL, 0);
	}

	void init(char *baddr, int bsize)
	{
		refaddr = baseaddr = curraddr = baddr;
		endaddr = baddr + bsize;
		bufsize = bsize;
	}

	bool can_alloc(int size)
	{
		return (curraddr + size > endaddr) ? false : true;
	}

	char *alloc_mem(int size)
	{
		if(curraddr + size > endaddr)
			return NULL;
		char *alloc = curraddr;
		curraddr += size;
		return alloc;
	}

	void undo_alloc(int size)
	{
		if(curraddr - size < endaddr)
			return;
		curraddr -= size;
	}

	void extend_size(int bySize)
	{
		endaddr += bySize;
		refaddr += bySize;
	}

	LONG_T alloc_size()
	{
		return curraddr - refaddr;
	}

	void set_curmem(int buf_len)
	{
		if(buf_len > bufsize)
			err_ret("Error is setting the current memory as it's out of allocated memory");
		curraddr = refaddr;
		curraddr += buf_len;
	}

	LONG_T get_offset(char *baddr)
	{
		return (LONG_T)(baddr - baseaddr);
	}

	char *get_addr(int offset)
	{
		return baseaddr + offset;
	}
};


struct mem_chunk
{
	char *buf;
	mem_chunk *next;

	mem_chunk()
	{
		buf = NULL;
		next = NULL;
	}

	mem_chunk(int _size, mem_chunk *_next)
	{
		buf = new char[_size];
		next = _next;
	}

	~mem_chunk()
	{
		delete[] buf;
	}
};

namespace USERCONFIG
{
	extern char SERVER_DIR[SHORTLINE];

	extern char BANGDB_LOG_DIR[SHORTLINE];

	extern char BANGDB_DATABASE_NAME[MINLINE];

	extern char BANGDB_TABLE_NAME[MINLINE];

	extern int BANGDB_PERSIST_TYPE;

	extern int BANGDB_INDEX_TYPE;

	extern int BANGDB_LOG;

	extern int BANGDB_AUTOCOMMIT;

	extern int BANGDB_TRANSACTION_CACHE_SIZE;

	extern int PAGE_SIZE_BANGDB;

	extern int DAT_SIZE;

	extern int KEY_SIZE;

	extern int MAX_RESULTSET_SIZE;

	extern char BANGDB_GROUP[64];

	extern int MAXTABLE;

	extern int MAXCONN;

	extern int LISTENQ;

	extern int MAX_THREADS;

	extern int BANGDB_APP_LOG;

	extern double PAGE_SPILT_FACTOR;

	extern int MAX_CLIENT_EVENTS;

	extern int SERVER_TYPE;

	extern int ENABLE_REPLICATION;

	extern char SERVER_ID[128];

	extern int SERV_PORT;

	extern char MASTER_SERVER_ID[128];

	extern int MASTER_SERV_PORT;

	extern int MAX_SLAVES;

	extern int PING_FREQ;

	extern int PING_THRESHOLD;

	extern int CLIENT_TIME_OUT;

	extern int SERVER_STAGE_OPTION;

	extern int SERVER_OPS_WORKERS;

	extern FILEOFF_T BUFF_POOL_SIZE_HINT;

	extern FILEOFF_T LOG_BUF_SIZE;

	extern int MASTER_LOG_BUF_SIZE;

	extern FILEOFF_T OPS_REC_BUF_SIZE;

	extern int DB_APP_LOG_SIZE_MB;

	extern int BANGDB_SIGNAL_HANDLER_STATE;

	extern int BANGDB_SYNC_TRAN;

	extern long LOG_FLUSH_FREQ;

	extern int CHKPNT_ENABLED;

	extern long CHKPNT_FREQ;

	extern long LOG_SPLIT_CHECK_FREQ;

	extern long BUF_FLUSH_RECLAIM_FREQ;

	extern FILEOFF_T GROW_BUFF_SIZE;

	extern int SCATTER_GATHER_MAX;

	extern int MIN_DIRTY_SCAN;

	extern int MIN_UPDATED_SCAN;

	extern int IDX_FLUSH_CONSTRAINT;

	extern int DAT_FLUSH_CONSTRAINT;

	extern int IDX_RECLAIM_CONSTRAINT;

	extern int DAT_RECLAIM_CONSTRAINT;

	extern int PAGE_WRITE_FACTOR;

	extern int IDX_DAT_NORMALIZE;

	extern int PREFETCH_BUF_SIZE;

	extern int PREFETCH_SCAN_WINDOW_NUM;

	extern int PREFETCH_EXTENT_NUM;

	extern int KEY_COMP_FUNCTION_ID;

	extern char SERV_PORT_STR[8];

	extern char MASTER_SERV_PORT_STR[8];

	extern int BANGDB_GROUP_ID;

	extern int HASH_TABLE_SIZE_IDX;

	extern int HASH_TABLE_SIZE_DAT;

	extern int HASH_TABLE_SIZE_DIR;

	extern int NLOOPFOR;

	extern int DIR_OFF;

	extern int NUMLOGREC;

	extern int NUMCONTHREAD;

	extern int DAT_BUF;

	extern FILEOFF_T MASTERLOGSHMSZ;

	extern FILEOFF_T RECORDSHMEM;

	extern FILEOFF_T RECORDSZ;

	extern bool repl_done;
}
using namespace USERCONFIG;

table_env *readuserconfig(char* path);
table_env *set_db_vars();
void set_table_buf_sizes(FILEOFF_T *buff_pool_size_hint, int *hash_table_size_dir, int *hash_table_size_idx, int *hash_table_size_dat);
FILEOFF_T _compute_buf_hash_table_size(int bufsize);
FILEOFF_T _compute_buf_size_from_table(int tbsz);

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
void set_repl_done(bool flag);
bool get_repl_done();
extern void *bangdbw;
void set_bangdb_wrapper(void *_bw);
void *get_bangdb_wrapper();

}
#endif /* BANGDB_H_ */
