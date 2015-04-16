using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class PrimConnection
    {
         private IntPtr _connection;

        internal PrimConnection(IntPtr conn)
        {
            _connection = conn;
        }
        public bool Get(long key, ref long val)
        {
            return BangDBNative.GetPrim(_connection, key, ref val) < 0 ? false : true;
        }

        public bool Get(int key, ref int val)
        {
            long _val = val;
            int r = BangDBNative.GetPrim(_connection, (long)key, ref _val);
            val = (int)_val;
            return r < 0 ? false : true;
        }

        public bool Get(string key, ref long val)
        {
            return BangDBNative.GetPrim_Str(_connection, key, key.Length, ref val) < 0 ? false : true;
        }

        public bool Get(byte[] key, ref long val)
        {
            return BangDBNative.GetPrim_Byte(_connection, key, key.Length, ref val) < 0 ? false : true;
        }

        public long Put(long key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim(_connection, key, val, (int)flag);
        }

        public long Put(int key, int val, InsertOptions flag)
        {
            return BangDBNative.PutPrim(_connection, key, val, (int)flag);
        }

        public long Put(string key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim_Str(_connection, key, key.Length, val, (int)flag);
        }

        public long Put(byte[] key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim_Byte(_connection, key, key.Length, val, (int)flag);
        }

        public long Del(byte[] key)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.DelPrim_Byte(_connection, key, key.Length);
        }

        public long Del(string key)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.DelPrim_Str(_connection, key, key.Length);
        }

        public long Del(long key)
        {
            return BangDBNative.DelPrim_Long(_connection, key);
        }

        public long Del(int key)
        {
            return BangDBNative.DelPrim_Long(_connection, (long)key);
        }

        public unsafe ResultSet Scan(long skey, long ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.ScanPrim_Long(_connection, skey, ekey, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(int skey, int ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.ScanPrim_Long(_connection, (long)skey, (long)ekey, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanPrim_Byte(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string skey, string ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanPrim_Str(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe long Count(byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            long rc = BangDBNative.CountPrim_Byte(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public unsafe long Count(string skey, string ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            long rc = BangDBNative.CountPrim_Str(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public unsafe long Count()
        {
            ScanFilter sf = new ScanFilter();
            return Count((byte[])null, (byte[])null, sf);
        }

        public unsafe long Count(long sk, long ek, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            long rc = BangDBNative.CountPrim_Long(_connection, sk, ek, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public unsafe long Count(int sk, int ek, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            long rc = BangDBNative.CountPrim_Long(_connection, (long)sk, (long)ek, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public int CloseConnection()
        {
            int r = BangDBNative.ClosePrimConnection(_connection);
            BangDBNative.FreeHandle(ref _connection);
            _connection = IntPtr.Zero;
            return r;
        }

        public IntPtr GetHandle()
        {
            return _connection;
        }

        public void SetAutoCommit(bool flag)
        {
            BangDBNative.SetAutoCommitPrim(_connection, flag ? 1 : 0);
        }

        public PersistType GetPersistType()
        {
            return (PersistType)BangDBNative.GetPrimPersistType(_connection);
        }

        public IndexType GetIndexType()
        {
            return (IndexType)BangDBNative.GetPrimIdxType(_connection);
        }
    }
}
