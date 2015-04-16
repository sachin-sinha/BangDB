using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class SWCount : IQCount
    {
        private IntPtr _swsc;

        public SWCount(int swTime, int swExpiry, BangDBCountType countType)
        {
            _swsc = BangDBNative.CreateSWCount(swTime, swExpiry, (int)countType, (int)BangDBWindowType.SlidingWindowSpan);
        }
        public void Add(string s)
        {
            BangDBNative.AddSWCount(_swsc, s, s.Length, (int)BangDBWindowType.SlidingWindowSpan);
        }

        public int[] List(int span)
        {
            int[] list = null;
            int list_size = 0;
            if (BangDBNative.ListSWCount(_swsc, span, ref list, ref list_size, (int)BangDBWindowType.SlidingWindowSpan) < 0)
                return null;
            return list;
        }

        public int Count()
        {
            return BangDBNative.CountSWCount(_swsc, (int)BangDBWindowType.SlidingWindowSpan);
        }

        public int Count(int span)
        {
            return BangDBNative.CountSpanSWCount(_swsc, span, (int)BangDBWindowType.SlidingWindowSpan);
        }

        public void FoldSlots()
        {
            BangDBNative.FoldSlotsSWCount(_swsc, (int)BangDBWindowType.SlidingWindowSpan);
        }

        public void Reset()
        {
            BangDBNative.ResetSWCount(_swsc, (int)BangDBWindowType.SlidingWindowSpan);
        }

        public void Close()
        {
            BangDBNative.CloseSWCount(_swsc, (int)BangDBWindowType.SlidingWindowSpan);
            BangDBNative.FreeHandle(ref _swsc);
            _swsc = IntPtr.Zero;
        }
    }
}
