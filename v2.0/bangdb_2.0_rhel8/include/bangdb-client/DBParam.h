/*
 * DBParam.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_DBPARAM_H_
#define SRC_DBPARAM_H_

#include "BangDBCommon.h"

namespace BangDB_Client
{
class DBParam {
public:
	DBParam();
	DBParam(long _ptdbpm);

	void setHost(const char *host);
	void setPort(const char *port);
	void setDbConfigPath(const char *dbconfigPath);
	void setDbPath(const char *dbPath);
	void setLogPath(const char *logPath);
	void setArchivePath(const char *archivePath);
	void setTransactionType(TransactionType tranType);
	void setInitSockConn(bool flag);
	void setSecureConn(bool flag);

	const char *getHost();
	const char *getPort();
	const char *getDbConfigPath();
	const char *getDbPath();
	const char *getLogPath();
	const char *getArchivePath();
	TransactionType getTranType();
	bool getInitSockConn();
	bool getSecureConn();

	virtual ~DBParam();
	long ptdbpm;
};
}
#endif /* SRC_DBPARAM_H_ */
