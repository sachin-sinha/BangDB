using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using BangDB_CSharp;

namespace bangdb_driver
{
    struct TParam
    {
        public Connection conn;
        public int nStart;
        public int nSlice;

        public TParam(Connection _conn, int a, int b)
        {
            conn = _conn;
            nStart = a;
            nSlice = b;
        }
    }
    public class bangdb_test
    {
        private static string KEYSTR = "key_prodid";
        private static string VALSTR = "This is the product type PC for dummys";

        public static void PutGetTest(int N, int nT, string path)
        {
            Database db = new Database("mydb", path);
            Table tbl = db.GetTable("mytbl");
            if (tbl == null)
            {
                Console.WriteLine("err in tbl creation");
                return;
            }
            Connection conn = tbl.GetConnection();
            if (conn == null)
            {
                Console.WriteLine("err in conn creation");
                return;
            }

            Stopwatch sw = new Stopwatch();

            sw.Start();
            MultiThreadPutPerfTest(conn, N, nT);
            sw.Stop();
            Console.WriteLine("Put test for {0} items using {1} threads completed in {2} ms", N, nT, sw.ElapsedMilliseconds);

            sw.Start();
            MultiThreadGetPerfTest(conn, N, nT);
            sw.Stop();
            Console.WriteLine("Get test for {0} items using {1} threads completed in {2} ms", N, nT, sw.ElapsedMilliseconds);

            db.CloseDatabase();

            Console.WriteLine("Put and Get Test Completed.");
        }
        public static void PutTest(int N, int nT, string path)
        {
            Database db = new Database("mydb", path);
            Table tbl = db.GetTable("mytbl");
            if (tbl == null)
            {
                Console.WriteLine("err in tbl creation");
                return;
            }
            Connection conn = tbl.GetConnection();
            if (conn == null)
            {
                Console.WriteLine("err in conn creation");
                return;
            }

            Stopwatch sw = new Stopwatch();

            sw.Start();

            MultiThreadPutPerfTest(conn, N, nT);

            sw.Stop();

            Console.WriteLine("Put test for {0} items using {1} threads completed in {2} ms", N, nT, sw.ElapsedMilliseconds);

            db.CloseDatabase();

            Console.WriteLine("Put Test Completed.");
        }
        public static void GetTest(int N, int nT, string path)
        {
            Database db = new Database("mydb", path);
            Table tbl = db.GetTable("mytbl");
            if (tbl == null)
            {
                Console.WriteLine("err in tbl creation");
                return;
            }
            Connection conn = tbl.GetConnection();
            if (conn == null)
            {
                Console.WriteLine("err in conn creation");
                return;
            }

            Stopwatch sw = new Stopwatch();

            sw.Start();

            MultiThreadGetPerfTest(conn, N, nT);

            sw.Stop();

            Console.WriteLine("Get test for {0} items using {1} threads completed in {2} ms", N, nT, sw.ElapsedMilliseconds);

            db.CloseDatabase();

            Console.WriteLine("Get Test Completed.");
        }
        static void MultiThreadPutPerfTest(Connection conn, int N, int nT)
        {
            int nslice = N / nT;
            int nstart = 0;
            Thread[] th = new Thread[nT];
            TParam[] tp = new TParam[nT];

            for (int i = 0; i < nT; i++)
            {
                tp[i] = new TParam(conn, nstart, nslice);
                th[i] = new Thread(ThreadPut);
                th[i].Start(tp[i]);
                nstart += nslice;
            }

            for (int i = 0; i < nT; i++)
            {
                th[i].Join();
            }
        }

        static void MultiThreadGetPerfTest(Connection conn, int N, int nT)
        {
            int nslice = N / nT;
            int nstart = 0;
            Thread[] th = new Thread[nT];
            TParam[] tp = new TParam[nT];

            for (int i = 0; i < nT; i++)
            {
                tp[i] = new TParam(conn, nstart, nslice);
                th[i] = new Thread(ThreadGet);
                th[i].Start(tp[i]);
                nstart += nslice;
            }

            for (int i = 0; i < nT; i++)
            {
                th[i].Join();
            }
        }
        static void ThreadPut(object _tp)
        {
            int error = 0;
            TParam tp = (TParam)_tp;
            Connection conn = tp.conn;
            int nstart = tp.nStart;
            int nitem = tp.nSlice;
            
            error = PutByte(conn, nstart, nitem);
            
            if (error < 0)
                Console.WriteLine("Test for Put Failed");
        }
       
        static int PutByte(Connection conn, int nstart, int nitem)
        {
            byte[] key; byte[] val;

            int status = 0;

            for (int i = nstart; i < (nitem + nstart); i++)
            {
                key = Encoding.UTF8.GetBytes(KEYSTR + i);
                val = Encoding.UTF8.GetBytes(VALSTR + i);
                if (conn.Put(key, val, InsertOptions.InsertUnique) < 0)
                    status++;
            }

            if (status != 0)
                Console.WriteLine("Put Test failed!. failed to put {0} items", status);
            else
                Console.WriteLine("Put Test Passed for {0} items!", nitem);

            return status == 0 ? 0 : -1;
        }

        static void ThreadGet(Object _tp)
        {
            int error = 0;
            TParam tp = (TParam)_tp;
            Connection conn = tp.conn;
            int nstart = tp.nStart;
            int nitem = tp.nSlice;

            error = GetByte(conn, nstart, nitem);
            if(error < 0)
                Console.WriteLine("Test for Get Failed");
        }
       
        static int GetByte(Connection conn, int nstart, int nitem)
        {
            byte[] key;
            byte[] val;
            byte[] rval;

            int status = 0, mismatch = 0;

            for (int i = nstart; i < (nitem + nstart); i++)
            {
                key = Encoding.UTF8.GetBytes(KEYSTR + i);
                val = Encoding.UTF8.GetBytes(VALSTR + i);

                if (!conn.Get(key, out rval))
                    status++;
                else if (!rval.SequenceEqual(val))
                    mismatch++;
            }

            if (status != 0)
                Console.WriteLine("Get Test failed!. failed to get {0} items", status);
            else if (mismatch != 0)
                Console.WriteLine("Get Test mismatch for {0} items!", mismatch);
            else
            {
                Console.WriteLine("Get Test Passed for {0} items!", nitem);
            }

            return (status == 0 && mismatch == 0) ? 0 : -1;
        }
        public static int TestSanityAllStr(string path = null)
        {
            string _dbname = "mydb";
            Database db = new Database(_dbname, path);
            Table tbl = db.GetTable("mytbl");
            Connection conn = tbl.GetConnection();

            bool status = true;

            string k = "key1";
            string v = "value is 1";

            if (conn.Put(k, v, InsertOptions.InsertUnique) < 0)
            {
                Console.WriteLine("error in put");
                status = false;
            }

            string o = null;
            if (!conn.Get(k, out o))
                status = false;

            if (!o.Equals(v))
            {
                Console.WriteLine("the retrieved val is not the same = " + o);
                status = false;
            }

            k = "key2";
            v = "the value is 2";

            if (conn.Put(k, v, InsertOptions.InsertUnique) < 0)
            {
                Console.WriteLine("error in put");
                status = false;
            }

            if (!conn.Get(k, out o))
                status = false;

            if (o == null)
            {
                Console.WriteLine("key not found, error");
                status = false;
            }

            if (!o.Equals(v))
            {
                Console.WriteLine("the retrieved val is not the same = " + o);
                status = false;
            }

            if (conn.Del(k) < 0)
            {
                Console.WriteLine("error in deleting key = " + k);
                status = false;
            }

            //try n get the deleted key
            if (conn.Get(k, out o))
                status = false;

            if (o != null)
            {
                Console.WriteLine("key not deleted, error");
                status = false;
            }

            //update
            k = "key1";
            v = "value is 3";
            if (conn.Put(k, v, InsertOptions.UpdateExisting) < 0)
            {
                Console.WriteLine("the update failed for key = " + k);
                status = false;
            }

            if (!conn.Get(k, out o))
                status = false;

            if (o == null)
            {
                Console.WriteLine("key not found, error");
                status = false;
            }

            if (!o.Equals(v))
            {
                Console.WriteLine("the retrieved val is not the same = " + o);
                status = false;
            }

            db.CloseDatabase();

            if (!status)
                Console.WriteLine("Test failed.");
            else
                Console.WriteLine("Test Passed!");

            return status ? 0 : -1;
        }
        public static int TestSanityAllByte(string path = null)
        {
            string _dbname = "mydb";
            Database db = new Database(_dbname, path);
            Table tbl = db.GetTable("mytbl");
            Connection conn = tbl.GetConnection();

            bool status = true;

            string k1 = "key1";
            string v1 = "value is 1";

            byte[] k = Encoding.UTF8.GetBytes(k1);
            byte[] v = Encoding.UTF8.GetBytes(v1);

            if (conn.Put(k, v, InsertOptions.InsertUnique) < 0)
            {
                Console.WriteLine("error in put");
                status = false;
            }

            byte[] o = null;
            if (!conn.Get(k, out o))
                status = false;

            if (o == null)
            {
                Console.WriteLine("key not found, error");
                status = false;
            }

            if (!o.SequenceEqual(v))
            {
                Console.WriteLine("the retrieved val is not the same");
                status = false;
            }

            k = Encoding.UTF8.GetBytes("key2");
            v = Encoding.UTF8.GetBytes("the value is 2");

            if (conn.Put(k, v, InsertOptions.InsertUnique) < 0)
            {
                Console.WriteLine("error in put");
                status = false;
            }

            if (!conn.Get(k, out o))
                status = false;

            if (o == null)
            {
                Console.WriteLine("key not found, error");
                status = false;
            }

            if (!o.SequenceEqual(v))
            {
                Console.WriteLine("the retrieved val is not the same");
                status = false;
            }

            if (conn.Del(k) < 0)
            {
                Console.WriteLine("error in deleting key = " + k.ToString());
                status = false;
            }

            //try n get the deleted key
            if (conn.Get(k, out o))
                status = false;

            if (o != null)
            {
                Console.WriteLine("key not deleted, error");
                status = false;
            }

            k = Encoding.UTF8.GetBytes("key1");
            v = Encoding.UTF8.GetBytes("value is 3");
            if (conn.Put(k, v, InsertOptions.UpdateExisting) < 0)
            {
                Console.WriteLine("the update failed for key = " + k.ToString());
                status = false;
            }

            if (!conn.Get(k, out o))
                status = false;

            if (o == null)
            {
                Console.WriteLine("key not found, error");
                status = false;
            }

            if (!o.SequenceEqual(v))
            {
                Console.WriteLine("the retrieved val is not the same = " + o.ToString());
                status = false;
            }

            db.CloseDatabase();

            if (!status)
                Console.WriteLine("Test failed.");
            else
                Console.WriteLine("Test Passed!");

            return status ? 0 : -1;
        }
    }
}
