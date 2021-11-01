/*
 * BangDBGraphTable.h
 *
 *  Created on: May 15, 2021
 *      Author: sachin
 */

#ifndef SRC_BANGDBGRAPHTABLE_H_
#define SRC_BANGDBGRAPHTABLE_H_

#include "BangDBGraphManager.h"

namespace BangDB_Client
{
class BangDBGraphTable {
public:
	// {label:"person",name:"sachin",prop:{}}
	long addNode(const char *node);

	// triple = {sub:{label:"person",name:"sachin",prop:{}},pred:{rel:"myrel", prop:{}},obj:{label:"person",name:"sachin",prop:{}}}
	long addTriple(const char *triple);

	char *runQuery(const char *qry);

private:
	BangDBGraphTable(long _ptgphtbl);

	virtual ~BangDBGraphTable();

	long ptgphtbl;

	friend class BangDBGraphManager;
};
}

#endif /* SRC_BANGDBGRAPHTABLE_H_ */
