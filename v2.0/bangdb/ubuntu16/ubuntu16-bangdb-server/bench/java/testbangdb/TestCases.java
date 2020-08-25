package testbangdb;
import com.bangdb.TransactionType;
import com.bangdb.DBParam;
import com.bangdb.InsertOptions;
import com.bangdb.KeyType;
import com.bangdb.OpenType;
import com.bangdb.ScanFilter;
import com.bangdb.ScanOperator;
import com.bangdb.TableEnv;
import com.bangdb.TableType;
import com.bangdb.ResultSet;
import com.bangdb.BangDBEnv;
import com.bangdb.BangDBDatabase;
import com.bangdb.BangDBTable;
import com.bangdb.CloseType;
import com.bangdb.DataQuery;
import com.bangdb.JoinType;


public class TestCases {

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
		
		error = TestUnits.SimpleRun(tbl);

		tbl.closeTable(CloseType.DEFAULT_AT_SERVER, false);
		dbenv.closeDatabase(CloseType.CLEANCLOSE_AT_SERVER);
		dbenv.close();
		
		if(error < 0)
			System.out.println("testsanity failed!");
		else
			System.out.println("testsanity passed!");
	}
	
	public static void testputget(int N, int nT)
	{
		int start_id;;
		System.loadLibrary("bangdb-client-java");
		boolean flag = true;
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
		
		StopWatch sw = new StopWatch();
		Thread[] threads = new Thread[nT];
		
		sw.Start();
		for(int i = 0; i<nT; i++)
	    	{
			 start_id = (N/nT)*i;
			 threads[i] = new PutThread(tbl, start_id, N/nT);
			 threads[i].start();
	    	}
	        //join
	        for(int i = 0; i<nT; i++)
	        {
			try {
				threads[i].join();
			 } catch (InterruptedException ignore) {}
	        }
	    	sw.Stop();
	    	System.out.print("Total time for put for [ "+ N +" ] items using [ "+ nT + " ] threads = ");
	    	sw.Print(N);
	    
	    	sw.Start();
		for(int i = 0; i<nT; i++)
	    	{
			 start_id = (N/nT)*i;
			 threads[i] = new GetThread(tbl, start_id, N/nT);
			 threads[i].start();
	    	}
	    	//join
	    	for(int i = 0; i<nT; i++)
	    	{
	        	try {
	        		threads[i].join();
	        	 } catch (InterruptedException ignore) {}
	    	}
	    	sw.Stop();
	    	System.out.print("Total time for get for [ "+ N +" ] items using [ "+ nT + " ] threads = ");
	    	sw.Print(N);
	    
	    	dbenv.closeDatabase(CloseType.CLEANCLOSE_AT_SERVER);
		dbenv.close();
		
		System.out.println("testputget passed!");
	}
}
