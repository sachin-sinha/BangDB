package testbangdb;

import com.bangdb.BangDBTable;
import com.bangdb.InsertOptions;

public class PutThread extends Thread{
	private BangDBTable tbl = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = "my key";
    	String k, v;
    	String val = "This to test bangdb in java and see how we fare against the bangdb in c++, hope we get good result";
    	boolean success = true;
	public PutThread(BangDBTable _tbl, int startid, int _num)
	{
		tbl = _tbl;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
		byte[] bval = null;
		for(int i = start_id; i<num_times+start_id; i++)
		{
		       	 k = key + i; 
		       	 v = val + i;
		       	 bval = v.getBytes();
		       	 if(tbl.put(k, bval, InsertOptions.INSERT_UNIQUE, null) < 0)
		       		System.out.println("put Failed.");
		}
	}
}
