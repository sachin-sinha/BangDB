/*
 * BangDBDatabase.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBDATABASE_H_
#define SRC_BANGDBDATABASE_H_

#include "BangDBTable.h"
#include "DBParam.h"

namespace BangDB
{
class BangDBDatabase {
public:

	BangDBDatabase(const char *dbName, DBParam *dbParam = NULL);

	BangDBTable *getTable(const char *tblName, TableEnv *tblenv = NULL, OpenType openflag = OPENCREATE);

	void beginTransaction(Transaction *txn);

	long commitTransaction(Transaction *txn);

	void abortTransaction(Transaction *txn);

	int dumpData();

	int dropTable(BangDBTable **tbl);

	short doesTableExist(const char *tblName, long tblId = 0, bool check_on_fs = false);

	long getNumTables(int flag = 1);

	const char *getTableList();

	const char *getStats(bool verbose = true);

	const char *getTableStats(const char *tblName, bool verbose);

	DBParam *getParam();

	const char *getName();

	TableType getTableType(const char *tblName, long tblId = 0);

	TableEnv *getTableEnv(const char *tblName, long tblId = 0);

	long getTableId(const char *tblName);

	void closeDatabase(CloseType dbclose = DEFAULT);

	bool isValid();

	virtual ~BangDBDatabase();

	long ptdb;

private:

	BangDBDatabase();
};
}
#endif /* SRC_BANGDBDATABASE_H_ */
