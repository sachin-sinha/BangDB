/*
 * BangDBCommon.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_HEADERS_BANGDBCOMMON_H_
#define SRC_HEADERS_BANGDBCOMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>


namespace BangDB
{

#define JSON_DOC_PK 							"_pk"
#define ML_BANGDB_SVM_STR						(char*)"SVM"
#define SVM_VERIFY_PROGRAM_NAME					(char*)"checkdata"
#define SVM_VERIFY_FUNC_NAME					(char*)"verify"
#define SVM_TUNEPARAM_PROGRAM_NAME				(char*)"grid"
#define SVM_TUNEPARAM_FUNC_NAME					(char*)"find_parameters"
#define SVM_TRAIN_PROGRAM_NAME					(char*)"svm_train"
#define SVM_SCALE_PROGRAM_NAME					(char*)"svm_scale"
#define SVM_PREDICT_PROGRAM_NAME				(char*)"svm_predict"
#define SCALED_FILE_EXT							(char*)".scale"
#define RANGE_FILE_EXT							(char*)".range"
#define MODEL_FILE_EXT							(char*)".model"
#define PREDICT_FILE_EXT						(char*)".predict"
#define SVM_PARAM_FILE_KEY						(char*)"param"
#define SVM_RANGE_FILE_KEY						(char*)"range"
#define	KM_NORM_FILE_KEY						(char*)"norm"
#define UDF_LOGIC_FILE_EXT						(char*)"logic_"
#define SVM_SAMPLE_TUNE_PRG						(char*)"subset"
#define SVM_SAMPLE_FILE_EXT						(char*)".samlple"

#define ACCOUNT_ID_KEY_STR						(char*)"schema-name"
#define STREAM_NAME								(char*)"stream-name"
#define ALGO_TYPE_KEY_STR						(char*)"algo_type"
#define ALGO_PARAM_KEY_STR						(char*)"algo_param"
#define ATTR_LIST_KEY_STR						(char*)"attr_list"
#define ML_ATTR_TYPE_STR						(char*)"attr_type"
#define ML_PRED_VAL_STR							(char*)"pred_val"
#define TRAINING_DETAILS_KEY_STR				(char*)"training_details"
#define TUNE_PARAM_KEY_STR						(char*)"tune_params"
#define SCALE_DATA_KEY_STR						(char*)"scale"
#define TRAINING_SOURCE_KEY_STR					(char*)"training_source"
#define TRAINING_SOURCE_TYPE_STR				(char*)"training_source_type"
#define TRAINING_ACTION_STR						(char*)"train_action"
#define PREDICT_DATA_TYPE_STR					(char*)"data_type"
#define PREDICT_DATA_REARRANGE_STR				(char*)"re_arrange"
#define PREDICT_DATA_REFORMAT_STR				(char*)"re_format"
#define PREDICT_MODEL_NAME_STR					(char*)"model_name"
#define PREDICT_FILE_NAME_STR					(char*)"file_name"
#define PREDICT_DATA_STR						(char*)"data"
#define ML_TUNED_PARAM_LIST_STR					(char*)"tuned_algo_params"
#define ML_TRAIN_REQ_STATE_STR					(char*)"train_req_state"
#define ML_TRAIN_REQ_START_TIME_STR				(char*)"train_start_ts"
#define ML_TRAIN_REQ_END_TIME_STR				(char*)"train_end_ts"
#define ML_PRED_REQ_STATE_STR					(char*)"pred_req_state"
#define ML_PRED_REQ_START_TIME_STR				(char*)"pred_start_ts"
#define ML_PRED_REQ_END_TIME_STR				(char*)"pred_end_ts"
#define ML_TRAIN_FILE_SIZE_MB					(char*)"file_size_mb"
#define ML_PREDICT_LABLES						(char*)"predict_labels"
#define ML_PREDICT_VALUES						(char*)"predict_values"
#define ML_PREDICT_LABLES_STR					(char*)"labels"
#define ML_TRAIN_SPEED_STR						(char*)"train_speed"
#define ML_SVM_TARGET_FIELD						(char*)"target_field"
#define ML_PROB_ESTIMATE						(char*)"prob_est"
#define ML_UDF_LABEL							(char*)"udf"
#define ML_UDF_LABEL_NAME						(char*)"udf_name"
#define ML_UDF_LABEL_LOGIC						(char*)"udf_logic"
#define ML_UDF_DEFAULT_BUCKET					(char*)"bangdb_udf_bucket"

#define SVM_TYPE_STR							(char*)"svm_type"
#define SVM_KERNEL_TYPE_STR						(char*)"kernel_type"
#define SVM_DEGREE_TYPE_STR						(char*)"degree"
#define SVM_GAMMA_TYPE_STR						(char*)"gamma"
#define SVM_COEF0_TYPE_STR						(char*)"coef0"
#define SVM_COST_TYPE_STR						(char*)"cost"
#define SVM_NU_TYPE_STR							(char*)"nu"
#define SVM_CACHE_SIZE_TYPE_STR					(char*)"cache_size"
#define SVM_PROBABILITY_TYPE_STR				(char*)"probability"
#define SVM_TERM_TYPE_STR						(char*)"termination_criteria"
#define SVM_EPS_SVR_TYPE_STR					(char*)"eps_svr"
#define SVM_SHRINKING_TYPE_STR					(char*)"shrinking"
#define SVM_NR_WEIGHT_TYPE_STR					(char*)"nr_weight"
#define SVM_WEIGHT_LABEL_TYPE_STR				(char*)"weight_label"
#define SVM_WEIGHT_TYPE_STR						(char*)"weight"
#define ML_ERROR_CODE_STR						(char*)"errorcode"

#define PRED_TRAIN_HOUSEKEEP_TBL_STR			(char*)"ml_pred_train_housekeep_tbl"
#define PRED_HOUSEKEEP_TBL_STR					(char*)"ml_pred_housekeep_tbl"

#define ML_BANGDB_IE_STR						(char*)"IE"
#define ML_BANGDB_IE_SENT_STR					(char*)"IE_SENT"
#define ML_BANGDB_IE_TAGS_SUPPORTED_STR			(char*)"IE_TAGS_SUPPORTED"
#define ML_BANGDB_IE_NER_DETECT_STR				(char*)"IE_NER_DETECT"
#define ML_BANGDB_ALGO_TYPE_IE_WORD_DICT_STR	(char*)"IE_WORD_DICT"
#define ML_BANGDB_ALGO_TYPE_IE_NER_TRAIN_STR	(char*)"IE_NER_TRAIN"
#define ML_IE_CLASS_FILE						(char*)"class_file"
#define ML_IE_TOTAL_FEATURE_EX_STR				(char*)"total_feature_ex"
#define ML_IE_TOTAL_FEATURE_EX_FILE				(char*)"total_word_feature_extractor.dat"
#define IE_GET_TEXT_BASE_DIR					(char*)"../helpers/ie_help"
#define IE_REVERB_PATH							(char*)"../helpers/bangdb-reverb"
#define IE_GET_TEXT_FILES_PROGRAM_NAME			(char*)"service"
#define IE_TOKEN_REL_PROGRAM_NAME				(char*)"ie_helper"
#define IE_TOKEN_REL_FUNC_NAME					(char*)"main"
#define IE_MODEL_RELATION_LIST					(char*)"relation_list"
#define IE_NER_MODEL_ID							(char*)"ner_model_id"
#define IE_REL_FILE_ID							(char*)"rel_file_id"
#define IE_ANNT_FILE_ID							(char*)"annt_file_id"
#define IE_TOKEN_FILE_ID						(char*)"token_file_id"
#define IE_TOKEN_FILE_EXT						(char*)".tokens"
#define IE_ANNOTATION_FILE_EXT					(char*)".annotations"
#define IE_RELATION_FILE_EXT					(char*)".relations"
#define IE_NER_MODEL_DAT_FILE_EXT				(char*)".dat"
#define IE_REL_MODEL_FILE_EXT					(char*)".svm"
#define IE_SENT_LABEL_LIST						(char*)"label_list"
#define IE_ONTO_NODE_STR						(char*)"nodes"
#define IE_ONTO_EDGE_STR						(char*)"edges"
#define IE_ONTO_SUBJ_STR						(char*)"subj"
#define IE_ONTO_PRED_STR						(char*)"pred"
#define IE_ONTO_OBJ_STR							(char*)"obj"
#define IE_ONTO_LBL_STR							(char*)"lbl"
#define IE_ONTO_RELLIST_STR						(char*)".rlist"
#define ML_BASE_PY_DIR							(char*)"../helpers"

#define IE_PYHELP_READ_CLASS_ERROR				(char*)"ERROR_READ_CLASSES_FILE"
#define IE_PYHELP_READ_URL_ERROR				(char*)"ERROR_READ_URL_FILE"
#define IE_PYHELP_NO_VALID_URLS_ERROR			(char*)"ERROR_NOT_VALID_URLS"
#define IE_PYHELP_RETURN_CODE_SUCCESS1			(char*)"SUCCESS_WERR"
#define IE_PYHELP_RETURN_CODE_SUCCESS2			(char*)"SUCCESS"
#define IE_TOKEN_ANNOT_CREATE_ERROR				(char*)"ERROR"
#define IE_TOKEN_ANNOT_CREATE_SUCCESS			(char*)"SUCCESS"

#define ML_BANGDB_KMEANS_STR					(char*)"KMEANS"
#define KMEANS_TYPE_STR							(char*)"kmeans_type"
#define KMEANS_MAX_DICT_SZ						(char*)"max_dict_size"
#define KMEANS_TERMINATION_VAL					(char*)"termination_criteria"
#define KMEANS_DIM_SZ							(char*)"dim"
#define KMEANS_NUM_CENTERS						(char*)"num_centers"
#define KM_NORMALIZE_FILE_EXT					(char*)".norm"
#define KM_CENTROID_FILE_EXT					(char*)".cntr"
#define KM_DATA_RSTATS_FILE_EXT					(char*)".rstats"
#define KM_NORM_FILE_KEY						(char*)"norm"

#define ML_BANGDB_CUSTOM_PY_STR					(char*)"PY"
#define ML_BANGDB_CUSTOM_ARG_LIST				(char*)"arg_list"
#define ML_EXT_TRAIN_FILE_STR					(char*)"train_file"
#define ML_EXT_PRED_FILE_STR					(char*)"pred_file"

#define ML_BANGDB_LIN_STR						(char*)"LIN"

enum ML_BANGDB_SERVER_TYPE
{
	ML_BANGDB_SERVER_TYPE_INVALID = 0,
	ML_BANGDB_SERVER_TYPE_TRAIN,
	ML_BANGDB_SERVER_TYPE_PREDICT,
	ML_BANGDB_SERVER_TYPE_TRAIN_PREDICT,
};

enum ML_BANGDB_ALGO_TYPE
{
	ML_BANGDB_ALGO_TYPE_INVALID = 0,
	ML_BANGDB_ALGO_TYPE_SVM,
	ML_BANGDB_ALGO_TYPE_IE,
	ML_BANGDB_ALGO_TYPE_IE_SENT,
	ML_BANGDB_ALGO_TYPE_IE_TAGS_SUPPORTED,
	ML_BANGDB_ALGO_TYPE_IE_NER_DETECT,
	ML_BANGDB_ALGO_TYPE_IE_WORD_DICT,
	ML_BANGDB_ALGO_TYPE_IE_NER_TRAIN,
	ML_BANGDB_ALGO_TYPE_KMEANS_TRAIN,
	ML_BANGDB_ALGO_TYPE_CUSTOM_EX,
	ML_BANGDB_ALGO_TYPE_LIN,

	//add all other algo type above this line
	ML_MAX_ALGO_TYPE,
};

enum ML_BANGDB_TRAIN_SOURCE
{
	ML_BANGDB_TRAIN_SOURCE_INVALID = 0,
	ML_BANGDB_TRAIN_SOURCE_FILE,
	ML_BANGDB_TRAIN_SOURCE_DIR,
	ML_BANGDB_TRAIN_SOURCE_DOMAIN,
	ML_BANGDB_TRAIN_SOURCE_STREAM,
	ML_BANGDB_TRAIN_SOURCE_TEXT,
};

enum ML_IE_TRAIN_ACTION
{
	ML_IE_TRAIN_ACTION_ALL = 0,
	ML_IE_TRAIN_ONLY_HELP,
	ML_IE_TRAIN_ACTION_SKIP_HELP,
	ML_IE_TRAIN_ACTION_SKIP_KB_TRAIN,
	ML_IE_TRAIN_ACTION_INVALID,
};

enum ML_PREDICT_DATA_TYPE
{
	ML_PREDICT_DATA_TYPE_INVALID = 0,
	ML_PREDICT_DATA_TYPE_FILE,
	ML_PREDICT_DATA_TYPE_EVENT,
};

enum ML_DATA_REFORMAT_TYPE
{
	ML_DATA_REFORMAT_TYPE_NONE = 0,
	ML_DATA_REFORMAT_TYPE_CSV,
	ML_DATA_REFORMAT_TYPE_ARFF,
	ML_DATA_REFORMAT_TYPE_JSON,
	ML_DATA_REFORMAT_JSON_TO_CSV,
	ML_DATA_REFORMAT_TYPE_TSROLLUP,
	ML_DATA_REFORMAT_TYPE_INVALID,	//add other enum val for different format above this
	// todo: need to add libsvm to csv, arff to csv etc
};

enum ML_BANGDB_ATTR_TYPE
{
	ML_BANGDB_ATTR_TYPE_INVALID = 0,
	ML_BANGDB_ATTR_TYPE_NUM,
	ML_BANGDB_ATTR_TYPE_STR,
	ML_BANGDB_ATTR_TYPE_HYBRID,
};

enum ML_BANGDB_TRAIN_SPEED
{
	ML_BANGDB_TRAIN_SPEED_VERYFAST = 1,
	ML_BANGDB_TRAIN_SPEED_FAST,
	ML_BANGDB_TRAIN_SPEED_MEDIUM,
	ML_BANGDB_TRAIN_SPEED_SLOW,
	ML_BANGDB_TRAIN_SPEED_VERYSLOW,
	ML_BANGDB_TRAIN_SPEED_INVALID,
};

enum ML_BANGDB_TRAINING_STATE
{
	//error
	ML_BANGDB_TRAINING_STATE_INVALID_INPUT = 10,
	ML_BANGDB_TRAINING_STATE_NOT_PRSENT,
	ML_BANGDB_TRAINING_STATE_ERROR_PARSE,
	ML_BANGDB_TRAINING_STATE_ERROR_FORMAT,
	ML_BANGDB_TRAINING_STATE_ERROR_BRS,
	ML_BANGDB_TRAINING_STATE_ERROR_TUNE,
	ML_BANGDB_TRAINING_STATE_ERROR_TRAIN,
	ML_FILE_TYPE_ERROR_VAL_TESTDATA,
	ML_FILE_TYPE_ERROR_VAL_TRAINDATA,
	ML_BANGDB_TRAINING_STATE_LIMBO,
	//intermediate states
	ML_BANGDB_TRAINING_STATE_BRS_GET_PENDING,
	ML_BANGDB_TRAINING_STATE_BRS_GET_DONE,
	ML_BANGDB_TRAINING_STATE_REFORMAT_DONE,
	ML_BANGDB_TRAINING_STATE_SCALE_TUNING_DONE,
	ML_BANGDB_TRAINING_STATE_BRS_MODEL_UPLOAD_PENDING,
	//training done
	ML_BANGDB_TRAINING_STATE_TRAINING_DONE,	//25
	ML_BANGDB_TRAINING_STATE_DEPRICATED,
};

enum ML_BANGDB_PRED_STATE
{
	ML_BANGDB_PRED_STATE_INVALID_INPUT = 10,
	ML_BANGDB_PRED_STATE_NOT_PRESENT,
	ML_BANGDB_PRED_STATE_ERROR_PARSE,
	ML_BANGDB_PRED_STATE_ERROR_FORMAT,
	ML_BANGDB_PRED_STATE_ERROR_BRS_FETCH,
	ML_BANGDB_PRED_STATE_ERROR_FILE_FORMAT,
	ML_BANGDB_PRED_STATE_ERROR_FILE_REFORMAT,
	ML_BANGDB_PRED_STATE_ERROR_FILE_TUNE,
	ML_BANGDB_PRED_STATE_ERROR_PREDICT,
	ML_BANGDB_PRED_STATE_LIMBO,
	ML_BANGDB_PRED_STATE_BRS_FETCH_PENDING,
	ML_BANGDB_PRED_STATE_BRS_FETCH_DONE,
	ML_BANGDB_PRED_STATE_REFORMAT_DONE,
	ML_BANGDB_PRED_STATE_TUNE_DONE,
	ML_BANGDB_PRED_STATE_BRS_PUT_DONE,
	ML_BANGDB_PRED_STATE_PREDICT_DONE, //25
	ML_BANGDB_PRED_STATE_DEPRICATED
};

enum ML_BANGDB_ML_DATA_FORMAT
{
	ML_BANGDB_ML_DATA_FORMAT_LIBSVM = 0,
	ML_BANGDB_ML_DATA_FORMAT_CSV,
	ML_BANGDB_ML_DATA_FORMAT_ARFF,
	ML_BANGDB_ML_DATA_FORMAT_JSON,
	ML_BANGDB_ML_DATA_FORMAT_INVALID,
};

enum BANGDB_TS_DATA_GRAN
{
	BANGDB_TS_DATA_GRAN_NONE = 0,
	BANGDB_TS_DATA_GRAN_DAY,
	BANGDB_TS_DATA_GRAN_WEEK,
	BANGDB_TS_DATA_GRAN_MONTH,
	BANGDB_TS_DATA_GRAN_YEAR
};

enum BANGDB_DATA_AGGR_TYPE
{
	BANGDB_DATA_AGGR_TYPE_COUNT = 1,
	BANGDB_DATA_AGGR_TYPE_SUM,
	BANGDB_DATA_AGGR_TYPE_AVG
};

enum BANGDB_TS_DATA_TYPE
{
	BANGDB_TS_DATA_TYPE_STRING = 5,
	BANGDB_TS_DATA_TYPE_LONG = 9,
	BANGDB_TS_DATA_TYPE_DOUBLE = 11
};

struct svm_feautre_order_node
{
	char *feature;
	short position;
	short flen;
	short reserved;
	short dtype;	//5 for string, 9 for long and 11 for double
};

struct svm_feature_order_node_list
{
	svm_feautre_order_node *list;
	int nitems;
};


//types of db
enum PersistType
{
	INMEM_ONLY,			//only RAM based, cache enabled (no overflow to disk, ideally overflow to other RAM)
	INMEM_PERSIST,		//disked backed, cache enabled (over flow to disk)
	PERSIST_ONLY,		//cache disabled, direct file IO
	INVALID_PERSIST_TYPE
};

//types of index
enum IndexType
{
	HASH,
	EXTHASH,
	BTREE,
	HEAP,
	INVALID_INDEX_TYPE,
};

//log type
enum LogType
{
	SHARED_LOG,
	PRIVATE_LOG,
	INVALID_LOG
};

//how should we access db, various ways
enum OpenType
{
	OPENCREATE,
	TRUNCOPEN,
	JUSTOPEN
};

//how should db be closed
enum CloseType
{
	DEFAULT,
	CONSERVATIVE,
	OPTIMISTIC,
	CLEANCLOSE,
	SIMPLECLOSE,
};

//the insert options
enum InsertOptions
{
	INSERT_UNIQUE,		//if non-existing then insert else return
	UPDATE_EXISTING,	//if existing then update else return
	INSERT_UPDATE,		//insert if non-existing else update
	DELETE_EXISTING,	//delete if existing
	UPDATE_EXISTING_INPLACE, //only for inplace update
	INSERT_UPDATE_INPLACE, //only for inplace update
};

enum TransactionType
{
	DB_TRANSACTION_NONE,
	DB_OPTIMISTIC_TRANSACTION,
	DB_PESSIMISTIC_TRANSACTION,
};

enum TableSizeHint
{
	TINY_TABLE_SIZE,
	SMALL_TABLE_SIZE,
	NORMAL_TABLE_SIZE,
	BIG_TABLE_SIZE,
	TABLE_SIZE_INVALID,
};

enum TableType
{
	/* index and data files with opaque (void*) key */
	NORMAL_TABLE,
	WIDE_TABLE,
	INDEX_TABLE,			//opaque(void*) as key and dataoff, datlen is of actual value in the data file store in main table
							//data is in same index file if dupl is not allowed, else data (as dofft) is in data file in chunk of 32 with link at the end
	/* no data file for following tables */
	PRIMITIVE_TABLE_INT,	//int as key and int as val, stored in index file only, no data file
	PRIMITIVE_TABLE_LONG,	//long as key and long as val, stored in index file only, no data file
	PRIMITIVE_TABLE_STRING,	//opaque(void*) as key and data stored in the index only, no data file - Fixed Table

	LARGE_TABLE,

	BANGDB_TABLE_INVALID
};

enum TableSubType
{
	BANGDB_SW_TABLE,
	BANGDB_TOPK_TABLE,
	NON_ANALYTICAL_TABLE,
	//SW_ENTITY_COUNT_TABLE,
	//SW_GROUPBYOP_TABLE,
	INDEXBTREE_TABLE,	// this is to override the selection of idx table, right now only for non_dupl keys index_table is selected
	DUPLINDEX_TABLE_NOLOG,	// this is to override the selection of idx table, right now only for dupl keys dupl_index is selected
	BANGDB_SW_INVALID,
};

enum PrimitiveDataType
{
	PRIMITIVE_INT,
	PRIMITIVE_LONG,
	PRIMITIVE_STRING,
	PRIMITIVE_INVALID,
};

enum ScanLimitBy
{
	// Adding the below LIMIT_INVALID to use it as a default parameter.
	LIMIT_INVALID = -1,
	LIMIT_RESULT_SIZE,
	LIMIT_RESULT_ROW,
};

enum ScanOperator
{
	GT,
	GTE,
	LT,
	LTE,
	EQ,
	NE
};

enum JoinOperator
{
	JO_INVALID = -1,
	JO_AND = 0,
	JO_OR = 1,
};

//currently just supporting whether data is valid or invalid
//later we can leverage this for versioning as well
enum VersionType
{
	BANGDB_DATA_VERSION_OFF, //no version (current default)
	BANGDB_DATA_VERSION_VALID_INVALID, //db will mark data as valid or invalid
	BANGDB_DATA_VERSION_ON,	//this is not supported as of now
};

enum SortMethod
{
	LEXICOGRAPH = 1,
	QUASI_LEXICOGRAPH = 2,
	SORT_METHOD_INVALID = 100,
};

enum SortDirection
{
	SORT_ASCENDING = 3,
	SORT_DESCENDING = 4,
    SORT_INVALID
};

enum KeyType
{
	NORMAL_KEY = 1,		//opaque (void*) as key
	COMPOSITE_KEY = 3,	//always treated as opaque even if it is of long:void* or long:long
	NORMAL_KEY_LONG = 10,	//long as key
	//COMPOSITE_KEY_LONG,	//long:long as key, all keys participating in composite will be long, no hybrid keys
	KEY_TYPE_INVALID = 100,
};

struct FDT
{
	FDT();
	FDT(const char *_data);
	FDT(const char *_data, uint _len);
	FDT(void *_data, uint _len);
	FDT(long _data, uint _len);
	void reset();
	void free(bool fixed_sz_key = false);
	~FDT();

	long length;
	void *data;
	short _fixed_sz_data;
	short _should_del;
};


void _set_fdt(FDT *fdt, const char *key, int len = 0);
void _set_fdt(FDT *fdt, long key);

#define CHECK_OPEN_RET(o,x) \
  if (!o) { \
	  err_ret("object is not initialized.."); \
	  return x; \
  }
#define CHECK_OPEN_RET_VOID(o) \
  if (!o) { \
	  err_ret("object is not initialized.."); \
	  return; \
  }

char *Itoa(int i);
char *Ltoa(long l);
char *Strncat(const char *s, int a);
char *Strncat(const char *s1, const char *s2);
char *Strncpy(const char *s);
char *Strncpy(const char *s, int len);
char *makeComposite_long_long(ulong k1, ulong k2);
int makeComposite_long_long(ulong k1, ulong k2, char *buf, int buflen);
int makeComposite_long(ulong k1, char *buf, int buflen, short stage);
int makeComposite_double(double k1, char *buf, int buflen, short stage);
int makeComposite_str(char *k1, char *buf, int buflen, short stage);
int makeComposite_long_long_long(ulong k1, ulong k2, ulong k3, char *buf, int buflen);
int makeComposite_str_long_long(char *k1, ulong k2, ulong k3, char *buf, int buflen);
char *makeComposite_str_str(char *k1, char *k2);
char *makeComposite_str_str(void *k1, int l1, void *k2, int l2);
char *makeComposite_long_str(ulong k1, char *k2);
char *makeComposite_long_str(ulong k1, char *k2, int l2);
char *makeComposite_str_long(char *k1, ulong k2);
char *makeComposite_str_long(void *k1, int l1, ulong k2);
long filesize(const char *fname);
unsigned long uniqueTimeStamp();
unsigned long getCurrentTime();
unsigned long subTime(long microsec);
void sleep_us(unsigned long microsec);
void *double_ptr(double x);
void *long_ptr(long x);
double get_double(void *x);
long get_long(void *x);
long readFileContent(const char *fname, char buf[], int max_buf_len);
uint hash_string_32(const char *s, int slen);
ulong hash_string_64(const char *s, int slen);
char* form_training_key_name(const char *model_name, const char *account_id, const char *train_data);
char *form_model_key_name(const char *modelName, const char *accountName);
char *get_full_path(const char *base_path, const char *train_data, bool fileDir);
char *get_file_name_path(const char *basepath, const char *filename, const char *fileext);
char *get_udf_logic_file(const char *udf_name);

char* geohashEncode(double lat, double lng, int precision);


void bangdb_print_error(int errnum);
void bangdb_print_last_error();
char *bangdb_add_error_info(const char *info, int ecode = -1);
char *bangdb_add_error_info(const char *info_fmt, long x, int ecode = -1);
char *bangdb_add_error_info(const char *info_fmt, const char *x, int ecode = -1);
int bangdb_check_error_code(char *err_json);


/* connection */
const int BANGDB_ERR_WALOG_BAD_PERSIST_TYPE = -1;		//BANGDB_ERR_00_02_001
const int BANGDB_ERR_IDX_TYPE_NOT_SUPPORTED = -2;		//BANGDB_ERR_00_02_002
const int BANGDB_ERR_TBLENV_IDX_NULL = -3;				//BANGDB_ERR_00_02_003
const int BANGDB_ERR_IDX_INIT = -4;						//BANGDB_ERR_00_02_004
const int BANGDB_ERR_HKEEP_WALOG = -5;					//BANGDB_ERR_00_02_005
const int BANGDB_ERR_HKEEP_BP = -6;						//BANGDB_ERR_00_02_006
const int BANGDB_ERR_PARAM_NULL = -7;					//BANGDB_ERR_00_02_007
const int BANGDB_ERR_TXN_NULL = -8;						//BANGDB_ERR_00_02_008
const int BANGDB_ERR_TENV_KEYTYPE = -9;					//BANGDB_ERR_00_02_009
const int BANGDB_ERR_TENV_KEYTYPE_PRIM = -10;			//BANGDB_ERR_00_02_010 - NOTUSED
const int BANGDB_ERR_KEY_SIZE = -11;					//BANGDB_ERR_00_02_011
const int BANGDB_ERR_VAL_SIZE = -12;					//BANGDB_ERR_00_02_012
const int BANGDB_ERR_TXN_ON = -13;					//BANGDB_ERR_00_02_013
const int BANGDB_ERR_TXN_INV = -14;					//BANGDB_ERR_00_02_014
const int BANGDB_ERR_DATVAR_BUF_OVFW = -15;			//BANGDB_ERR_00_02_015
const int BANGDB_ERR_DATVAR_OFFT_OVFW = -16;		//BANGDB_ERR_00_02_016
const int BANGDB_ERR_JSON_PARSE = -17;				//BANGDB_ERR_00_02_017
const int BANGDB_ERR_COMMIT_CONCUR_TXN = -18;		//BANGDB_ERR_00_02_018	-NOTUSED
const int BANGDB_ERR_TXN_NOT_SUPPORTED = -19;		//BANGDB_ERR_00_02_019
const int BANGDB_ERR_DATVAR_NOT_SUPPORTED = -20;	//BANGDB_ERR_00_02_020	-NOTUSED
const int BANGDB_ERR_API_NOT_SUPPORTED = -21;		//BANGDB_ERR_00_02_021	-NOTUSED
const int BANGDB_FLTR_NS_NORMAL_TABLE = -22;
const int BANGDB_PUT_DOC_NULL_ERR = -23;
const int BANGDB_PUT_KEY_VAL_NULL_ERR = -24;
const int BANGDB_PUT_NUMIDX_INVALID = -26;
const int BANGDB_TABLE_ENV_VERIFY_ERROR = -27;

/* database */
const int BANGDB_ERR_TXN_TYPE_NOT_SUPPORTED = -51;	//BANGDB_ERR_00_00_001	-NOTUSED
const int BANGDB_ERR_BP_SIZE_LESS = -52;			//BANGDB_ERR_00_00_002
const int BANGDB_ERR_DB_METAFILE_VERF = -53;			//BANGDB_ERR_00_00_003
const int BANGDB_ERR_DB_METAFILE_OPEN = -54;			//BANGDB_ERR_00_00_004
const int BANGDB_ERR_CREATE_TABLE = -55;				//BANGDB_ERR_00_00_005
const int BANGDB_ERR_DB_NONTXN_MODE = -56;				//BANGDB_ERR_00_00_007
const int BANGDB_ERR_INV_TXN_HANDLE = -57;				//BANGDB_ERR_00_00_007
const int BANGDB_ERR_TXN_HANDLE_NOT_FOUND = -58;			//BANGDB_ERR_00_00_008
const int BANGDB_ERR_NULL_TXN_HANLDE = -59;				//BANGDB_ERR_00_00_009
const int BANGDB_ERR_NULL_TABLE = -60;					//BANGDB_ERR_00_00_010
const int BANGDB_ERR_CLOSE_TABLE = -61;					//BANGDB_ERR_00_00_011
const int BANGDB_ERR_LOG_FLUSH = -62;					//BANGDB_ERR_00_00_012
const int BANGDB_ERR_LOG_CLOSE = -63;					//BANGDB_ERR_00_00_013
const int BANGDB_ERR_OPEN_IDX_FILES = -64;				//BANGDB_ERR_00_00_016
const int BANGDB_ERR_DB_NOT_AVAIL = -65;				//BANGDB_ERR_00_00_017
const int BANGDB_ERR_DB_NAME_NULL = -66;				//BANGDB_ERR_00_00_018
const int BANGDB_ERR_DB_NAME_ALREADY_EXIST = -67;		//BANGDB_ERR_00_00_019
const int BANGDB_ERR_INV_USER_INFO = -68;				//BANGDB_ERR_00_00_020
const int BANGDB_ERR_MAX_TABLE_RCHD = -69;
const int BANGDB_ERR_OPEN_FILE	= -70;
const int BANGDB_ERR_CREATE_FILE = -71;
const int BANGDB_ERR_DB_INIT= -72;
const int BANGDB_ERR_TBL_ENV_INCORRECT = -73;
const int BANGDB_ERR_LOCK_FILE	= -74;
const int BANGDB_ERR_UNLOCK_FILE	= -75;

/* table */
const int BANGDB_ERR_INV_OPENFLAG = -101;				//BANGDB_ERR_00_01_001
const int BANGDB_ERR_NUM_CONN_EXCEED = -102;				//BANGDB_ERR_00_01_002
const int BANGDB_ERR_INIT_CONN = -103;				//BANGDB_ERR_00_01_003
const int BANGDB_ERR_DUMPDATA_FILES = -104;				//BANGDB_ERR_00_01_004
const int BANGDB_ERR_DUMPDATA_HDR = -105;				//BANGDB_ERR_00_01_005
const int BANGDB_ERR_NULL_CONN_CLOSE = -106;				//BANGDB_ERR_00_01_006
const int BANGDB_ERR_CONN_CLOSE = -107;				//BANGDB_ERR_00_01_007
const int BANGDB_ERR_TBL_NOT_FOUND_BUFFCHE = -108;				//BANGDB_ERR_00_01_008
const int BANGDB_ERR_BUFF_POOL_CLOSE = -109;				//BANGDB_ERR_00_01_009
const int BANGDB_ERR_WAL_CLOSE = -110;				//BANGDB_ERR_00_01_010
const int BANGDB_ERR_TBL_IMPL_CLOSE = -111;				//BANGDB_ERR_00_01_011
const int BANGDB_ERR_TBL_META_WRITE = -112;				//BANGDB_ERR_00_01_012
const int BANGDB_ERR_IDX_RECREATE_IN_PROG = -113;				//BANGDB_ERR_00_01_013
const int BANGDB_ERR_CONN_FOR_PRIM_TBL = -114;				//BANGDB_ERR_00_01_014
const int BANGDB_ERR_CONN_FOR_NORM_TBL = -115;				//BANGDB_ERR_00_01_015
const int BANGDB_ERR_TBL_NOT_AVAIL = -116;				//BANGDB_ERR_00_01_016
const int BANGDB_ERR_CONN_TBL_STATE_CLOSE = -117;				//BANGDB_ERR_00_01_017
const int BANGDB_ERR_TABLE_STATE_OPEN = -118;				//BANGDB_ERR_00_01_018
const int BANGDB_ERR_TABLE_NAME_NULL = -119;				//BANGDB_ERR_00_01_023
const int BANGDB_ERR_TABLE_ENV_NULL = -120;				//BANGDB_ERR_00_01_024
const int BANGDB_ERR_TABLE_TYPE_INV = -121;				//BANGDB_ERR_00_01_025
const int BANGDB_ERR_PRIM_DATATYPE_INV = -122;				//BANGDB_ERR_00_01_026
const int BANGDB_ERR_IDX_NOT_SUPPORTED = -123;				//BANGDB_ERR_00_01_027
const int BANGDB_ERR_NOT_SUPPORTED_TABLETYPE = -124;
const int BANGDB_ERR_CONN_NULL = -125;
const int BANGDB_ERR_DATATYPE_MISMATCH = -126;
const int BANGDB_ERR_TABLE_STATE_CLOSED = -127;
const int BANGDB_ERR_TABLE_VERIFY_ERROR = -128;

/* swTable, swTableUnit, swEntityCount */
const int BANGDB_ERR_SWMGR_INIT_ERROR	= -150;
const int BANGDB_ERR_SWENT_COUNT_CREATE = -151;				//BANGDB_ERR_00_60_001
const int BANGDB_ERR_SWENT_NOT_AVAIL = -152;				//BANGDB_ERR_00_01_020
const int BANGDB_ERR_SWENT_STATE_OPEN = -153;				//BANGDB_ERR_00_01_022
const int BANGDB_ERR_SWTABLE_CREATE = -154;				//BANGDB_ERR_00_61_001
const int BANGDB_ERR_SWENT_STATE_CLOSE = -155;				//BANGDB_ERR_00_01_021
const int BANGDB_ERR_SWTABLE_OPEN_ARCHIVE	= -156;
const int BANGDB_ERR_SWTABLE_SCAN	= -157;
const int BANGDB_ERR_SWTABLE_INV_CALL = -158;
const int BANGDB_ERR_SWTABLE_REGISTER = -159;
const int BANGDB_ERR_SWMGR_CLOSE_ERROR = -160;

/* STREAM */
const int BANGDB_ERR_STREAM_DDL_LOCK = -181;
const int BANGDB_ERR_STREAM_DML_LOCK = -182;
const int BANGDB_BSM_NOT_AVAIL_ERR = -183;
const int BANGDB_NMGR_NOT_AVAIL_ERR = -184;

/* wideTable */
const int BANGDB_ERR_TABLE_STATE_CLOSED_IDX = -201;				//BANGDB_ERR_00_63_001
const int BANGDB_ERR_CREATE_IDX = -202;				//BANGDB_ERR_00_63_002
const int BANGDB_ERR_CREATE_CONN = -203;				//BANGDB_ERR_00_63_003
const int BANGDB_ERR_CREATE_CONN_IDX = -204;				//BANGDB_ERR_00_63_004
const int BANGDB_ERR_CONN_OPEN_IDX_DROP = -205;				//BANGDB_ERR_00_63_005
const int BANGDB_ERR_IDX_NOT_AVAIL = -206;				//BANGDB_ERR_00_63_006
const int BANGDB_ERR_CONN_OPEN_IDX_CREATE = -207;				//BANGDB_ERR_00_63_007
const int BANGDB_ERR_IDX_REBUILD_FAILED = -208;				//BANGDB_ERR_00_63_008

/* for user id/pwd related */
const int BANGDB_ERR_USER_ALREADY_AVAIL	= -301;				//BANGDB_ERR_00_65_001
const int BANGDB_ERR_USER_NOT_AVAIL	= -302;				//BANGDB_ERR_00_65_002
const int BANGDB_ERR_USERID_LEN_OVERFLOW	= -303;				//BANGDB_ERR_00_65_003
const int BANGDB_ERR_PWD_LEN_OVERFLOW	= -304;				//BANGDB_ERR_00_65_004
const int BANGDB_ERR_USER_TYPE_INV	= -305;				//BANGDB_ERR_00_65_005
const int BANGDB_ERR_PWD_INV	= -306;				//BANGDB_ERR_00_65_006
const int BANGDB_ERR_USER_NOT_ADMIN	= -307;				//BANGDB_ERR_00_65_007

/* Communication/protocol/timeout [socket layer in-general] errors */
const int BANGDB_ERR_00_80_001 = -351;    // client-side read-query-TIMEOUT										//BANGDB_ERR_00_80_001
const int BANGDB_ERR_00_80_002 = -352;    // No route to host													//BANGDB_ERR_00_80_002
const int BANGDB_ERR_00_80_003 = -353;    // Connection reset by peer											//BANGDB_ERR_00_80_003
const int BANGDB_ERR_00_80_004 = -354;    // Error in reading from/writing to socket							//BANGDB_ERR_00_80_004

//ML related
const int BANGDB_ML_HELPER_NOT_AVAIL		= -501;
const int ML_PARAM_JSON_PARSE_ERROR			= -502;
const int ML_PARAM_ALGO_TYPE_MISSING		= -503;
const int ML_PARAM_WRONG_ALGO_TYPE			= -504;
const int ML_PARAM_WRONG_ATTR_TYPE			= -505;
const int ML_PARAM_ALGO_LIST_ERROR			= -506;
const int ML_PARAM_SCALE_TYPE_MISSING		= -507;
const int ML_PARAM_TUNE_TYPE_MISSING		= -508;
const int ML_PARAM_TRAIN_TYPE_ERROR			= -509;
const int ML_TRAIN_SOURCE_MISSING_ERROR		= -510;
const int ML_TRAIN_SOURCE_TYPE_ERROR		= -511;
const int ML_PARAM_ATTR_INFO_ERROR			= -512;
const int ML_PARAM_ATTR_NAME_ERROR			= -513;
const int ML_PARAM_ATTR_ORDER_ERROR			= -514;
const int ML_PARAM_ATTR_TYPE_ERROR			= -515;
const int ML_PARAM_TRAIN_INFO_MISSING_ERROR	= -516;
const int ML_PREDICT_PARAM_DATA_TYPE_INVALID= -517;
const int ML_DATA_FORMAT_TYPE_ERROR			= -518;
const int ML_PARAM_MODEL_NAME_TYPE_ERROR	= -519;
const int ML_DATA_FORMAT_ERROR				= -520;
const int ML_DATA_FORMAT_NOT_SUPPORTED		= -521;
const int ML_WRONG_SVM_TYPE_ERROR			= -522;
const int ML_WRONG_KERNEL_TYPE_ERROR		= -523;
const int ML_PARAM_MODEL_NAME_MISSING_ERROR	= -524;
const int ML_GET_MODEL_ERROR				= -525;
const int ML_GET_MODEL_SIZE_ERROR			= -526;
const int ML_GET_DATA_FILE_ERROR			= -527;
const int ML_MODEL_PRE_TRAIN_ERROR			= -528;
const int ML_TRAIN_PARAM_RETRIEVAL_ERROR	= -529;
const int ML_BANGDB_SVM_TRAIN_ERROR			= -530;
const int ML_BRS_TRAIN_DATA_GET_ERROR		= -531;
const int ML_ACCID_MISSING_ERROR			= -532;
const int ML_PREDICT_DATA_MISSING_ERROR		= -533;
const int ML_BRS_NULL_ERROR					= -534;
const int ML_GET_PARAM_DATA_ERROR			= -535;
const int ML_MODEL_FILE_LOAD_ERROR			= -536;
const int ML_GET_RANGE_FILE_ERROR			= -537;
const int ML_FILE_REFORMAT_ERROR			= -538;
const int ML_REQ_STATUS_ERROR				= -539;
const int ML_REQ_NOT_AVAIABLE				= -540;
const int ML_REQ_TRAIN_ALREADY_INPROG		= -541;
const int ML_REQ_TRAIN_STATE_INVALID		= -542;
const int ML_REQ_TRAIN_INPUT_ERROR			= -543;
const int ML_TRAIN_FILE_SZ_ERROR			= -544;
const int ML_TRAIN_MEM_BUDEGT_ERROR			= -545;
const int ML_PRED_ERROR_CODE_MISSING		= -546;
const int ML_PRED_OUT_JSON_PARSE_ERROR		= -547;
const int ML_PRED_GENERAL_ERROR				= -548;
const int ML_REINIT_PARAM_ERROR				= -549;
const int ML_REINIT_PARAM_INDENTICAL		= -550;
const int ML_REINIT_ROLL_BACK_DONE			= -551;

const int ML_IE_CLASS_NAME_MISSING_ERROR	= -552;
const int ML_IE_GET_TOKEN_PRE_TRAIN			= -553;
const int ML_IE_GET_FIX_REL_PRE_TRAIN		= -554;
const int ML_IE_TOTAL_FETAURE_EX_FILE_ERROR	= -555;
const int ML_IE_TOTAL_FETAURE_EX_BRS_ERROR	= -556;
const int ML_IE_NER_MODEL_BRS_ERROR			= -557;
const int ML_IE_REL_TRAIN_ERROR				= -558;
const int ML_IE_PY_HELPER_ERROR				= -559;
const int ML_BASE_DIR_CREATE_ERROR			= -560;
const int ML_IE_TK_AN_RE_BRS_ERROR			= -561;
const int ML_TRAIN_ACTION_ERROR				= -562;
const int ML_UPDATE_REQ_PHHELP_ERROR		= -563;
const int ML_REQ_TRAIN_STATE_NOT_PRESENT	= -564;
const int ML_IE_NO_RELATION_PRESENT_ERROR	= -565;
const int ML_IE_SENTI_LABEL_ERROR			= -566;
const int ML_IE_REL_LIST_UPLOAD_ERROR		= -567;
const int ML_IE_GET_RELLIST_FILE_ERROR		= -568;
const int ML_PREDICT_DATA_TOO_BIG_ERROR		= -569;
const int ML_FILE_TYPE_IMPROPER_ERROR		= -570;
const int ML_NER_MODEL_FILE_NOT_PRESENT		= -571;
const int ML_WORD_DICT_DATA_FOLDER_ERROR	= -572;
const int ML_WORD_DICT_TRAIN_ERROR			= -573;
const int ML_KMEANS_INIT_ERROR				= -574;
const int ML_KEAMNS_SET_TRAIN_DATA_ERROR	= -575;
const int ML_KMEANS_PERSIST_ERROR			= -576;

const int ML_UDF_APPLY_ERROR				= -577;
const int ML_UDF_BRS_GET_ERROR				= -578;
const int ML_IE_NER_MODEL_DSLZ_ERROR		= -579;
const int ML_IE_NER_MODEL_LOAD_SL_ERROR		= -580;
const int ML_CUSTOM_ARG_LIST_ERROR			= -581;
const int ML_EXT_TRAIN_FILE_ERROR			= -582;
const int ML_EXT_PRED_FILE_ERROR			= -583;
const int ML_CUSTOM_COMP_APPLY_ERROR		= -584;

const int ML_REQ_PRED_ALREADY_INPROG		= -585;
const int ML_REQ_PRED_STATE_INVALID			= -586;
const int ML_REQ_PRED_INPUT_ERROR			= -587;

const int ML_PYTHON_FILE_NOT_FOUND			= -588;
const int ML_PYTHON_EXEC_ERROR				= -589;

const int BANGDB_LRU_INIT_ERROR				= -671;
const int BANGDB_LRU_CLOSE_ERROR			= -672;
const int BANGDB_LRU_NODE_PRESENT_ERROR		= -673;
const int BANGDB_LRU_BUDGET_FULL_ERROR		= -674;
const int BANGDB_LRU_NO_FREE_NODE_ERROR		= -675;

/* general */
const int BANGDB_ERR_OP_NOT_SUPPORTED	= -1024;
}

#endif /* SRC_HEADERS_BANGDBCOMMON_H_ */
