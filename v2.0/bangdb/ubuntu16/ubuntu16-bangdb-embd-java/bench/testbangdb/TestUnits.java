package testbangdb;

import com.bangdb.BangDBTable;
import com.bangdb.InsertOptions;
import com.bangdb.ResultSet;
import com.bangdb.ScanFilter;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;


public class TestUnits {
    
    public static int Put(BangDBTable tbl, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
	 byte[] vb = null;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
		 vb = v.getBytes();
 	       	 if(tbl.put(k, vb, InsertOptions.INSERT_UNIQUE, null) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("Put Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    public static int Update(BangDBTable tbl, int start_id, int num_times)
    {
    	 int retval = 0;
    	 String k, v;
	 byte[] vb = null;
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val2 + i;
		 vb = v.getBytes();
 	       	 if(tbl.put(k, vb, InsertOptions.UPDATE_EXISTING, null) < 0)
 	       		 retval++;
         }
    	 if(retval != 0)
    	 {
	    	 System.out.print("Update Failed = ");
	    	 System.out.println(retval);
    	 }
    	return retval==0?0:-1;
    }
    
    public static int Get(BangDBTable tbl, int start_id, int num_times)
    {
    	 int mismatch = 0, retval = 0;
    	 String k, v;
	 byte[] out = null, bval;
    	
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	 v = Common.val + i;
 	       	 bval = v.getBytes();
 	       	 if((out = tbl.get(k, null)) == null)
 	       		 retval++;
 	       	 else if(!Arrays.equals(out, bval))
 	       		 mismatch++;
         }
    	 if(mismatch != 0)
    	 {
    		 System.out.print("get Failed = ");
        	 System.out.print("get mismatch = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    public static int Del(BangDBTable tbl, int start_id, int num_times)
    {
    	 int mismatch = 0, retval = 0;
    	 String k;
	 byte[] out = null;
    	
    	 for(int i = start_id; i<num_times+start_id; i++)
         {
 	       	 k = Common.key + i; 
 	       	
 	       	 if(tbl.del(k, null) < 0)
 	       		 retval++;
 	       	 else if((out = tbl.get(k, null)) != null)
 	       		 mismatch++;
         }
    	 if(mismatch != 0)
    	 {
    		 System.out.print("del Failed = ");
        	 System.out.print("get after del not null = ");
        	 System.out.println(mismatch);
        	 return -1;
    	 }
    	return 0;
    }
    
    /*
     * Assumes that the values are there in the database
     */
    public static int Scan(BangDBTable tbl, int start_id, int end_id)
    {
    	int kretval = 0, vretval = 0, count = 0;
    	String k1 = Common.key + start_id;
    	String k2 = Common.key + end_id;
    	String v1 = Common.val + start_id;
    	String v2 = Common.val + end_id;
    	String k, v, kout, vout;
    	ScanFilter sf = new ScanFilter();
	ResultSet rs = null;
	while(true)
	{
		rs = tbl.scan(rs, k1, k2, sf, null);
		if(rs == null)
			break;
	
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
	}
    	
    	return 0;
    }
    
    public static int SimpleRun(BangDBTable tbl)
    {
		Boolean success = true;
		String k = "my key\0sjsj";
		String v = "The test value";
		byte[] val = v.getBytes();
		
		if(tbl.put(k, val, InsertOptions.INSERT_UNIQUE, null) < 0)
		{
	       		success = false;
	       		System.out.println("put failed");
    		}
		
		byte[] retval = tbl.get(k, null);
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
				System.out.println("get failed");
			}
		}
		
		//update 
		v = "This is updated value";
		val = v.getBytes();
		
		if(tbl.put(k, val, InsertOptions.UPDATE_EXISTING, null) < 0)
		{
	       		success = false;
	       		System.out.println("Update failed");
       		}
		
		retval = tbl.get(k, null);
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
		if(tbl.del(k, null) < 0)
		{
			success = false;
       			System.out.println("delete failed");
		}
		
		if((val = tbl.get(k, null)) != null)
		{
			success = false;
       			System.out.println("got deleted value, failed");
		}
		
		//for string
		k = "str key_1";
		v = "This is value 1 for key 1";
		
		if(tbl.put(k, v.getBytes(), InsertOptions.INSERT_UPDATE, null) < 0)
		{
			success = false;
       			System.out.println("str put, failed");
		}
		
		byte[] outval;
		if((outval = tbl.get(k, null)) == null)
		{
			success = false;
       			System.out.println("str get, failed");
		}
		else
		{
			if(!Arrays.equals(outval, v.getBytes()))
			{
				success = false;
	       			System.out.println("str mismatch get, failed");
			}
		}
		
		v = "Let's do the right thing, even if it discomforts all of us";
		if(tbl.put(k, v.getBytes(), InsertOptions.INSERT_UPDATE, null) < 0)
		{
			success = false;
       			System.out.println("str update, failed");
		}
		
		if((outval = tbl.get(k, null)) == null)
		{
			success = false;
       			System.out.println("str get, failed");
		}
		else
		{
			if(!Arrays.equals(outval, v.getBytes()))
			{
				success = false;
	       			System.out.println("str mismatch get, failed");
			}
		}
		
		if(tbl.del(k, null) < 0)
		{
			success = false;
       		System.out.println("str delete, failed");
		}
		if((outval = tbl.get(k, null)) != null)
		{
			success = false;
       			System.out.println("delete str received even after delete, failed");
		}
		return success?0:-1;
	}
}
