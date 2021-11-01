/*
 * ScanFilter.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_SCANFILTER_H_
#define SRC_SCANFILTER_H_

#include "BangDBCommon.h"

namespace BangDB
{
class ScanFilter {
public:
	ScanFilter();
	void set_skey_op(ScanOperator skey_op);
	ScanOperator get_skey_op();
	void set_ekey_op(ScanOperator ekey_op);
	ScanOperator get_ekey_op();
	void set_limit_by(ScanLimitBy limitby);
	ScanLimitBy get_limit_by();
	void set_limit(int limit);
	int get_limit();
	void set_only_key(short flag);
	short get_only_key();
	void set_reserved(int reserved);
	int get_reserved();
	void reset();
	virtual ~ScanFilter();
	long ptsf;
};
}
#endif /* SRC_SCANFILTER_H_ */
