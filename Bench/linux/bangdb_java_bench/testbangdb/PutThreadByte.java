package testbangdb;

import bangdb.Connection;
import bangdb.InsertOptions;

public class PutThreadByte extends Thread{
	private Connection conn = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = "my key";
    	String k, v;
    	String val = "This to test bangdb in java and see how we fare against the bangdb in c++, hope we get good result";
    	boolean success = true;
	public PutThreadByte(Connection _conn, int startid, int _num)
	{
		conn = _conn;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
		byte[] bval = null;
		byte[] bkey = null;
        for(int i = start_id; i<num_times+start_id; i++)
        {
	       	 k = key + i; 
	       	 v = val + i;
	       	 bkey = k.getBytes();
	       	 bval = v.getBytes();
	       	 if(conn.put(bkey, bval, InsertOptions.INSERT_UNIQUE) < 0)
	       		System.out.println("Put Failed.");
        }
	}
}
