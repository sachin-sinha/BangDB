package test;
import com.bangdb.TransactionType;
import com.bangdb.DBParam;
import com.bangdb.OpenType;
import com.bangdb.TableEnv;
import com.bangdb.TableType;
import com.bangdb.BangDBEnv;
import com.bangdb.BangDBDatabase;
import com.bangdb.BangDBTable;
import com.bangdb.CloseType;
import com.bangdb.InsertOptions;
import com.bangdb.ResultSet;
import com.bangdb.ScanFilter;
import com.bangdb.KeyType;
import com.bangdb.VersionType;
import com.bangdb.DataQuery;
import com.bangdb.ScanOperator;
import com.bangdb.JoinType;

public class Sample {

	public static void testsanity()
	{
		int error = 0;
		boolean flag = true;
		System.loadLibrary("bangdb-client-java");
		DBParam dbp = new DBParam();
		dbp.set_host("127.0.0.1");
		dbp.set_port("10101");
		dbp.setTransactionType(TransactionType.DB_MULTIOPS_TRANSACTION_NONE);
		
		BangDBEnv dbenv = BangDBEnv.getInstance(dbp);
		BangDBDatabase bdb = dbenv.openDatabase("mydb", dbp);
		if(bdb != null)
		{
			System.out.println("java - bdb created");
		}
		else
			flag = false;
		TableEnv tenv = new TableEnv();
		BangDBTable tbl = bdb.getTable("mytbl", tenv, OpenType.OPENCREATE);
		if(tbl != null)
		{
			System.out.println("java - tbl created");
		}
		else
			flag = false;
		

		tbl.closeTable(CloseType.DEFAULT_AT_SERVER, false);
		dbenv.closeDatabase(CloseType.CLEANCLOSE_AT_SERVER);
		dbenv.close();
		
		if(error < 0)
			System.out.println("testsanity failed!");
		else
			System.out.println("testsanity passed!");
	}

	public static int test_manual_sample()
	{
		boolean flag = true;
		System.loadLibrary("bangdb-client-java");

		// first get the db environment
		DBParam dpm = new DBParam();
		dpm.set_host("127.0.0.1");
		dpm.set_port("10101");
		dpm.setTransactionType(TransactionType.DB_MULTIOPS_TRANSACTION_NONE);   // is transaction is not needed
		BangDBEnv env = BangDBEnv.getInstance(dpm);
		if(env == null)
		{
			System.out.print("failed to get db env\n");
			return -1;
		}

		//  get the db
		BangDBDatabase bdb = env.openDatabase("mydb", dpm);
		if(bdb == null)
		{
			System.out.print("test failed. bdb is null\n");
			return -1;
		}

		// create a normal table - normal table is simple key value table, secondary indexes are not allowed here
		TableEnv te = new TableEnv();
		te.setTableType(TableType.NORMAL_TABLE);
		te.setKeySize(24);	// default key is String type, hence we can set the size of the key
		BangDBTable t1 = bdb.getTable("normal_table", te, OpenType.OPENCREATE);   // Open or create
		if(t1 == null)
		{
			System.out.print("normal table creating failed\n");
			return -1;
		}

		// let’s get the db description and print
		String db_desc = null;
		db_desc = bdb.getStats(true);
		if(db_desc == null)
		{
			System.out.print("getStats for db failed\n");
			return -1;
		}
		else
		{
			System.out.print("getStats for db returns following:\n" + db_desc);
		}

		// we may get the table description as well
		String tbl_desc = t1.getStats(true);
		if(tbl_desc == null)
		{
			System.out.print("table desc failed\n");
			return -1;
		}
		else
		{
			System.out.print("getStats for normal table returns following:\n" + tbl_desc);
		}

		// let’s put some key and value
		String key = "my_key1";
		String val = "my_val1";
		if(t1.put(key, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put in the normal table failed\n");
			flag = false;
		}

		byte[] ov = null;
		if((ov = t1.get(key, null)) == null)
		{
			System.out.print("get in the normal table failed\n");
			flag = false;
		}
		else
		{
			System.out.println("1. key = " + key + " val = " + new String(ov));
		}

		// use the previous key to inter unique, it should return 1, which means key already exists
		val = "my_val1_update";
		if(t1.put(key, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) != 1)	  // unique put should fail here as key exists
		{
			System.out.print("update in the normal table failed as it put unique data\n");
			flag = false;
		}

		// we may call put with INSERT_UPDATE to update the existing key
		if(t1.put(key, val.getBytes(), InsertOptions.INSERT_UPDATE, null) < 0)
		{
			System.out.print("update in the normal table failed as it could not update the key\n");
			flag = false;
		}

		ov = null;
		if((ov = t1.get(key, null)) == null)
		{
			System.out.print("get in the normal table failed\n");
			flag = false;
		}
		else
		{
			System.out.println("1. key = " + key + " val = " + new String(ov));
		}

		// delete the key
		if(t1.del(key, null) < 0)
		{
			System.out.print("del in normal table failed\n");
			flag = false;
		}

		// try to get the deleted key, you should get -1 else it’s error
		ov = null;
		if((ov = t1.get(key, null)) != null)
		{
			System.out.print("del error\n");
			flag = false;
		}
		if(ov != null)
		{
			System.out.print("get in the normal table failed as it got the deleted key\n");
			flag = false;
		}

		// scan the table
		ResultSet rs = null;
		ScanFilter sf = new ScanFilter();
		String sk = null;
		int nc = 0;
		// since there could be large amount of data and hence we may need to
		// scan multiple times in order to get the data
		// therefore we need to call scan recursively
		// BangDB simplifies this completely and allows user to call like following;
		// Note; you may add other args as well as needed
		System.out.print("Scanning for table t1\n");
		while(true)
		{
			rs = t1.scan(rs, sk, null, sf, null);
			if(rs == null)
				break;
			nc += rs.count();
			while(rs.hasNext())
			{
				System.out.println("key = " + new String(rs.getNextKey()) + "val = " + new String(rs.getNextVal()));
				rs.moveNext();
			}
		}
		System.out.println("num of scanned items for table t1 = "+ nc);

		// create a normal table with long as key
		te.reset();
		te.setTableType(TableType.NORMAL_TABLE);
		te.setKeyType(KeyType.NORMAL_KEY_LONG);    // key is long now, not String, hence key_size is not needed
		BangDBTable t2 = bdb.getTable("normal_table_long", te, OpenType.OPENCREATE);
		if(t2 == null)
		{
			System.out.print("normal table creating failed\n");
			return -1;
		}

		// put key val
		long lk = 1;
		val = "my_val_long1";
		if(t2.put(lk, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put in the normal table failed\n");
			flag = false;
		}

		// get the val for the given key
		ov = null;
		if((ov = t2.get(lk, null)) == null)
		{
			System.out.print("get in the normal table failed\n");
			flag = false;
		}
		else
		{
			System.out.println("3. key = " + lk + " val = " + new String(ov));
		}


		// drop a table now
		// there are two ways to do this
		// 1. Call dropTable() on BangDBDatabse
		// 2. Close the table and tell server to clean close it - I.e. delete everything for the table
		// let’s drop the table using 2
		if(t1.closeTable(CloseType.CLEANCLOSE_AT_SERVER, true) < 0)
		{
			System.out.print("failed to drop the table t1\n");
			flag = false;
		}

		// check if it exists
		if(bdb.doesTableExist("normal_table", 0))
		{
			System.out.print("table normal_table exists after dropping it\n");
			flag = false;
		}

		// let’s create wide table now, table that deals with json doc, but it can also store simple text

		te.reset();
		te.setTableType(TableType.WIDE_TABLE);
		te.setKeyType(KeyType.NORMAL_KEY_LONG);    	// let’s use long key
		te.setAllowDuplicate(1);			// dupl key is allowed
		te.setVersionType(VersionType.BANGDB_DATA_VERSION_VALID);   // this will maintain versions, usually we should do this

		BangDBTable t3 = bdb.getTable("my_wide_table1", te, OpenType.OPENCREATE);
		if(t3 == null)
		{
			System.out.print("wide table could not be created\n");
			return -1;
		}

		// put few keys and vals

		lk = 111;
		val = "wide val 1";
		if(t3.put(lk, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put for widetable failed\n");
			flag = false;
		}

		lk = 222;
		val = "wide val 2";
		if(t3.put(lk, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put for widetable failed\n");
			flag = false;
		}

		lk = 333;
		val = "wide val 3";
		if(t3.put(lk, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put for widetable failed\n");
			flag = false;
		}

		lk = 111;
		val = "wide_val_1_up";
		if(t3.put(lk, val.getBytes(), InsertOptions.INSERT_UNIQUE, null) < 0)
		{
			System.out.print("put for widetable failed\n");
			flag = false;
		}

		ov = null;
		if((ov = t3.get(lk, null)) == null)
		{
			System.out.print("get failed for wide table\n");
			flag = false;
		}
		else
		{
			System.out.println("4. key = " + lk + " val = " + new String(ov));
		}

		// scan for some key range - this will recursively scan until all keys and values are scanned
		rs = null;
		sf.reset();
		nc = 0;
		long lk1 = 111, lk3 = 333;
		System.out.print("Scanning for table t3\n");
		while(true)
		{
			rs = t3.scan(rs, lk1, lk3, sf, null);
			if(rs == null)
				break;
			nc += rs.count();
			while(rs.hasNext())
			{
				System.out.println("key = " + rs.getNextKeyLong() + " val = " + new String(rs.getNextVal()));
				rs.moveNext();
			}
		}
		System.out.println("num of scanned items for table t3 = " + nc);

		// may count number of keys as well, with or without range
		System.out.println("total num of elements in t3 = " + t3.count());
		long lk2 = 222;
		sf.reset();
		System.out.println("num of elements between lk2 and lk3 in t3 = " + t3.count(lk2, lk3, null, sf));

		// try now json doc - usually we should only put docs or non-docs, mixing may not be very logical
		// hence let’s create new wide table

		te.reset();
		te.setAllowDuplicate(1);
		te.reset();
		te.setTableType(TableType.WIDE_TABLE);
		te.setKeyType(KeyType.NORMAL_KEY_LONG);
		te.setAllowDuplicate(1);
		te.setVersionType(VersionType.BANGDB_DATA_VERSION_VALID);

		BangDBTable t4 = bdb.getTable("my_wide_table2", te, OpenType.OPENCREATE);
		if(t4 == null)
		{
			System.out.print("wide table t4 could not be created\n");
			return -1;
		}

		// add few indexes as well
		// this one creates an index on String type field where max size is 16 bytes
		if(t4.addIndex_str("org", 16, true) < 0)
		{
			System.out.print("error in adding index org\n");
			flag = false;
		}

		// this one creates an index on String type field where max size is 24 bytes
		// note, it’s a nested index
		if(t4.addIndex_str("family.favsport", 24, true) < 0)
		{
			System.out.print("error in adding index family.favsport\n");
			flag = false;
		}


		String doc1 = "{\"name\":\"sachin sinha\", \"org\":\"iqlect\", \"likes\":[\"music\", \"sports\", \"movies\"], \"family\":{\"wife\":\"vijeta\", \"father\":\"k m n sinha\",\"favsport\":\"cricket\"}}";

		String doc2 = "{\"name\":\"mukesh prasad singh\", \"org\":\"zopsmart\", \"likes\":[\"tech\", \"sports\", \"movies\"], \"family\":{\"wife\":\"julie\", \"father\":\"p prasad\",\"favsport\":\"football\"}}";

		String doc3 = "{\"name\":\"aman thakur\", \"org\":\"google\", \"likes\":[\"investment\", \"ping pong\", \"movies\"], \"family\":{\"wife\":\"koyal\", \"father\":\"h thakur\",\"favsport\":\"cricket\"}}";

		String doc4 = "{\"name\":\"arjun\", \"org\":\"nps\", \"likes\":[\"music\", \"video games\", \"movies\"], \"family\":{\"father\":\"Sachin Sinha\", \"mother\":\"vijeta\",\"favsport\":\"cricket\"}}";

		if(t4.putDoc(doc1, 0, null, InsertOptions.INSERT_UNIQUE) < 0)         // note we are not supplying any key, in this case db will pick timestamp (in microsec) as the key
		{
			System.out.print("put failed for doc1\n");
			flag = false;
		}

		if(t4.putDoc(doc2, 0, null, InsertOptions.INSERT_UNIQUE) < 0)
		{
			System.out.print("put failed for doc2\n");
			flag = false;
		}

		if(t4.putDoc(doc3, 0, null, InsertOptions.INSERT_UNIQUE) < 0)
		{
			System.out.print("put failed for doc3\n");
			flag = false;
		}

		if(t4.putDoc(doc4, 0, null, InsertOptions.INSERT_UNIQUE) < 0)
		{
			System.out.print("put failed for doc4\n");
			flag = false;
		}


		// let’s define some query for which we wish to scan the data
		DataQuery dq = new DataQuery();
		String idx_query = null;
		dq.addQuery("org", ScanOperator.EQ, "iqlect", JoinType.JO_INVALID);   // select all where org = Iqlect
		idx_query = dq.getQuery();
		rs = null; // must set it to null
		sf.reset();
		nc = 0;
		System.out.print("Scan query : select * from t4 where org = iqlect\n");
		while(true)
		{
			if((rs = t4.scanDoc(rs, 0, 0, idx_query, sf)) == null)	// note scanDoc() here and not scan()
				break;
			nc += rs.count();
			while(rs.hasNext())
			{
				System.out.println("key = " + rs.getNextKeyLong() + " val = " + new String(rs.getNextVal()));
				rs.moveNext();
			}
		}
		System.out.println("num of scanned items for table t4 (select * from t4 where org = iqlect) = " + nc);

		// now select all where family favs ports = cricket.
		dq.reset();
		dq.addQuery("family.favsport",  ScanOperator.EQ, "cricket", JoinType.JO_INVALID);
		idx_query = dq.getQuery();
		rs = null; // must set it to null
		sf.reset();
		nc = 0;
		System.out.print("Scanning query : select * from t4 where family.favsport = cricket\n");
		while(true)
		{
			if((rs = t4.scanDoc(rs, 0, 0, idx_query, sf)) == null)	// note scanDoc() here and not scan()
				break;
			nc += rs.count();
			while(rs.hasNext())
			{
				System.out.println("key = " + rs.getNextKeyLong() + " val = " + new String(rs.getNextVal()));
				rs.moveNext();
			}
		}
		System.out.println("num of scanned items for table t4 (select * from t4 where family.favsport = cricket) = " + nc);


		System.out.println("t4 count for filter based scan = " + t4.count(null, null, idx_query, sf) + " with total count = " + t4.count());

		// number of tables in the db
		System.out.println("num of tables in the db = " + bdb.getNumTables(3));

		System.out.println("does table t3 exist? ans = " + bdb.doesTableExist("my_wide_table1", 0));

		System.out.println("does table t1 exist? ans = " + bdb.doesTableExist("normal_table", 0));


		// get all table list and print - note you will get these tables in describe database or describe table api calls as well
		String tbl_list = bdb.getTableList();

		if(tbl_list == null)
		{
			System.out.print("tbl list is null\n");
			flag = false;
		}
		else
		{
			System.out.println("table list = \n"+ tbl_list);
		}

		// drop the "org" index and put some value and then scan using index
		if(t4.dropIndex("org") < 0)
		{
			System.out.print("drop index failed for index org\n");
			flag = false;
		}

		String doc5 = "{\"name\":\"raj\", \"org\":\"iqlect\", \"likes\":[\"music\", \"sprots\", \"movies\"], \"family\":{\"wife\":\"richa pandey\", \"father\":\"kevin\", \"mother\":\"latika\"}}";
		if(t4.putDoc(doc5, 0, null, InsertOptions.INSERT_UNIQUE) < 0)
		{
			System.out.print("put failed for doc5\n");
			flag = false;
		}

		System.out.print("........ scan again for org index = iqlect .......\n");

		dq.reset();
		dq.addQuery("org", ScanOperator.EQ, "iqlect", JoinType.JO_INVALID);
		idx_query = dq.getQuery();
		rs = null; // must set it to null
		sf.reset();
		nc = 0;
		System.out.print("Scan query - select * from t4 where org = iqlect\n");
		while(true)
		{
			if((rs = t4.scanDoc(rs, 0, 0, idx_query, sf)) == null)	// note scanDoc() here and not scan()
				break;
			nc += rs.count();
			while(rs.hasNext())
			{
				System.out.println("key = " + rs.getNextKeyLong() + " val = " + new String(rs.getNextVal()));
				rs.moveNext();
			}
		}
		System.out.println("num of scanned items for table t4 (select * from t4 where org = iqlect) = " + nc);


		// you may close the table when done or in the end when you close database, all tables get closed as well
		if(t2.closeTable(CloseType.DEFAULT_AT_CLIENT, false) < 0)
		{
			System.out.print("normal closeTable failed\n");
			flag = false;
		}

		env.closeDatabase(CloseType.CLEANCLOSE_AT_SERVER);
		if(flag)
			System.out.println("test passed");
		else
			System.out.println("test failed");
		return flag ? 0 : -1;
	}
}
