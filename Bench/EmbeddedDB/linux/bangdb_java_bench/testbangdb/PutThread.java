package testbangdb;
import bangdb.*;
public class PutThread extends Thread {

	private Connection conn = null;
	private int start_id = 0;
	private int num_times = 0;
    	String key = Common.key;
    	String k, v;
    	String val = Common.val;
    
	public PutThread(Connection _conn, int startid, int _num)
	{
		conn = _conn;
		start_id = startid;
		num_times = _num;
	}
	public void run()
	{
        for(int i = start_id; i<num_times+start_id; i++)
        {
	       	 k = key + i; 
	       	 v = val + i;
	       	 if(conn.put(k, v, InsertOptions.INSERT_UNIQUE) < 0)
	       		 System.out.println("Put Failed.");
        }
	}
}
