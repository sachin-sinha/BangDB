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

	void add(ResultSet *rs, bool byval = false);
	void append(ResultSet *rs, bool appendAtFront = false);
	void intersect(ResultSet *rs, bool byval = false);
	void addDoc(ResultSet *rs, char *orderBy=NULL);
	void appendDoc(ResultSet *rs, char *orderBy = NULL);
	void intersectDoc(ResultSet *rs, char *orderBy = NULL);
	void sortDoc(char *byField = NULL);
	void sortDocPK(short bysort_id);

	virtual ~ResultSet();
	long ptrs;
};
}
#endif /* SRC_RESULTSET_H_ */
