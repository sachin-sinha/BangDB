package testbangdb;
import bangdb.Connection;
import bangdb.DBAccess;
import bangdb.DBClose;
import bangdb.Database;
import bangdb.DatabaseImpl;
import bangdb.Table;
import bangdb.TransactionType;


public class TestCases {

	public static void testsanity()
	{
		int error = 0;
		System.loadLibrary("bangdbjava");
		String dbPath = null;	//override the dbpath defined in bangdb.config by providing new path here
		String dbLogPath = null;	//override the dbLogpath defined in bangdb.config by providing new path here
		Database db = new DatabaseImpl("mydb", null, TransactionType.DB_MULTIOPS_TRANSACTION_NONE, dbPath, dbLogPath);
		Table tbl = db.getTable("mytbl", DBAccess.OPENCREATE, null);
		Connection conn = tbl.getConnection();
		
		error = TestUnits.SimpleRun(conn);
		db.closeDatabase(DBClose.DEFAULT);
		
		if(error < 0)
			System.out.println("testsanity failed!");
		else
			System.out.println("testsanity passed!");
	}
	
	public static void testputget(int N, int nT)
	{
		int start_id;;
		System.loadLibrary("bangdbjava");
		String dbPath = null;	//overriding the dbpath defined in bangdb.config by providing new path here
		String dbLogPath = null;	//override the dbLogpath defined in bangdb.config by providing new path here
		Database db = new DatabaseImpl("mydb", null, TransactionType.DB_MULTIOPS_TRANSACTION_NONE, dbPath, dbLogPath);
		Table tbl = db.getTable("mytbl", DBAccess.OPENCREATE, null);
		Connection conn = tbl.getConnection();
		
		StopWatch sw = new StopWatch();
		Thread[] threads = new Thread[nT];
		
		sw.Start();
		for(int i = 0; i<nT; i++)
	    {
			 start_id = (N/nT)*i;
			 threads[i] = new PutThreadByte(conn, start_id, N/nT);
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
	    System.out.print("Total time for Put is = ");
	    sw.Print();
	    
	    sw.Start();
		for(int i = 0; i<nT; i++)
	    {
			 start_id = (N/nT)*i;
			 threads[i] = new GetThreadByte(conn, start_id, N/nT);
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
	    System.out.print("Total time for Get is = ");
	    sw.Print();
	    
	    db.closeDatabase(DBClose.DEFAULT);
		
		System.out.println("testputget passed!");
	}
}
