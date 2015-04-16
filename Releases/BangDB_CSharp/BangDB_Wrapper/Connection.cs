using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class Connection
    {
        private IntPtr _connection;

        internal Connection(IntPtr conn)
        {
            _connection = conn;
        }

        public bool Get(long key, byte[] val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vlen = 0;
            val = null;
            if (BangDBNative.Get_Long_Str(_connection, key, ref valptr, ref vlen) < 0)
                return false;
            
            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(long key, out string vout)
        {
            IntPtr valptr = IntPtr.Zero;
            int vlen = 0;
            vout = null;
            if (BangDBNative.Get_Long_Str(_connection, key, ref valptr, ref vlen) < 0)
                return false;

            vout = Marshal.PtrToStringAnsi(valptr, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }
/*
        public bool Get(long key, out byte[] val)
        {
            byte[] k = BitConverter.GetBytes(key);
            val = Get(k);
            return (val == null) ? false : true;
        }

        public bool Get(long key, out byte[] val, Transaction txn)
        {
            byte[] k = BitConverter.GetBytes(key);
            val = Get(k, txn);
            return (val == null) ? false : true;
        }

        public bool Get(long key, out string val)
        {
            byte[] k = BitConverter.GetBytes(key);

            IntPtr valptr;
            int vlen;
            if (BangDBNative.Get(_connection, k, k.Length, out valptr, out vlen) < 0)
                val = null;
            else
            {
                val = Marshal.PtrToStringAnsi(valptr, vlen); 
                BangDBNative.FreeBytes(valptr);
            }
            return (val == null) ? false : true;
        }

        public bool Get(long key, out string val, Transaction txn)
        {
            byte[] k = BitConverter.GetBytes(key);

            IntPtr valptr;
            int vlen;
            if (BangDBNative.Get_Tran(_connection, k, k.Length, out valptr, out vlen, txn.GetTranPtr()) < 0)
                val = null;
            else
            {
                val = Marshal.PtrToStringAnsi(valptr, vlen);
                BangDBNative.FreeBytes(valptr);
            }
            return (val == null) ? false : true;
        }
*/
        public bool Get(string key, out byte[] val)
        {
            if(key == null)
                throw new Exception("key can't be null");
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get(_connection, key, key.Length, out valptr, out vlen) < 0)
                return false;

            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out byte[] val, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get_Tran(_connection, key, key.Length, out valptr, out vlen, txn.GetTranPtr()) < 0)
                return false;

            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out string val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get(_connection, key, key.Length, out valptr, out vallen) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out string val, Transaction txn)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_Tran(_connection, key, key.Length, out valptr, out vallen, txn.GetTranPtr()) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out byte[] val)
        {
            if (key == null)
                throw new Exception("key can't be null");
            //string k = System.Text.Encoding.UTF8.GetString(key);
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get(_connection, key, key.Length, out valptr, out vlen) < 0)
                return false;

            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out byte[] val, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");
            //string k = System.Text.Encoding.UTF8.GetString(key);
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get_Tran(_connection, key, key.Length, out valptr, out vlen, txn.GetTranPtr()) < 0)
                return false;

            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out string val)
        {
            if (key == null)
                throw new Exception("key can't be null");
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get(_connection, key, key.Length, out valptr, out vlen) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out string val, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");
            IntPtr valptr;
            int vlen;
            val = null;
            if (BangDBNative.Get_Tran(_connection, key, key.Length, out valptr, out vlen, txn.GetTranPtr()) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vlen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, ref DataVar dv)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_connection, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(string key, ref DataVar dv, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_connection, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(byte[] key, ref DataVar dv)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_connection, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(byte[] key, ref DataVar dv, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_connection, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(long key, ref DataVar dv)
        {
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_connection, key, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(long key, ref DataVar dv, Transaction txn)
        {
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_connection, key, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }
/*
        public int Put(long key, byte[] val, InsertOptions flag)
        {
            if (val == null)
                throw new Exception("val can't be null");
            byte[] k = BitConverter.GetBytes(key);
            return Put(k, val, flag);
        }

        public int Put(long key, byte[] val, InsertOptions flag, Transaction txn)
        {
            if (val == null)
                throw new Exception("val can't be null");
            byte[] k = BitConverter.GetBytes(key);
            return Put(k, val, flag, txn);
        }

        public int Put(long key, string val, InsertOptions flag)
        {
            if (val == null)
                throw new Exception("val can't be null");
            byte[] k = BitConverter.GetBytes(key);
            return BangDBNative.Put(_connection, k, k.Length, val, val.Length, (int)flag);
        }

        public int Put(long key, string val, InsertOptions flag, Transaction txn)
        {
            if (val == null)
                throw new Exception("val can't be null");
            byte[] k = BitConverter.GetBytes(key);
            return BangDBNative.Put_Tran(_connection, k, k.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }
*/
        

        public long Put(long key, string val, InsertOptions flag)
        {
            return BangDBNative.PutByte_Long(_connection, key, val, val.Length, (int)flag);
        }

        public long Put(long key, byte[] val, InsertOptions flag)
        {
            return BangDBNative.PutByte_Long(_connection, key, val, val.Length, (int)flag);
        }

        public long Put(long key, string val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.PutByte_Long_Tran(_connection, key, val, val.Length, (int)flag, txn.GetTranPtr());
        }
            public long Put(long key, byte[] val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.PutByte_Long_Tran(_connection, key, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(byte[] key, byte[] val, InsertOptions flag)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put(_connection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(byte[] key, byte[] val, InsertOptions flag, Transaction txn)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put_Tran(_connection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(string key, string val, InsertOptions flag)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put(_connection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(string key, string val, InsertOptions flag, Transaction txn)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put_Tran(_connection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(string key, byte[] val, InsertOptions flag)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put(_connection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(string key, byte[] val, InsertOptions flag, Transaction txn)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put_Tran(_connection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(byte[] key, string val, InsertOptions flag)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put(_connection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(byte[] key, string val, InsertOptions flag, Transaction txn)
        {
            if (key == null || val == null)
                throw new Exception("key or/and val can't be null");
            return BangDBNative.Put_Tran(_connection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(string key, ref DataVar dv, InsertOptions flag)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            long retval = BangDBNative.PutAdvanced(_connection, key, key.Length, pBuf, buflen, ref dlen, dofft, ref eflag, (int)flag);
            dv.dataLength = dlen;
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            return retval;
        }

        public long Put(byte[] key, ref DataVar dv, InsertOptions flag)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            long retval = BangDBNative.PutAdvanced(_connection, key, key.Length, pBuf, buflen, ref dlen, dofft, ref eflag, (int)flag);
            dv.dataLength = dlen;
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            return retval;
        }

        public long Put(string key, ref DataVar dv, InsertOptions flag, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            long retval = BangDBNative.PutAdvanced_Tran(_connection, key, key.Length, pBuf, buflen, ref dlen, dofft, ref eflag, (int)flag, txn.GetTranPtr());
            dv.dataLength = dlen;
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            return retval;
        }

        public long Put(byte[] key, ref DataVar dv, InsertOptions flag, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            long retval = BangDBNative.PutAdvanced_Tran(_connection, key, key.Length, pBuf, buflen, ref dlen, dofft, ref eflag, (int)flag, txn.GetTranPtr());
            dv.dataLength = dlen;
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            return retval;
        }

        public long Del(byte[] key)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.Del(_connection, key, key.Length);
        }

        public long Del(byte[] key, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.Del_Tran(_connection, key, key.Length, txn.GetTranPtr());
        }

        public long Del(string key)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.Del(_connection, key, key.Length);
        }

        public long Del(string key, Transaction txn)
        {
            if (key == null)
                throw new Exception("key can't be null");
            return BangDBNative.Del_Tran(_connection, key, key.Length, txn.GetTranPtr());
        }

        public long Del(long key)
        {
            return BangDBNative.Del_Long(_connection, key);
        }

        public long Del(long key, Transaction txn)
        {
            return BangDBNative.Del_Long_Tran(_connection, key, txn.GetTranPtr());
        }

        /*
        public unsafe ResultSet Scan(long skey, long ekey, ScanFilter sf)
        {
            long *sfptr = (long*)&sf;
            IntPtr rsptr = BangDBNative.Scan_Long(_connection, skey, ekey, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            return new ResultSet(rsptr);
        }
        
        public ResultSet Scan(long skey, long ekey, ScanFilter sf)
        {
            IntPtr sfptr = Common.MarshalToPointer(sf);
            IntPtr rsptr = BangDBNative.Scan_Long(_connection, skey, ekey, sfptr);
            Common.FreeStructPtr(sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            return new ResultSet(rsptr);
        }
        */
        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.Scan(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, Transaction txn, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.Scan_Tran(_connection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr);
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
            IntPtr rsptr = BangDBNative.Scan(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string skey, string ekey, Transaction txn, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.Scan_Tran(_connection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(long skey, long ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.Scan_Long(_connection, skey, ekey, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(long skey, long ekey, Transaction txn, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.Scan_Long_Tran(_connection, skey, ekey, txn.GetTranPtr(), (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string skey, string ekey, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string skey, string ekey, Transaction txn, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_Tran(_connection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, Transaction txn, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_Tran(_connection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(long skey, long ekey, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_Long(_connection, skey, ekey, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(long skey, long ekey, Transaction txn, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_Long_Tran(_connection, skey, ekey, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

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
            long rc = BangDBNative.Count(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
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
            long rc = BangDBNative.Count(_connection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public long Count()
        {
            ScanFilter sf = new ScanFilter();
            return Count((byte[])null, (byte[])null, sf);
        }

        public unsafe long Count(long sk, long ek, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            long rc = BangDBNative.Count_LONG(_connection, sk, ek, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public unsafe long Count(int sk, int ek, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            long rc = BangDBNative.Count_LONG(_connection, sk, ek, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public int CloseConnection()
        {
            int r = BangDBNative.CloseConnection(_connection);
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
            BangDBNative.SetAutoCommit(_connection, flag?1:0);
        }

        public PersistType GetPersistType()
        {
            return (PersistType)BangDBNative.GetPersistType(_connection);
        }

        public IndexType GetIndexType()
        {
            return (IndexType)BangDBNative.GetIdxType(_connection);
        }

        //private functions
        private bool Get(long key, ref long val)
        {
            return BangDBNative.GetPrim(_connection, key, ref val) < 0 ? false : true;
        }

        private bool Get(string key, ref long val)
        {
            return BangDBNative.GetPrim_Str(_connection, key, key.Length, ref val) < 0 ? false : true;
        }

        private bool Get(byte[] key, ref long val)
        {
            return BangDBNative.GetPrim_Byte(_connection, key, key.Length, ref val) < 0 ? false : true;
        }

        private long Put(long key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim(_connection, key, val, (int)flag);
        }

        private long Put(string key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim_Str(_connection, key, key.Length, val, (int)flag);
        }

        private long Put(byte[] key, long val, InsertOptions flag)
        {
            return BangDBNative.PutPrim_Byte(_connection, key, key.Length, val, (int)flag);
        }
    }
}
