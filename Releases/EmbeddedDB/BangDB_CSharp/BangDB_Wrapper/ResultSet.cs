using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class ResultSet
    {
        private IntPtr _rs;

        public ResultSet(IntPtr rs)
        {
            _rs = rs;
        }

        public void AddDoc(ResultSet rs, string orderBy = null)
        {
            BangDBNative.Add_Doc(_rs, rs._rs, orderBy);
        }

        public void Add(ResultSet rs)
        {
            BangDBNative.Add(_rs, rs._rs);
        }

        public void Append(ResultSet rs)
        {
            BangDBNative.Append(_rs, rs._rs);
        }

        public void Intersect(ResultSet rs)
        {
            BangDBNative.Intersect(_rs, rs._rs);
        }

        public bool GetNextKey(out byte[] key)
        {
            IntPtr kptr;
            int klen;
            if (BangDBNative.GetNextKey(_rs, out kptr, out klen) < 0)
            {
                key = null;
                return false;
            }
            key = new byte[klen];
            System.Runtime.InteropServices.Marshal.Copy(kptr, key, 0, klen);
            return true;
        }

        public bool GetNextKey(out string key)
        {
            IntPtr kptr;
            int klen;
            if (BangDBNative.GetNextKey(_rs, out kptr, out klen) < 0)
            {
                key = null;
                return false;
            }
            key = Marshal.PtrToStringAnsi(kptr, klen);
            return true;
        }

        public long GetNextKeyLong()
        {
            return BangDBNative.GetNextKeyLong(_rs);
        }

        public int GetNextKeyInt()
        {
            return (int)BangDBNative.GetNextKeyLong(_rs);
        }

        public string GetNextKeyStr()
        {
            string key = null;
            if (!GetNextKey(out key))
                return null;
            return key;
        }

        public bool GetNextVal(out byte[] val)
        {
            IntPtr vptr;
            int vlen;
            if (BangDBNative.GetNextVal(_rs, out vptr, out vlen) < 0)
            {
                val = null;
                return false;
            }
            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(vptr, val, 0, vlen);
            return true;
        }

        public bool GetNextVal(out string val)
        {
            IntPtr vptr;
            int vlen;
            if (BangDBNative.GetNextVal(_rs, out vptr, out vlen) < 0)
            {
                val = null;
                return false;
            }
            val = Marshal.PtrToStringAnsi(vptr, vlen);
            return true;
        }

        public long GetNextValLong()
        {
            return BangDBNative.GetNextValLong(_rs);
        }

        public int GetNextValInt()
        {
            return (int)BangDBNative.GetNextValLong(_rs);
        }

        public string GetNextValStr()
        {
            string val = null;
            if (!GetNextVal(out val))
            {
                return null;
            }
            return val;
        }

        public bool HasNext()
        {
            return BangDBNative.HasNext(_rs) == 1;
        }

        public void MoveNext()
        {
            BangDBNative.MoveNext(_rs);
        }

        public void Begin()
        {
            BangDBNative.Begin(_rs);
        }

        public void BeginReverse()
        {
            BangDBNative.BeginReverse(_rs);
        }

        public void Clear()
        {
            BangDBNative.Clear(_rs);
            BangDBNative.FreeHandle(ref _rs);
            _rs = IntPtr.Zero;
        }

        public bool LastEvaluatedKey(out byte[] key)
        {
            IntPtr kptr;
            int klen;
            BangDBNative.LastEvaluatedKey(_rs, out kptr, out klen);
            if(kptr == IntPtr.Zero || klen == 0)
            {
                key = null;
                return false;
            }
            key = new byte[klen];
            System.Runtime.InteropServices.Marshal.Copy(kptr, key, 0, klen);
            BangDBNative.FreeBytes(kptr);
            return true;
        }

        public bool LastEvaluatedKey(out string key)
        {
            IntPtr kptr;
            int klen;
            BangDBNative.LastEvaluatedKey(_rs, out kptr, out klen);
            if(kptr == IntPtr.Zero || klen == 0)
            {
                key = null;
                return false;
            }
            key = Marshal.PtrToStringAnsi(kptr, klen);
            BangDBNative.FreeBytes(kptr);
            return true;
        }

        public long LastEvaluatedKeyLong()
        {
            return BangDBNative.LastEvaluatedKeyLong(_rs);
        }

        public bool MoreDataToCome()
        {
            return BangDBNative.MoreDataToCome(_rs)==1?true:false;
        }

        public bool SearchValue(byte[] key, out byte[] val)
        {
            IntPtr vptr;
            int vlen;
            BangDBNative.SearchValue(_rs, key, key.Length, out vptr, out vlen);
            if(vptr == IntPtr.Zero || vlen == 0)
            {
                val = null;
                return false;
            }
            val = new byte[vlen];
            System.Runtime.InteropServices.Marshal.Copy(vptr, val, 0, vlen);
            return true;
        }

        public bool SearchValue(string key, out string val)
        {
            IntPtr vptr;
            int vlen;
            BangDBNative.SearchValue(_rs, key, key.Length, out vptr, out vlen);
            if (vptr == IntPtr.Zero || vlen == 0)
            {
                val = null;
                return false;
            }
            val = Marshal.PtrToStringAnsi(vptr, vlen);
            return true;
        }

        public int Count()
        {
            return BangDBNative.RSCount(_rs);
        }

        public int Size()
        {
            return BangDBNative.Size(_rs);
        }

        public int RSDataSize()
        {
            return BangDBNative.RSDataSize(_rs);
        }
    }
}
