/*
 * BangDBGraphManager.h
 *
 *  Created on: May 15, 2021
 *      Author: sachin
 */

#ifndef SRC_BANGDBGRAPHMANAGER_H_
#define SRC_BANGDBGRAPHMANAGER_H_

#include "BangDBDatabase.h"
#include "BangDBMLHelper.h"
#include "BangDBGraphTable.h"

namespace BangDB_Client
{
class BangDBGraphTable;

class BangDBGraphManager {
public:
	BangDBGraphManager(BangDBDatabase *bdb);

	BangDBGraphTable *getGraphTable(const char *tableName, bool createTable = true);

	char *listGraphs();

	void closeGraphTable(BangDBGraphTable **tbl);

	int closeGraphManager(bool force = false);

	virtual ~BangDBGraphManager();
private:
	long ptgphmgr;
};
}
#endif /* SRC_BANGDBGRAPHMANAGER_H_ */
