package testbangdb;
import bangdb.*;
public class GetThread extends Thread {
	private Connection conn = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = Common.key;
    	String k, v;
    	String val = Common.val;
    
	public GetThread(Connection _conn, int startid, int _num)
	{
		conn = _conn;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
		String out = null;
		for(int i = start_id; i<num_times+start_id; i++)
	    {
	      	 k = key + i; 
	      	 v = val + i;
	       	 if((out = conn.get(k)) == null)
	       		System.out.println("Get Failed.");
	       	 else
	       	 {
	       		 if(out.compareTo(v) != 0)
	       			System.out.println("Get Mismatch.");
	       	 }
	    }
	}
}
