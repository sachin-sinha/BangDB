/*
 * DataQuery.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef DATAQUERY_H_
#define DATAQUERY_H_

#include "BangDBCommon.h"

namespace BangDB_Client
{
class DataQuery {
public:
	DataQuery();

	//DataQuery(const char *query);

	//void init(const char *query);

	void addQuery(const char *filterKey, ScanOperator comp_op, const char *filterVal, JoinOperator jOp = JO_AND);

	void addQuery(const char *filterKey, ScanOperator comp_op, long filterVal, JoinOperator jOp = JO_AND);

	void addQuery(const char *filterKey, ScanOperator comp_op, double filterVal, JoinOperator jOp = JO_AND);

	// matchWordList = "apple, phone, music" - comma separated list
	void addQuery(const char *matchWordList, JoinOperator wordJoin, JoinOperator queryJoin, const char *field);

	void setQueryType(int type);

	const char *getQuery();

	void printQuery();

	void reset();

	void clean();

	virtual ~DataQuery();
private:
	long ptdq;
};
}

#endif /* DATAQUERY_H_ */
