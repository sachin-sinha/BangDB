
#include "BangDBDatabase.h"
using namespace BangDB_Client;

int main(int argc, char *argv[])
{

	printf("running sample test...\n");
	BangDBEnv *env;
	BangDBDatabase *db;
	BangDBTable *tbl1, *tbl2;

	DBParam dpm;
	dpm.setTransactionType(DB_TRANSACTION_NONE);
	env = new BangDBEnv(&dpm);
	db = new BangDBDatabase("mydb", env, &dpm);

	TableEnv tenv;
	tenv.setTableType(NORMAL_TABLE);
	tenv.setKeySize(12);
	if((tbl1 = db->getTable((char*)"mykvtable", &tenv, OPENCREATE)) == NULL)
	{
		printf("BangDBTable kv NULL error, quitting");
		exit(-1);
	}

	tenv.reset();
	tenv.setTableType(WIDE_TABLE);
	tenv.setKeySize(12);
	if((tbl2 = db->getTable((char*)"mydoctable", &tenv, OPENCREATE)) == NULL)
	{
		printf("BangDBTable doc NULL error, quitting");
		exit(-1);
	}

	tbl1->closeTable();	
	delete tbl1;
	tbl2->closeTable();	
	delete tbl2;
	env->closeDatabase(db);
	delete db;
	delete env;

	printf("sample test was successful\n");

	return 0;
}
