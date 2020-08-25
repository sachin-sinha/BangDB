/*
 * BangDBDatabase.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBDATABASE_H_
#define SRC_BANGDBDATABASE_H_

#include "BangDBEnv.h"
#include "BangDBTable.h"
#include "DBParam.h"

namespace BangDB_Client
{
class BangDBDatabase {
public:

	BangDBDatabase(const char *dbName, BangDBEnv *env, DBParam *dbParam = NULL);

	BangDBTable *getTable(const char *tblName, TableEnv *tblenv = NULL, OpenType openflag = OPENCREATE);

	void beginTransaction(Transaction *txn);

	long commitTransaction(Transaction *txn);

	void abortTransaction(Transaction *txn);

	int dumpData();

	int dropTable(BangDBTable **tbl);

	short doesTableExist(const char *tblName, long tblId = 0);

	long getNumTables(int flag = 1);

	const char *getTableList();

	const char *getStats(bool verbose = true);

	const char *getTableStats(const char *tblName, bool verbose);

	DBParam *getParam();

	const char *getName();

	TableType getTableType(const char *tblName, long tblId = 0);

	TableEnv *getTableEnv(const char *tblName, long tblId = 0);

	long getTableId(const char *tblName);

	bool isValid();

	virtual ~BangDBDatabase();

	long ptdb;

private:

	BangDBDatabase();
};
}
#endif /* SRC_BANGDBDATABASE_H_ */
