using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class TopK
    {
        private IntPtr _topk;

        public TopK(string name, int swSizeSec, int k, bool desc, string uniqueBy)
        {
            _topk = BangDBNative.CreateTopk(name, swSizeSec, k, desc ? 1 : 0, uniqueBy);
        }

        public void Put(long score, string data, string uniqueParam)
        {
            BangDBNative.Put_topk(_topk, score, data, data.Length, uniqueParam);
        }

        public ResultSet GetTopK(int k = 0)
        {
            IntPtr rs = BangDBNative.GetTopk(_topk, k);
            return rs == null ? null : new ResultSet(rs);
        }

        public string GetTopKJson(int k = 0)
        {
            IntPtr str = IntPtr.Zero;
            BangDBNative.GetTopkJson(_topk, out str, k);
            string jstr = Marshal.PtrToStringAnsi(str);
            BangDBNative.FreeHandle(ref str);
            return jstr;
        }

        public void Close()
        {
            BangDBNative.CloseTopk(_topk);
            BangDBNative.FreeHandle(ref _topk);
            _topk = IntPtr.Zero;
        }
    }
}
