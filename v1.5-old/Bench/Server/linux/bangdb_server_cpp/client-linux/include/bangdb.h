/*
 * bangdb.h
 *
 *  Created on: 16-Nov-2011
 *      Author: sachin
 *
 *      bangdb related config parameters
 */

#ifndef BANGDB_H_
#define BANGDB_H_

#include "tableenv.h"
#include "bangdb_error_msg.h"
namespace bangdb_client
{
//buffer size related macros end
#define MINLINE					128
#define SHORTLINE 				512
#define MAXLINE 				4096               				//max line length
#define	BUFFSIZE 				8192							//buffer size for reads and writes
#define MAXN 					16384							//max buffer that could be written on IPv4 socket
#define MAXTRY					20								//max num of try a file/dir operation should make before giving up in genuine cases#define MAXTRY 20
#define BANGDB_DIV_FORMAT_KB 	1024
#define MAX_FILES_IN_DIR		128

//===========various system parameters for bangdb=============
//need to revisit these
#define SEP 					':' 							//in the idx file, fixed
#define SEP_STR					":"								//the str version of SEP
#define SLASH 					'/'
#define KEY_SEP					'.'
#define SPACE 					0								//on prod use 0 as space for debugging the idx file use ' ', as it's readable, fixed
#define BLANK 					' '								//this is good as we can utilize it for log (in logrecord ops for efficiency)
#define PTR_SZ 					12 								//in the idx file and in the .dir file, fixed
#define INT_SZ 					4 								//in the idx file for a idx record, fixed
#define FREE_OFF 				0								//offset for the free list in the .dir file, fixed
#define DIRREC_SZ 				8								//changed to 8 as we write the serialized object of FILEOFF_T type
#define BTREE_PAGE 				1								//fixed
#define EHASH_PAGE 				0								//fixed
#define NULL_PAGE 				-9								//fixed
#define INFINITY_KEY 			"$#&*!%^@"						//fixed, assuming no body would have such key to insert :)
#define INFINITY_KEY_LONG		-1								//fixed, assuming no one will use -1 as key
#define JSON_DOC_PK				"_pk"

//defintion for various params in the begining of .dir file(ONLY FOR Ehash index type)
#define GDLEN_SZ 				2
#define DIRLEN_SZ 				PTR_SZ
#define IDXLEN_SZ 				INT_SZ
#define GD_OFF 					PTR_SZ 							//of len GD_SIZE
#define ROOT_OFF 				(INT_SZ+INT_SZ+PTR_SZ)			//2 INT_SZ(ld, m), PTR_SZ, PAG_HDR = 32, offset in the .idx file for Btree which contains the current root offset

//========log relates macros=========
#define DBSTATUSLEN				 1								//length to denote if the db was close properly(1-ok, 0-not ok)
#define LSNLEN					14								//length of LSN (loff_t)
#define TXNIDLEN				13								//length of transaction id (loff_t)
#define PAGEIDLEN				 9								//size of pageid (BLOCKNUM_T)
#define LOGRECLEN				 9 								//size of logrec (int)
#define FIDLEN					 3								//length of fid, which describes file id within a file type for ex; 23rd file of idx for btree
																//(in case of multiple column family)
#define LOGMAXFULL				80								//the percentage which tells the log to be flushed on priority once threshold has been reached
#define OFFSETLEN				PTR_SZ							//length for offset in any file
#define DATSZLEN				 9								//length of data to store (this however is exacerated as datszlen can;t go beyond the log buffer size:))
#define LOGXTNSZ				 8								//the extension of the log file name, i.e. 00000001 part of the name mytable00000001.log

#define MIN_CHKPT_TXN			500								//minimum trnsactions to happen before a chekpoint should be done

#define DPRECSZ					(1+FIDLEN+PAGEIDLEN+LSNLEN+5)	//ftype+ID+PAGEID+recLSN or IDX+PAGEID+recLSN (1+3+9+14+5 = 32) 5 reserve,
																//here ID would come handy in case of column family, now it will be just for idx third file or so
#define TXRECSZ					(TXNIDLEN+LSNLEN+1+4)			//TXN+lastLSN+TRANSTATE (13+14+1+4 = 32), 4 reserve
#define DPTXRECSZ				DPRECSZ							//since DPRECSZ = TXRECSZ
#define DPTXKEYLEN				(1+FIDLEN+PAGEIDLEN)			//1+3+9 = 13 or 13 for TXNIDLEN
#define RECHDRSZ				(LSNLEN+LOGRECLEN+LSNLEN+TXNIDLEN+1+1+FIDLEN+PAGEIDLEN)		//14+9+14+13+1+1+3+9 = 64
#define INRPRTSZ				(DATSZLEN+OFFSETLEN+DATSZLEN)	//9+12+9 = 30
#define LOGFXDSZ				(RECHDRSZ+INRPRTSZ)				//64+30 = 94

/* edit the defined number for func when new func is added */
#define MAX_KEYCMP_FUNC 3

//these const are defined for performance
const int NDPRECSZ = DPRECSZ;
const int NTXRECSZ = TXRECSZ;
const int NDPTXRECSZ = DPTXRECSZ;
const int NDPTXKEYLEN = DPTXKEYLEN;
const int NRECHDRSZ = RECHDRSZ;
const int NINRPRTSZ = INRPRTSZ;
const int NLOGFXDSZ = LOGFXDSZ;

//types of db
enum bangdb_persist_type
{
	INMEM_ONLY,			//only RAM based, cache enabled (no overflow to disk, ideally overflow to other RAM)
	INMEM_PERSIST,		//disked backed, cache enabled (over flow to disk)
	PERSIST_ONLY,		//cache disabled, direct file IO
};

//types of index
enum bangdb_index_type
{
	HASH,
	EXTHASH,
	BTREE,
	HEAP
};

//log type
enum bangdb_log_type
{
	SHARED_LOG,
	PRIVATE_LOG,
};

//how should we access db, various ways
enum bangdb_open_type
{
	OPENCREATE,
	TRUNCOPEN,
	JUSTOPEN
};

//the various state of the db
enum bangdb_state
{
	DBCLOSE,
	DBOPEN
};

//how should db be closed
enum bangdb_close_type
{
	DEFAULT_AT_CLIENT,
	CONSERVATIVE_AT_SERVER,
	OPTIMISTIC_AT_SERVER,
	CLEANCLOSE_AT_SERVER,
	SIMPLECLOSE_AT_SERVER,
	DEFAULT_AT_SERVER,
};

//the insert options
enum insert_options
{
	INSERT_UNIQUE,		//if non-existing then insert else return
	UPDATE_EXISTING,	//if existing then update else return
	INSERT_UPDATE,		//insert if non-existing else update
	DELETE_EXISTING,	//delete if existing
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
	/* index and data files with opaque (void*) key */
	NORMAL_TABLE,
	WIDE_TABLE,
	/* no data file for following tables */
	INDEX_TABLE,			//opaque(void*) as key and dataoff, datlen is of actual value in the data file store in main table, no data file
	PRIMITIVE_TABLE_INT,	//int as key and int as val, stored in index file only, no data file
	PRIMITIVE_TABLE_LONG,	//long as key and long as val, stored in index file only, no data file
	PRIMITIVE_TABLE_STRING,	//opaque(void*) as key and data stored in the index only, no data file
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

/*
 * sort order id computation
 * ---for normal key (NORMAL_KEY = 1)---
 * 3*1 = 3 for lexi + asc
 * 4*1 = 4 for lexi + desc
 * 3*2 = 6 for quasi + asc
 * 4*2 = 8 for quasi + desc
 * ---for composite key (COMPOSITE_KEY = 3)---
 * 3*1*3 = 9 for lexi + asc
 * 4*1*3 = 12 for lexi + desc
 * 3*2*3 = 18 for quasi + asc
 * 4*2*3 = 24 for quasi + desc
 * ---for composite key (NORMAL_KEY_LONG = 5)---
 * 3*1*10 = 30 for lexi + asc
 * 4*1*10 = 40 for lexi + desc
 * 3*2*10 = 60 for quasi + asc
 * 4*2*10 = 80 for quasi + desc
 */

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
	NORMAL_KEY = 1,		//opaque (void*) as key
	COMPOSITE_KEY = 3,	//always treated as opaque even if it is of long:void* or long:long
	NORMAL_KEY_LONG = 10,	//long as key
	//COMPOSITE_KEY_LONG,	//long:long as key, all keys participating in composite will be long, no hybrid keys
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
	BS_RANDOM_OCCUR,	//whichever is found first in the page (same as of first and last for unique key)
	BS_FIRST_OCCUR,		//the first occurrence of the key in the page
	BS_LAST_OCCUR,		//the last occurrence of the key in the page
};

//denotes whether analytical stuff or not
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
	SHORT_T ntableid;	//ever increasing number, MAX TABLE = 64K, starts from 1
	int page_size;
};

//todo:add duplicate allowed or not
struct table_meta
{
	char tbl_name[MINLINE];
	SHORT_T log_st;
	SHORT_T log_sz;	//in MB
	SHORT_T log_tp;
	SHORT_T idx_tp;
	SHORT_T key_sz;
	SHORT_T key_tp;
	SHORT_T db_tp;
	SHORT_T db_close;
	SHORT_T fid;
	SHORT_T tbl_type;	//wide or simple
	SHORT_T num_idx;	//if wide then num of index
	SHORT_T sort_method;
	SHORT_T sort_dirction;
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

//file extentions for various types of files

#define METAEXTN				".met"
#define IDXEXTN					".idx"
#define DATEXTN					".dat"
#define DIREXTN					".dir"
#define LOGXTN					".log"
#define ARCHIVEEXT				".arc."
#define APPLOGEXTN					".applog"

//#define SERVER_DIR 				"/home/bangdb/bangdbdata/"

#define BANGDB_CONFIG			"bangdb.config"

#ifdef BPOOL_DEBUG_MODE
#undef BPOOL_DEBUG_MODE
#endif

#define TINY_STACK_SIZE 32

//the stack is mainly for btree insert help when we traverse from top to leaf
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

//very simple stack, not considering overflow etc... mainly because it's not required, also needed the fastest one with out any extra features etc...
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

//simple sequential mem alloc for given buffer
struct bangdb_malloc
{
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
		baseaddr = curraddr = baddr;
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
	}

	LONG_T alloc_size()
	{
		return curraddr - baseaddr;
	}

	void set_curmem(int buf_len)
	{
		if(buf_len > bufsize)
			err_ret("Error is setting the current memory as it's out of allocated memory");
		curraddr = baseaddr;
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

//==below stuf should be moved to a config file which should be read by the bangdb at boot time==
namespace USERCONFIG
{
	//the dir where the db file will be created, it should be inside the install dir always
	extern char SERVER_DIR[SHORTLINE];

	//the dir for the log file
	extern char BANGDB_LOG_DIR[SHORTLINE];

	//size of db log
	extern int DB_APP_LOG_SIZE_MB;

	//the syslog for bangdb
	extern int BANGDB_APP_LOG;

	//type of db (0=EMBED_INMEM_ONLY, 1=EMBED_INMEM_PERSIST, 2=EMBED_FILE, 3=NETWORK_INMEM_PERSIST)
	extern int BANGDB_PERSIST_TYPE;

	//type of indec (0 = EXTHASH, 1 = BTREE)
	extern int BANGDB_INDEX_TYPE;

	//log enabled = 1, disabled = 0
	extern int BANGDB_LOG;

	//if on, single ops without explicit txn
	extern int BANGDB_AUTOCOMMIT;

	//page size in bytes
	extern int PAGE_SIZE_BANGDB;

	//dat buffer size in KB (max)
	extern int DAT_SIZE;

	//index size in bytes (max)
	extern int KEY_SIZE;

	//max size of the result set
	extern int MAX_RESULTSET_SIZE;

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

	//Id of the server (Name or IP Address)
	extern char MASTER_SERVER_ID[128];

	extern int KEY_COMP_FUNCTION_ID;

	//Define some port number that can be used for our examples
	extern int SERV_PORT;								//7888, TCP and UDP

	extern char SERV_PORT_STR[8];

	extern int MASTER_SERV_PORT;

	extern char MASTER_SERV_PORT_STR[8];

	extern int BANGDB_GROUP_ID;

	extern int DAT_BUF;

	extern int RECV_BUF_SIZE;
}
using namespace USERCONFIG;

struct scan_filter
{
	scan_operator skey_op;	//default GTE
	scan_operator ekey_op;	//default LTE
	scan_limit_by limitby;	//default LIMIT_RESULT_SIZE
	int limit;				//default 2MB (MAX_RESULTSET_SIZE) for LIMIT_RESULT_SETSIZE
	int skip_count;			//this is set by the db during scan when the last key is duplicated, so that in next scan db should skip these many counts
	scan_filter()
	{
		reset();
	}

	void reset()
	{
		skey_op = GTE;
		ekey_op = LTE;
		limitby = LIMIT_RESULT_SIZE;
		limit = MAX_RESULTSET_SIZE;
		skip_count = 0;
	}

	void clone(scan_filter *_sf)
	{
		skey_op = _sf->skey_op;
		ekey_op = _sf->ekey_op;
		limitby = _sf->limitby;
		limit = _sf->limit;
		skip_count = _sf->skip_count;
	}
};
extern table_env *gtable_env;
table_env *readuserconfig(char* path);
table_env *set_db_vars();
void set_table_buf_sizes(FILEOFF_T *buff_pool_size_hint, int *hash_table_size_dir, int *hash_table_size_idx, int *hash_table_size_dat);
FILEOFF_T _compute_buf_hash_table_size(int bufsize);
FILEOFF_T _compute_buf_size_from_table(int tbsz);

//LONG_T keycmp_lexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen, bool prim_type);
//LONG_T keycmp_quasiLexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen, bool prim_type);
//void init_keycmp();
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
#endif /* BANGDB_H_ */
