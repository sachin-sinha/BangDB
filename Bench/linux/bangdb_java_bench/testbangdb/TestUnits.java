package testbangdb;

import bangdb.Connection;
import bangdb.InsertOptions;
import bangdb.ResultSet;
import bangdb.ScanFilter;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;


public class TestUnits {
    
    public static int Put(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
 	       	 if(conn.put(k, v, InsertOptions.INSERT_UNIQUE) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("Put Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    public static int Update(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val2 + i;
 	       	 if(conn.put(k, v, InsertOptions.UPDATE_EXISTING) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("Update Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    
    public static int Get(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0, mismatch = 0;
    	 String k, v, out = null;
    	
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
 	       	 
 	       	 if((out = conn.get(k)) == null)
 	       		 retval++;
 	       	 else if(out.compareTo(v) != 0)
 	       		 mismatch++;
         }
    	 if(retval != 0 || mismatch != 0)
    	 {
    		 System.out.print("Get Failed = ");
        	 System.out.println(retval);
        	 System.out.print("Get mismatch = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    public static int Del(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0, mismatch = 0;
    	 String k;
    	
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	
 	       	 if(conn.del(k) < 0)
 	       		 retval++;
 	       	 else if(conn.get(k) != null)
 	       		 mismatch++;
         }
    	 if(retval != 0 || mismatch != 0)
    	 {
    		 System.out.print("Del Failed = ");
        	 System.out.println(retval);
        	 System.out.print("Get after del not null = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    
    public static int PutByte(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
    	 byte[] bkey, bval;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
 	       	 bkey = k.getBytes();
 	       	 bval = v.getBytes();
 	       	 if(conn.put(bkey, bval, InsertOptions.INSERT_UNIQUE) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("PutByte Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    public static int UpdateByte(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
    	 byte[] bkey, bval;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val2 + i;
 	       	 bkey = k.getBytes();
 	       	 bval = v.getBytes();
 	       	 if(conn.put(bkey, bval, InsertOptions.UPDATE_EXISTING) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("Put Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    
    public static int GetByte(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0, mismatch = 0;
    	 String k, v;
    	 byte[] bkey, bval, out;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
 	       	 bkey = k.getBytes();
	       	 bval = v.getBytes();
 	       	 if((out = conn.get(bkey)) == null)
 	       		 retval++;
 	       	 else if(!Arrays.equals(out, bval))
 	       		 mismatch++;
         }
    	 if(retval != 0 || mismatch != 0)
    	 {
    		 System.out.print("Get Failed = ");
        	 System.out.println(retval);
        	 System.out.print("Get mismatch = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    public static int DelByte(Connection conn, int start_id, int num_times)
    {
    	 int retval = 0, mismatch = 0;
    	 String k;
    	 byte[] bkey;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 bkey = k.getBytes();
	       	 
 	       	 if(conn.del(bkey) < 0)
 	       		 retval++;
 	       	 else if(conn.get(bkey) != null)
 	       		 mismatch++;
         }
    	 if(retval != 0 || mismatch != 0)
    	 {
    		 System.out.print("DelByte Failed = ");
        	 System.out.println(retval);
        	 System.out.print("Get not null after del = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    
    /*
     * Assumes that the values are there in the database
     */
    public static int Scan(Connection conn, int start_id, int end_id)
    {
    	int kretval = 0, vretval = 0, count = 0;
    	String k1 = Common.key + start_id;
    	String k2 = Common.key + end_id;
    	String v1 = Common.val + start_id;
    	String v2 = Common.val + end_id;
    	String k, v, kout, vout;
    	ScanFilter sf = new ScanFilter();

    	ResultSet rs = conn.scan(k1, k2, sf);
    	if(rs == null)
    	{
    		System.out.println("Scan failed, resultset is null");
    		return -1;
    	}
    	while(rs.hasNext())
    	{
    		k = Common.key + (start_id + count);
    		v = Common.val + (start_id + count);
		kout = null; vout = null;
		byte[] bk = rs.getNextKey();
		if(bk != null)
	    		kout = new String(bk);
		byte[] bv = rs.getNextVal();
		if(bv != null)
	    		vout = new String(bv);
    		
    		if(kout == null || kout.compareTo(k) != 0)
    			kretval++;
    		if(vout == null || vout.compareTo(v) != 0)
    			vretval++;
    		
    		rs.moveNext();
    		count++;
    	}
    	if(kretval != 0 || vretval != 0)
   	 	{
	   		 System.out.print("Scan Failed for key = ");
	       	 	System.out.println(kretval);
	       	 	System.out.print("Scan Failed for val = ");
	       	 	System.out.println(vretval);
	       	 	rs.clear();
	       	 	return -1;
   	 	}
    	rs.clear();
    	return 0;
    }
    
    public static int ScanByte(Connection conn, int start_id, int end_id)
    {
    	int kretval = 0, vretval = 0, count = 0;
    	String k1 = Common.key + start_id;
    	String k2 = Common.key + end_id;
    	String v1 = Common.val + start_id;
    	String v2 = Common.val + end_id;
    	String k, v;
    	byte[] kout, vout;
    	
    	byte[] bk, bv;
    	bk = k1.getBytes();
    	bv = k2.getBytes();

	ScanFilter sf = new ScanFilter();
    	
    	ResultSet rs = conn.scan(bk, bv, sf);
    	if(rs == null)
    	{
    		System.out.println("Scan failed, resultset is null");
    		return -1;
    	}
    	while(rs.hasNext())
    	{
    		k = Common.key + (start_id + count);
    		v = Common.val + (start_id + count);
    		bk = k.getBytes();
        	bv = v.getBytes();
        	
    		kout = rs.getNextKey();
    		vout = rs.getNextVal();
    		
    		if(kout == null || !Arrays.equals(kout, bk))
    			kretval++;
    		if(vout == null || !Arrays.equals(vout, bv))
    			vretval++;
    		
    		rs.moveNext();
    		count++;
    	}
    	if(kretval != 0 || vretval != 0)
   	 	{
	   		System.out.print("Scan Failed for key = ");
	       	 	System.out.println(kretval);
	       	 	System.out.print("Scan Failed for val = ");
	       	 	System.out.println(vretval);
	       		rs.clear();
	       	 	return -1;
   	 	}
    	rs.clear();
    	return 0;
    }
    
    public static int SimpleRun(Connection conn)
	{
		Boolean success = true;
		String k = "my key\0sjsj";
		String v = "The test value";
		byte[] key = k.getBytes();
		byte[] val = v.getBytes();
		
		if(conn.put(key, val, InsertOptions.INSERT_UNIQUE) < 0)
		{
       		success = false;
       		System.out.println("Put failed");
       	}
		
		byte[] retval = conn.get(key);
		if(retval != null)
		{
			String rv = null;
			try {
				rv = new String(retval, "UTF-8");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(rv.compareTo(v) != 0)
			{
				success = false;
				System.out.println("Get failed");
			}
		}
		
		//update 
		v = "This is updated value";
		val = v.getBytes();
		
		if(conn.put(key, val, InsertOptions.UPDATE_EXISTING) < 0)
		{
       		success = false;
       		System.out.println("Update failed");
       	}
		
		retval = conn.get(key);
		if(retval != null)
		{
			String rv = null;
			try {
				rv = new String(retval, "UTF-8");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if(rv.compareTo(v) != 0)
			{
				success = false;
				System.out.println("Get failed");
			}
		}
		
		//delete
		if(conn.del(key) < 0)
		{
			success = false;
       		System.out.println("delete failed");
		}
		
		if(conn.get(key) != null)
		{
			success = false;
       		System.out.println("got deleted value, failed");
		}
		
		//for string
		k = "str key_1";
		v = "This is value 1 for key 1";
		
		if(conn.put(k, v, InsertOptions.INSERT_UPDATE) < 0)
		{
			success = false;
       		System.out.println("str put, failed");
		}
		
		String outval;
		if((outval = conn.get(k)) == null)
		{
			success = false;
       		System.out.println("str get, failed");
		}
		else
		{
			if(outval.compareTo(v) != 0)
			{
				success = false;
	       		System.out.println("str mismatch get, failed");
			}
		}
		
		v = "Let's do the right thing, even if it discomforts all of us";
		if(conn.put(k, v, InsertOptions.INSERT_UPDATE) < 0)
		{
			success = false;
       		System.out.println("str update, failed");
		}
		
		if((outval = conn.get(k)) == null)
		{
			success = false;
       		System.out.println("str get, failed");
		}
		else
		{
			if(outval.compareTo(v) != 0)
			{
				success = false;
	       		System.out.println("str mismatch get, failed");
			}
		}
		
		if(conn.del(k) < 0)
		{
			success = false;
       		System.out.println("str delete, failed");
		}
		if(conn.get(k) != null)
		{
			success = false;
       		System.out.println("delete str received even after delete, failed");
		}
		return success?0:-1;
	}
}
