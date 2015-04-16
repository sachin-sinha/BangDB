using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class WideConnection
    {
        private IntPtr _wconnection;

        internal WideConnection(IntPtr wconn)
        {
            _wconnection = wconn;
        }

        public long PutDoc(string jsonStr)
        {
            return BangDBNative.Put_Doc(_wconnection, jsonStr);
        }

        public long PutDoc(string key, string jsonStr, InsertOptions flag)
        {
            return BangDBNative.Put_Doc_Str(_wconnection, key, jsonStr, (int)flag);
        }

        public long PutDoc(long key, string jsonStr, InsertOptions flag)
        {
            return BangDBNative.Put_Doc_Long(_wconnection, key, jsonStr, (int)flag);
        }

        public unsafe ResultSet ScanDoc(string idxName, string skey, string ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.Scan_Doc_Idx(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet ScanDoc(string idxName, byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.Scan_Doc_Idx(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet ScanDoc(string idxName, long skey, long ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.Scan_Doc_Idx_Long(_wconnection, idxName, skey, ekey, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet ScanDoc(string idxName, string skey, string ekey, ScanFilter sf, DataVar dv)
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

            IntPtr rsptr = BangDBNative.Scan_Doc_Idx_DV(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe ResultSet ScanDoc(string idxName, byte[] skey, byte[] ekey, ScanFilter sf, DataVar dv)
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

            IntPtr rsptr = BangDBNative.Scan_Doc_Idx_DV(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe ResultSet ScanDoc(string idxName, long skey, long ekey, ScanFilter sf, DataVar dv)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_Doc_Idx_Long_DV(_wconnection, idxName, skey, ekey, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe ResultSet Scan(string idxName, string skey, string ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanWIdx(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string idxName, byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanWIdx(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            if (rsptr == IntPtr.Zero)
                return null;
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string idxName, string skey, string ekey, ScanFilter sf, DataVar dv)
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

            IntPtr rsptr = BangDBNative.ScanWIdx_DV(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;

            if (rsptr == IntPtr.Zero)
                sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
                return null;
            return new ResultSet(rsptr);
        }

        public unsafe ResultSet Scan(string idxName, byte[] skey, byte[] ekey, ScanFilter sf, DataVar dv)
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

            IntPtr rsptr = BangDBNative.ScanWIdx_DV(_wconnection, idxName, skey, sklen, ekey, eklen, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public long Put(string key, string val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdx(_wconnection, key, key.Length, val, val.Length, idxName, idxVal, idxVal.Length); 
        }

        public long Put(string key, byte[] val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdx(_wconnection, key, key.Length, val, val.Length, idxName, idxVal, idxVal.Length); 
        }

        public long Put(long key, string val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdxLong(_wconnection, key, val, val.Length, idxName, idxVal, idxVal.Length);
        }

        public long Put(long key, byte[] val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdxLong(_wconnection, key, val, val.Length, idxName, idxVal, idxVal.Length);
        }

        public long Put(byte[] key, string val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdx(_wconnection, key, key.Length, val, val.Length, idxName, idxVal, idxVal.Length); 
        }

        public long Put(byte[] key, byte[] val, string idxName, string idxVal)
        {
            return BangDBNative.PutWIdx(_wconnection, key, key.Length, val, val.Length, idxName, idxVal, idxVal.Length); 
        }

        public bool Get(long key, out byte[] val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_LongW(_wconnection, key, ref valptr, ref vallen) < 0)
                return false;

            val = new byte[vallen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(long key, out string val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_LongW(_wconnection, key, ref valptr, ref vallen) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(long key, ref DataVar dv)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_conn, key, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(long key, ref DataVar dv, Transaction txn)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;
            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_conn, key, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(String key, ref DataVar dv)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_conn, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(String key, ref DataVar dv, Transaction txn)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_conn, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(byte[] key, ref DataVar dv)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvanced(_conn, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag);
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(byte[] key, ref DataVar dv, Transaction txn)
        {
            IntPtr _conn = BangDBNative.GetMainConn(_wconnection);
            if (_conn == IntPtr.Zero)
                return false;

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            int retval = BangDBNative.GetAdvancedTran(_conn, key, key.Length, ref pBuf, buflen, ref dlen, dofft, ref eflag, txn.GetTranPtr());
            dv.opsFlag = (BangDBDataOpsFlag)eflag;
            dv.bufferPointer = pBuf;
            dv.dataLength = dlen;
            return retval < 0 ? false : true;
        }

        public bool Get(string key, out byte[] val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.GetW(_wconnection, key, key.Length, ref valptr, ref vallen) < 0)
                return false;

            val = new byte[vallen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out byte[] val, Transaction txn)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_TranW(_wconnection, key, key.Length, ref valptr, ref vallen, txn.GetTranPtr()) < 0)
                return false;

            val = new byte[vallen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out string val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.GetW(_wconnection, key, key.Length, ref valptr, ref vallen) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(string key, out string val, Transaction txn)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_TranW(_wconnection, key, key.Length, ref valptr, ref vallen, txn.GetTranPtr()) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out byte[] val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.GetW(_wconnection, key, key.Length, ref valptr, ref vallen) < 0)
                return false;

            val = new byte[vallen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out byte[] val, Transaction txn)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.Get_TranW(_wconnection, key, key.Length, ref valptr, ref vallen, txn.GetTranPtr()) < 0)
                return false;

            val = new byte[vallen];
            System.Runtime.InteropServices.Marshal.Copy(valptr, val, 0, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public bool Get(byte[] key, out string val)
        {
            IntPtr valptr = IntPtr.Zero;
            int vallen = 0;
            val = null;
            if (BangDBNative.GetW(_wconnection, key, key.Length, ref valptr, ref vallen) < 0)
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
            if (BangDBNative.Get_TranW(_wconnection, key, key.Length, ref valptr, ref vallen, txn.GetTranPtr()) < 0)
                return false;

            val = Marshal.PtrToStringAnsi(valptr, vallen);
            BangDBNative.FreeBytes(valptr);
            return true;
        }

        public long Put(long key, string val, InsertOptions flag)
        {
            return BangDBNative.Put_LongW(_wconnection, key, val, val.Length, (int)flag);
        }

        public long Put(long key, string val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_Long_TranW(_wconnection, key, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(long key, byte[] val, InsertOptions flag)
        {
            return BangDBNative.Put_LongW(_wconnection, key, val, val.Length, (int)flag);
        }

        public long Put(long key, byte[] val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_Long_TranW(_wconnection, key, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(string key, string val, InsertOptions flag)
        {
            return BangDBNative.PutW(_wconnection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(string key, string val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_TranW(_wconnection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(string key, byte[] val, InsertOptions flag)
        {
            return BangDBNative.PutW(_wconnection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(string key, byte[] val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_TranW(_wconnection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(byte[] key, string val, InsertOptions flag)
        {
            return BangDBNative.PutW(_wconnection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(byte[] key, string val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_TranW(_wconnection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Put(byte[] key, byte[] val, InsertOptions flag)
        {
            return BangDBNative.PutW(_wconnection, key, key.Length, val, val.Length, (int)flag);
        }

        public long Put(byte[] key, byte[] val, InsertOptions flag, Transaction txn)
        {
            return BangDBNative.Put_TranW(_wconnection, key, key.Length, val, val.Length, (int)flag, txn.GetTranPtr());
        }

        public long Del(long key)
        {
            return BangDBNative.Del_longW(_wconnection, key);
        }

        public long Del(long key, Transaction txn)
        {
            return BangDBNative.Del_long_TranW(_wconnection, key, txn.GetTranPtr());
        }

        public long Del(string key)
        {
            return BangDBNative.DelW(_wconnection, key, key.Length);
        }

        public long Del(string key, Transaction txn)
        {
            return BangDBNative.Del_TranW(_wconnection, key, key.Length, txn.GetTranPtr());
        }

        public long Del(byte[] key)
        {
            return BangDBNative.DelW(_wconnection, key, key.Length);
        }

        public long Del(byte[] key, Transaction txn)
        {
            return BangDBNative.Del_TranW(_wconnection, key, key.Length, txn.GetTranPtr());
        }

        public unsafe ResultSet Scan(long skey, long ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            IntPtr rsptr = BangDBNative.Scan_LongW(_wconnection, skey, ekey, (IntPtr)sfptr);
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
            IntPtr rsptr = BangDBNative.Scan_Long_TranW(_wconnection, skey, ekey, txn.GetTranPtr(), (IntPtr)sfptr);
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

            IntPtr rsptr = BangDBNative.Scan_DV_LongW(_wconnection, skey, ekey, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

            IntPtr rsptr = BangDBNative.Scan_DV_Long_TranW(_wconnection, skey, ekey, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe ResultSet Scan(string skey, string ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;

            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanW(_wconnection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
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
            IntPtr rsptr = BangDBNative.Scan_TranW(_wconnection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr);
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

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DVW(_wconnection, skey, skey.Length, ekey, ekey.Length, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_TranW(_wconnection, skey, skey.Length, ekey, ekey.Length, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe ResultSet Scan(byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;

            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            IntPtr rsptr = BangDBNative.ScanW(_wconnection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
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
            IntPtr rsptr = BangDBNative.Scan_TranW(_wconnection, skey, sklen, ekey, eklen, txn.GetTranPtr(), (IntPtr)sfptr);
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

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DVW(_wconnection, skey, skey.Length, ekey, ekey.Length, (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

            IntPtr pBuf = dv.bufferPointer;
            int buflen = dv.bufferLength;
            int dlen = dv.dataLength;
            int dofft = dv.dataOffset;
            int eflag = (int)dv.opsFlag;

            IntPtr rsptr = BangDBNative.Scan_DV_TranW(_wconnection, skey, skey.Length, ekey, ekey.Length, txn.GetTranPtr(), (IntPtr)sfptr, pBuf, buflen, ref dlen, dofft, ref eflag);

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

        public unsafe long Count(long skey, long ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            long rc = BangDBNative.Count_LongW(_wconnection, skey, ekey, (IntPtr)sfptr);
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
            long rc = BangDBNative.CountW(_wconnection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public unsafe long Count(byte[] skey, byte[] ekey, ScanFilter sf)
        {
            ScanFilterStruct sfs = sf.sfs;
            long* sfptr = (long*)&sfs;
            int sklen = (skey != null) ? skey.Length : 0;
            int eklen = (ekey != null) ? ekey.Length : 0;
            long rc = BangDBNative.CountW(_wconnection, skey, sklen, ekey, eklen, (IntPtr)sfptr);
            sf.skeyOp = sfs.skeyOp;
            sf.ekeyOp = sfs.ekeyOp;
            sf.skip_count = sfs.skip_count;
            return rc;
        }

        public long Count()
        {
            ScanFilter sf = new ScanFilter();
            return Count((string)null, (string)null, sf);
        }

        public IntPtr GetHandle()
        {
            return _wconnection;
        }

        public void SetAutoCommit(bool flag)
        {
            BangDBNative.SetAutoCommitW(_wconnection, flag ? 1 : 0);
        }

        public PersistType GetPersistType()
        {
            return (PersistType)BangDBNative.GetPersistTypeW(_wconnection);
        }

        public IndexType GetIndexType()
        {
            return (IndexType)BangDBNative.GetIdxType(_wconnection);
        }

        public int CloseConnection()
        {
            int r = BangDBNative.CloseConnectionW(_wconnection);
             BangDBNative.FreeHandle(ref _wconnection);
            _wconnection = IntPtr.Zero;
            return r;
        }
    }
}
