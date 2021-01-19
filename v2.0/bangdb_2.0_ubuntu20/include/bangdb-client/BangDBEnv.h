/*
 * BangDBEnv.h
 *
 *  Created on: 27-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBENV_H_
#define SRC_BANGDBENV_H_

#include "DBParam.h"

namespace BangDB_Client
{
class BangDBDatabase;
class BangDBEnv
{
public:
	BangDBEnv(DBParam *dbp);

	DBParam *verifyDatabase(const char *dbname);

	char *getHost();

	char *getPort();

	//switch_option = 0, make it master, 1 make it slave, 2 just follow what stated
	//int getServerType(const char *host = NULL, const char *port = NULL);

	//int setServerMaster(const char *host = NULL, const char *port = NULL);

	//int setServerSlave(const char *host, const char *port, const char *master_ip, const char *master_port);

	void closeDatabase(BangDBDatabase *bdb, CloseType dbclose = DEFAULT_AT_CLIENT);

	virtual ~BangDBEnv();

	long ptenv;
};

}
#endif /* SRC_BANGDBENV_H_ */
