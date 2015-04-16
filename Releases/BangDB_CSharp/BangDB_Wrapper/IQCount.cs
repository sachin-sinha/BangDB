using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public interface IQCount
    {
        void Add(string s);

        int[] List(int span);

        int Count();

        int Count(int span);

        void FoldSlots();

        void Reset();

        void Close();
    }
}
