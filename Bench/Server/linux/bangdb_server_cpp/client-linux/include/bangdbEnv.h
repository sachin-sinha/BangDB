/*
 * bangdbEnv.h
 *
 *  Created on: 11-Jan-2014
 *      Author: sachin
 */

#ifndef BANGDBENV_H_
#define BANGDBENV_H_

#include "database.h"
namespace bangdb_client
{
class database;
struct client_context;

class bangdbEnv {
public:
	//all params can be read from the config file (except userid and passwork which should be left to NULL)
	bangdbEnv(const char *host = NULL, const char *port = NULL, const char * configPath = NULL, db_transaction_type db_tran_type = DB_TRANSACTION_NONE, const char *userid = NULL, const char *password = NULL, bool read_config = true);
	database *openDatabase(const char *dbname);
	database *get_db_handle();
	bool isAdmin();
	char *get_host();
	char *get_port();
	bangdbEnv *clone();
	virtual ~bangdbEnv();
private:
	char *hostname;
	char *portnum;
	char *configpath;
	char *user;
	char *pwd;
	database *db;
	db_transaction_type tran_type;
	friend struct client_context;
};

struct client_context
{
	bangdbEnv *_dbEnv;
	char *recvbuf;
	void *h;
	client_context(bangdbEnv *dbEnv);
	void init();
	bool isValid();
	bool isAdmin();
	void close();
	~client_context();
};
}
#endif /* BANGDBENV_H_ */
