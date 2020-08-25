/*
 * BangDBTransaction.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_TRANSACTION_H_
#define SRC_TRANSACTION_H_

#include "BangDBCommon.h"

namespace BangDB_Client
{
class Transaction {
public:
	Transaction();
	bool isActive();
	virtual ~Transaction();
	long pttxn;
};
}
#endif /* SRC_TRANSACTION_H_ */
