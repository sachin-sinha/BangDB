/*
 * ResultSet.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_RESULTSET_H_
#define SRC_RESULTSET_H_

#include "BangDBCommon.h"

namespace BangDB
{
class ResultSet {
public:
	ResultSet();
	ResultSet(long rs);
	bool moreDataToCome();
	int count();
	void begin();
	void beginReverse();
	bool hasNext();
	void moveNext();
	FDT *getNextKey();
	FDT *getNextVal();
	char *getNextKeyStr();
	int getNextKeyLen();
	char *getNextValStr();
	int getNextValLen();;
	long getNextKeyLong();
	long getNextValLong();
	bool isKeyString();
	bool isValString();
	FDT *lastEvaluatedKey();
	virtual ~ResultSet();
	long ptrs;
};
}
#endif /* SRC_RESULTSET_H_ */
