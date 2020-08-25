/*
 * BangDBTable.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBTABLE_H_
#define SRC_BANGDBTABLE_H_

#include <BangDBTransaction.h>
#include "TableEnv.h"
#include "ScanFilter.h"
#include "ResultSet.h"

namespace BangDB_Client
{
class BangDBTable {
public:

	int closeTable(CloseType tblCloseType = DEFAULT_AT_CLIENT);

	int addIndex(const char *idxName, TableEnv *tenv);

	//always creates index with following property BTREE, INMEM_PERSIST, QUASI_LEXICOGRAPH, SORT_ASCENDING, log = off
	int addIndex_str(const char *idxName, int idx_size, bool allowDuplicates);

	int addIndex_num(const char *idxName, bool allowDuplicates);

	int dropIndex(const char *idxName);

	bool hasIndex(const char *idxName);

	TableEnv *getTableEnv();

	int dumpData();

	const char *getName();

	const char *getTableDir();

	IndexType getIndexType();

	const char *getStats(bool verbose = true);

	/* connection or CRUD API */
	// for files - supported only for LARGE_TABLE
	long putFile(const char *key, const char *file_path, InsertOptions iop);

	long getFile(const char *key, const char *fname, const char *fpath);

	long putLargeData(const char *key, void *val, long vallen, InsertOptions iop);

	long getLargeData(const char *key, void **buf, long *vallen);

	char *listLargeDataKeys(const char *key, int list_size_mb = 0);	//todo: make it recursive, should have flag set in the json itself

	int countSliceLargeData(const char *key);

	long countLargeData();

	int delLargeData(const char *key);

	long put(FDT *key, FDT *val, InsertOptions flag = INSERT_UNIQUE, Transaction *txn = NULL);

	ResultSet *scan(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, ScanFilter *sf = NULL, Transaction *txn = NULL);

	// for text data
	// reverse indexes the data (str)
	// FDT *key, if null then timestamp
	long putText(const char *text, int textlen, FDT *k = NULL, InsertOptions flag = INSERT_UNIQUE);

	ResultSet *scanText(const char *wlist[], int nfilters, bool intersect = false);

	long putDoc(const char *doc, FDT *pk = NULL, const char *rev_idx_fields_json = NULL, InsertOptions flag = INSERT_UNIQUE);

	ResultSet *scanDoc(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	int get(FDT *key, FDT **val, Transaction *txn = NULL);

	long del(FDT *key, Transaction *txn = NULL);

	long count(FDT *pk_skey, FDT *pk_ekey, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	long expCount(FDT *skey, FDT *ekey);

	long count();

	//void printStats();

	void setAutoCommit(bool flag);

	TableType getTableType();

	bool isSameAs(BangDBTable *tbl);

	virtual ~BangDBTable();

private:

	BangDBTable(long tbl);

	long pttbl;

	friend class BangDBDatabase;
};
}
#endif /* SRC_BANGDBTABLE_H_ */
