package test;
import com.bangdb.TransactionType;
import com.bangdb.DBParam;
import com.bangdb.OpenType;
import com.bangdb.TableEnv;
import com.bangdb.TableType;
import com.bangdb.BangDBDatabase;
import com.bangdb.BangDBTable;
import com.bangdb.CloseType;

public class Sample {

	public static void testsanity()
	{
		int error = 0;
		boolean flag = true;
		System.loadLibrary("bangdb-embd-java");
		DBParam dbp = new DBParam();
		dbp.setTransactionType(TransactionType.DB_MULTIOPS_TRANSACTION_NONE);
		
		BangDBDatabase bdb = new BangDBDatabase("mydb", dbp);
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
		

		tbl.closeTable(CloseType.DEFAULT, false);
		bdb.closeDatabase(CloseType.DEFAULT);
		
		if(error < 0)
			System.out.println("testsanity failed!");
		else
			System.out.println("testsanity passed!");
	}
}
