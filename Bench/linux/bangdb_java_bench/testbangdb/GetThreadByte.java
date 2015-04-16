
package testbangdb;
import java.util.Arrays;

import bangdb.Connection;

public class GetThreadByte extends Thread{
	private Connection conn = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = "my key";
    	String k, v;
   	String val = "This to test bangdb in java and see how we fare against the bangdb in c++, hope we get good result";
    
	public GetThreadByte(Connection _conn, int startid, int _num)
	{
		conn = _conn;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
		byte[] bval = null;
		byte[] bkey = null;
		byte[] out = null;
		for(int i = start_id; i<num_times+start_id; i++)
	    {
	      	 k = key + i; 
	      	 v = val + i;
	      	 bkey = k.getBytes();
	      	 bval = v.getBytes();
	       	 if((out = conn.get(bkey)) == null)
	       		System.out.println("Get Failed.");
	       	 else
	       	 {
	       		 if(!Arrays.equals(out, bval))
	       			System.out.println("Get Mismatch.");
	       	 }
	    }
	}
}
