
package testbangdb;
import java.util.Arrays;

import com.bangdb.BangDBTable;

public class GetThread extends Thread{
	private BangDBTable tbl = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = "my key";
    	String k, v;
   	String val = "This to test bangdb in java and see how we fare against the bangdb in c++, hope we get good result";
    
	public GetThread(BangDBTable _tbl, int startid, int _num)
	{
		tbl = _tbl;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
		byte[] bval = null;
		byte[] out = null;
		for(int i = start_id; i<num_times+start_id; i++)
	    	{
	      		k = key + i; 
	      	 	v = val + i;
	      	 	bval = v.getBytes();
	       	 	if((out = tbl.get(k, null)) == null)
	       			System.out.println("get Failed.");
	       	 	else
	       	 	{
	       		 	if(!Arrays.equals(out, bval))
	       				System.out.println("get Mismatch.");
	       	 	}
	    	}
	}
}
