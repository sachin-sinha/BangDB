using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class SWSlotCount : IQCount
    {
        private IntPtr _swsc;

        public SWSlotCount(int swTime, int swExpiry, BangDBCountType countType)
        {
            _swsc = BangDBNative.CreateSWCount(swTime, swExpiry, (int)countType, (int)BangDBWindowType.SlidingWindowUnit);
        }
        public void Add(string s)
        {
            BangDBNative.AddSWCount(_swsc, s, s.Length, (int)BangDBWindowType.SlidingWindowUnit);
        }

        public int[] List(int span)
        {
            int[] list = null;
            int list_size = 0;
            if (BangDBNative.ListSWCount(_swsc, span, ref list, ref list_size, (int)BangDBWindowType.SlidingWindowUnit) < 0)
                return null;
            return list;
        }

        public int Count()
        {
            return BangDBNative.CountSWCount(_swsc, (int)BangDBWindowType.SlidingWindowUnit);
        }

        public int Count(int span)
        {
            return BangDBNative.CountSpanSWCount(_swsc, span, (int)BangDBWindowType.SlidingWindowUnit);
        }

        public void FoldSlots()
        {
            BangDBNative.FoldSlotsSWCount(_swsc, (int)BangDBWindowType.SlidingWindowUnit);
        }

        public void Reset()
        {
            BangDBNative.ResetSWCount(_swsc, (int)BangDBWindowType.SlidingWindowUnit);
        }

        public void Close()
        {
            BangDBNative.CloseSWCount(_swsc, (int)BangDBWindowType.SlidingWindowUnit);
            BangDBNative.FreeHandle(ref _swsc);
            _swsc = IntPtr.Zero;
        }
    }
}
