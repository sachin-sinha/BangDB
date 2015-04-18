/*
 * swTable.h
 *
 *  Created on: 12-Oct-2014
 *      Author: sachin
 */

#ifndef SWTABLE_H_
#define SWTABLE_H_

#include "bangdbEnv.h"
namespace bangdb_client
{
class bangdbEnv;
struct client_context;

class swTable {
public:
	swTable(bangdbEnv *dbEnv, char *tableName, table_env *tenv, int ttlsec, bool archive = false);
	void addIndex(client_context *c, char *idxName, table_env *tenv);
	int initialize();
	//wideConnection *getConnection();
	//wideConnection *getActiveConnection();
	//wideConnection *getPassiveConnection();
	int put(client_context *c, char *str, int len, insert_options iop);
	int put(client_context *c, char *str, int len, char *idx, char *idxkey);
	int put(client_context *c, char *str, int len, char *idx, char *idxkey, int idxkeylen);
	/*
	 * scan for period sec means from cur - period upto current
	 */
	resultset *scan(client_context *c, int period);
	/*
	 * scan for period sec with lag means from (cur - lag - period) upto current - lag
	 */
	resultset *scan(client_context *c, int period, int lag);
	/*
	 * scan for whole ttlsec
	 */
	resultset *scan_full(client_context *c);
	resultset *scan_remaining(client_context *c, ULONG_T from_time, int lag);
	int getTTLSec(client_context *c);
	bool needPassive(client_context *c, int windowsec);
	FILEOFF_T getnextlsn(client_context *c);
	void close(bangdb_close_type swclose = DEFAULT_AT_CLIENT);
	virtual ~swTable();
private:

	char *_tableName;
	table_env *_tenv;
	ULONG_T tid;
	bangdbEnv *_dbEnv;
	int _ttlsec;
	bool _archive;
};
}
#endif /* SWTABLE_H_ */
