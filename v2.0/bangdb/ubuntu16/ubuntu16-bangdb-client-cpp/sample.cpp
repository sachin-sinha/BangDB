
#include "BangDBDatabase.h"
#include "DataQuery.h"
using namespace BangDB_Client;

int test_sample()
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
		return -1;
	}

	tenv.reset();
	tenv.setTableType(WIDE_TABLE);
	tenv.setKeySize(12);
	if((tbl2 = db->getTable((char*)"mydoctable", &tenv, OPENCREATE)) == NULL)
	{
		printf("BangDBTable doc NULL error, quitting");
		return -1;
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

int test_manual_sample()
{
	// first get the db environment
	DBParam dpm;
	dpm.setTransactionType(DB_TRANSACTION_NONE);   // is transaction is not needed
	BangDBEnv *env = new BangDBEnv(&dpm);
	if(!env)
	{
		printf("failed to get db env\n");
		return -1;
	}

	//  get the db
	BangDBDatabase *bdb = new BangDBDatabase((char*)"mydb", env, &dpm);
	if(!bdb)
	{
		printf("test failed. bdb is null\n");
		return -2;
	}

	// create a normal table - normal table is simple key value table, secondary indexes are not allowed here
	TableEnv te;
	te.setTableType(NORMAL_TABLE);
	te.setKeySize(24);	// default key is string type, hence we can set the size of the key
	BangDBTable *t1 = bdb->getTable("normal_table", &te, OPENCREATE);   // Open or create
	if(!t1)
	{
		printf("normal table creating failed\n");
		return -1;
	}

	// let’s get the db description and print
	const char *db_desc = NULL;
	db_desc = bdb->getStats(true);
	if(!db_desc)
	{
		printf("getStats for db failed\n");
		return -1;
	}
	else
	{
		printf("getStats for db returns following:\n%s\n", db_desc);
		delete[] db_desc;
	}

	// we may get the table description as well
	const char *tbl_desc = t1->getStats(true);
	if(!tbl_desc)
	{
		printf("table desc failed\n");
		return -1;
	}
	else
	{
		printf("getStats for normal table returns following:\n%s\n", tbl_desc);
		delete[] tbl_desc;
	}

	bool flag = true;

	// let’s put some key and value
	FDT k("my_key1", 7), v("my_val1", 7);
	if(t1->put(&k, &v, INSERT_UNIQUE) < 0)
	{
		printf("put in the normal table failed\n");
		flag = false;
	}

	FDT *ov = NULL;
	if(t1->get(&k, &ov) < 0)
	{
		printf("get in the normal table failed\n");
		flag = false;
	}
	else
	{
		printf("1. key = %s, val = %s\n", (char*)k.data, (char*)ov->data);
		ov->free();
	}

	// use the previous key to inter unique, it should return 1, which means key already exists
	v.data = (char*)"my_val1_update";
	v.length = 14;
	if(t1->put(&k, &v, INSERT_UNIQUE) != 1)	  // unique put should fail here as key exists
	{
		printf("update in the normal table failed as it put unique data\n");
		flag = false;
	}

	// we may call put with INSERT_UPDATE to update the existing key
	if(t1->put(&k, &v, INSERT_UPDATE) < 0)
	{
		printf("update in the normal table failed as it could not update the key\n");
		flag = false;
	}


	ov = NULL;
	if(t1->get(&k, &ov) < 0)
	{
		printf("get in the normal table failed\n");
		flag = false;
	}
	else
	{
		printf("2. key = %s, val = %s\n", (char*)k.data, (char*)ov->data);
		ov->free();
	}


	// delete the key
	if(t1->del(&k) < 0)
	{
		printf("del in normal table failed\n");
		flag = false;
	}

	// try to get the deleted key, you should get -1 else it’s error
	ov = NULL;
	if(t1->get(&k, &ov) >= 0)
	{
		printf("del error\n");
		flag = false;
	}
	if(ov)
	{
		printf("get in the normal table failed as it got the deleted key\n");
		flag = false;
	}

	// scan the table
	ResultSet *rs = NULL;
	ScanFilter sf;
	int nc = 0;
	// since there could be large amount of data and hence we may need to
	// scan multiple times in order to get the data
	// therefore we need to call scan recursively
	// BangDB simplifies this completely and allows user to call like following;
	// Note; you may add other args as well as needed
	printf("Scanning for table t1\n");
	while(true)
	{
		rs = t1->scan(rs, NULL, NULL, &sf);
		if(!rs)
			break;
		nc += rs->count();
		while(rs->hasNext())
		{
			// as we know this table has key and val both string hence can call these to get them
			printf("key = %s, val = %s\n", rs->getNextKeyStr(), rs->getNextValStr());
			rs->moveNext();
		}
	}
	printf("num of scanned items for table t1 = %d\n", nc);

	// create a normal table with long as key
	te.reset();
	te.setTableType(NORMAL_TABLE);
	te.setKeyType(NORMAL_KEY_LONG);    // key is long now, not string, hence key_size is not needed
	BangDBTable *t2 = bdb->getTable("normal_table_long", &te, OPENCREATE);
	if(!t2)
	{
		printf("normal table creating failed\n");
		return -1;
	}

	// put key val
	long lv = 1;
	FDT k2(lv, 8), v2("my_val_long1", 12);
	if(t2->put(&k2, &v2, INSERT_UNIQUE) < 0)
	{
		printf("put in the normal table failed\n");
		flag = false;
	}

	// get the val for the given key
	ov = NULL;
	if(t2->get(&k2, &ov) < 0)
	{
		printf("get in the normal table failed\n");
		flag = false;
	}
	else
	{
		printf("3. key = %ld, val = %s\n", (long)k2.data, (char*)ov->data);
		ov->free();
	}


	// drop a table now
	// there are two ways to do this
	// 1. Call dropTable() on BangDBDatabse
	// 2. Close the table and tell server to clean close it - I.e. delete everything for the table
	// let’s drop the table using 2
	if(t1->closeTable(CLEANCLOSE_AT_SERVER) < 0)
	{
		printf("failed to drop the table t1\n");
		flag = false;
	}

	// check if it exists
	if(bdb->doesTableExist("normal_table"))
	{
		printf("table normal_table exists after dropping it\n");
		flag = false;
	}

	// let’s create wide table now, table that deals with json doc, but it can also store simple text

	te.reset();
	te.setTableType(WIDE_TABLE);
	te.setKeyType(NORMAL_KEY_LONG);    	// let’s use long key
	te.setAllowDuplicate(true);			// dupl key is allowed
	te.setVersionType(BANGDB_DATA_VERSION_VALID_INVALID);   // this will maintain versions, usually we should do this

	BangDBTable *t3 = bdb->getTable("my_wide_table1", &te, OPENCREATE);
	if(!t3)
	{
		printf("wide table could not be created\n");
		return -1;
	}

	// put few keys and vals
	FDT wk1(111, 8), wk2(222, 8), wk3(333, 8);
	FDT wv1("wide val 1", 10), wv2("wide val 2", 10), wv3("wide val 3", 10);
	if(t3->put(&wk1, &wv1, INSERT_UNIQUE) < 0)
	{
		printf("put for widetable failed\n");
		flag = false;
	}

	if(t3->put(&wk2, &wv2, INSERT_UNIQUE) < 0)
	{
		printf("put for widetable failed\n");
		flag = false;
	}

	if(t3->put(&wk3, &wv3, INSERT_UNIQUE) < 0)
	{
		printf("put for widetable failed\n");
		flag = false;
	}

	 wv1.data = (char*)"wide_val_1_up";
	 wv1.length = 13;
	if(t3->put(&wk1, &wv1, INSERT_UNIQUE) < 0)
	{
		printf("put for widetable failed\n");
		flag = false;
	}

	FDT *wov = NULL;
	if(t3->get(&wk1, &wov) < 0)
	{
		printf("get failed for wide table\n");
		flag = false;
	}
	else
	{
		printf("4. key = %d, val = %s\n", 111, (char*)wov->data);
		wov->free();
		delete wov;
	}

	// scan for some key range - this will recursively scan until all keys and values are scanned
	rs = NULL;
	sf.reset();
	nc = 0;
	printf("Scanning for table t3\n");
	while(true)
	{
		rs = t3->scan(rs, &wk1, &wk3, &sf);
		if(!rs)
			break;
		nc += rs->count();
		while(rs->hasNext())
		{
			printf("key = %ld, val = %s\n", rs->getNextKeyLong(), rs->getNextValStr());
			rs->moveNext();
		}
	}
	printf("num of scanned items for table t3 = %d\n", nc);

	// may count number of keys as well, with or without range
	printf("total num of elements in t3 = %ld\n", t3->count());
	printf("num of elements between wk2 and wk3 in t3 = %ld\n", t3->count(&wk2, &wk3));

	// try now json doc - usually we should only put docs or non-docs, mixing may not be very logical
	// hence let’s create new wide table

	te.reset();
	te.setAllowDuplicate(true);
	te.reset();
	te.setTableType(WIDE_TABLE);
	te.setKeyType(NORMAL_KEY_LONG);
	te.setAllowDuplicate(true);
	te.setVersionType(BANGDB_DATA_VERSION_VALID_INVALID);

	BangDBTable *t4 = bdb->getTable("my_wide_table2", &te, OPENCREATE);
	if(!t4)
	{
		printf("wide table t4 could not be created\n");
		return -1;
	}

	// add few indexes as well
	// this one creates an index on string type field where max size is 16 bytes
	if(t4->addIndex_str("org", 16, true) < 0)
	{
		printf("error in adding index org\n");
		flag = false;
	}

	// this one creates an index on string type field where max size is 24 bytes
	// note, it’s a nested index
	if(t4->addIndex_str("family.favsport", 24, true) < 0)
	{
		printf("error in adding index family.favsport\n");
		flag = false;
	}


	const char *doc1 = "{\"name\":\"sachin sinha\", \"org\":\"iqlect\", \"likes\":[\"music\", \"sports\", \"movies\"], \"family\":{\"wife\":\"vijeta\", \"father\":\"k m n sinha\",\"favsport\":\"cricket\"}}";

	const char *doc2 = "{\"name\":\"mukesh prasad singh\", \"org\":\"zopsmart\", \"likes\":[\"tech\", \"sports\", \"movies\"], \"family\":{\"wife\":\"julie\", \"father\":\"p prasad\",\"favsport\":\"football\"}}";

	const char *doc3 = "{\"name\":\"aman thakur\", \"org\":\"google\", \"likes\":[\"investment\", \"ping pong\", \"movies\"], \"family\":{\"wife\":\"koyal\", \"father\":\"h thakur\",\"favsport\":\"cricket\"}}";

	const char *doc4 = "{\"name\":\"arjun\", \"org\":\"nps\", \"likes\":[\"music\", \"video games\", \"movies\"], \"family\":{\"father\":\"Sachin Sinha\", \"mother\":\"vijeta\",\"favsport\":\"cricket\"}}";

	if(t4->putDoc(doc1) < 0)         // note we are not supplying any key, in this case db will pick timestamp (in microsec) as the key
	{
		printf("put failed for doc1\n");
		flag = false;
	}

	if(t4->putDoc(doc2) < 0)
	{
		printf("put failed for doc2\n");
		flag = false;
	}

	if(t4->putDoc(doc3) < 0)
	{
		printf("put failed for doc3\n");
		flag = false;
	}

	if(t4->putDoc(doc4) < 0)
	{
		printf("put failed for doc4\n");
		flag = false;
	}


	// let’s define some query for which we wish to scan the data
	DataQuery dq;
	const char *idx_query;
	dq.addQuery("org", EQ, "iqlect", JO_INVALID);   // select all where org = Iqlect
	idx_query = dq.getQuery();
	rs = NULL; // must set it to null
	sf.reset();
	nc = 0;
	printf("Scan query : select * from t4 where org = iqlect\n");
	while(true)
	{
		if((rs = t4->scanDoc(rs, NULL, NULL, idx_query, &sf)) == NULL)	// note scanDoc() here and not scan()
			break;
		nc += rs->count();
		while(rs->hasNext())
		{
			printf("key = %ld, val = %s\n", rs->getNextKeyLong(), rs->getNextValStr());
			rs->moveNext();
		}
	}
	printf("num of scanned items for table t4 (select * from t4 where org = iqlect) = %d\n", nc);

	// now select all where family favs ports = cricket.
	dq.reset();
	dq.addQuery("family.favsport",  EQ, "cricket", JO_INVALID);
	idx_query = dq.getQuery();
	rs = NULL; // must set it to null
	sf.reset();
	nc = 0;
	printf("Scanning query : select * from t4 where family.favsport = cricket\n");
	while(true)
	{
		if((rs = t4->scanDoc(rs, NULL, NULL, idx_query, &sf)) == NULL)
			break;
		nc += rs->count();
		while(rs->hasNext())
		{
			printf("key = %ld, val = %s\n", rs->getNextKeyLong(), rs->getNextValStr());
			rs->moveNext();
		}
	}
	printf("num of scanned items for table t4 (select * from t4 where family.favsport = cricket) = %d\n", nc);


	printf("t4 count for filter based scan = %ld with total count = %ld\n", t4->count(NULL, NULL, idx_query, &sf), t4->count());

	// number of tables in the db
	printf("num of tables in the db = %ld\n", bdb->getNumTables());

	printf("does table t3 exist? ans = %s\n", bdb->doesTableExist("my_wide_table1") ? "yes" : "no");

	printf("does table t1 exist? ans = %s\n", bdb->doesTableExist("normal_table") ? "yes" : "no");


	// get all table list and print - note you will get these tables in describe database or describe table api calls as well
	const char *tbl_list = bdb->getTableList();

	if(!tbl_list)
	{
		printf("tbl list is NULL\n");
		flag = false;
	}
	else
	{
		printf("table list = \n%s\n", tbl_list);
		delete[] tbl_list;
	}

	// drop the "org" index and put some value and then scan using index
	if(t4->dropIndex("org") < 0)
	{
		printf("drop index failed for index org\n");
		flag = false;
	}

	const char *doc5 = "{\"name\":\"raj\", \"org\":\"iqlect\", \"likes\":[\"music\", \"sprots\", \"movies\"], \"family\":{\"wife\":\"richa pandey\", \"father\":\"kevin\", \"mother\":\"latika\"}}";
	if(t4->putDoc(doc5) < 0)
	{
		printf("put failed for doc5\n");
		flag = false;
	}

	printf("........ scan again for org index = iqlect .......\n");

	dq.reset();
	dq.addQuery("org", EQ, "iqlect", JO_INVALID);
	idx_query = dq.getQuery();
	rs = NULL; // must set it to null
	sf.reset();
	nc = 0;
	printf("Scan query - select * from t4 where org = iqlect\n");
	while(true)
	{
		if((rs = t4->scanDoc(rs, NULL, NULL, idx_query, &sf)) == NULL)
			break;
		nc += rs->count();
		while(rs->hasNext())
		{
			printf("key = %ld, val = %s\n", rs->getNextKeyLong(), rs->getNextValStr());
			rs->moveNext();
		}
	}
	printf("num of scanned items for table t4 (select * from t4 where org = iqlect) = %d\n", nc);


	// you may close the table when done or in the end when you close database, all tables get closed as well
	if(t2->closeTable() < 0)
	{
		printf("normal closeTable failed\n");
		flag = false;
	}
	delete t2;    // even if you don’t close the table, it’s a good practice to delete the table object, db won’t clean this object, will just close the table

	env->closeDatabase(bdb, CLEANCLOSE_AT_SERVER);
	delete bdb;
	printf("test %s\n", flag ? "passed" : "failed");
	return flag ? 0 : -1;
}

int main(int argc, char *argv[])
{
	int rv = 0;	
	if(test_sample() < 0)
	{
		rv = -1;
		printf("test_sample failed!\n");
	}

	if(test_manual_sample() < 0)
	{
		rv = -1;
		printf("test_manual_sample failed!\n");
	}

	printf("Sample test execution was %s\n", rv == 0 ? "successful!" : "failure.");

	return 0;
}
