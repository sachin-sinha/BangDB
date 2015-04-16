using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class WideTable
    {
        private IntPtr _wtable;
        private string _name;

        internal WideTable(string name, IntPtr wtable)
        {
            _wtable = wtable;
            _name = name;
        }

        public int AddIndex_Str(string idxName, int idxSizeByte, bool allowDuplicates)
        {
            return BangDBNative.AddIndex_Str(_wtable, idxName, idxSizeByte, allowDuplicates ? 1 : 0);
        }

        public int AddIndex_Num(string idxName, bool allowDuplicates)
        {
            return BangDBNative.AddIndex_Num(_wtable, idxName, allowDuplicates ? 1 : 0);
        }

        public int AddIndex(string idxName, TableEnv tenv)
        {
            return BangDBNative.AddIndex(_wtable, idxName, tenv.GetHandle());
        }

        public int DropIndex(string idxName)
        {
            return BangDBNative.DropIndex(_wtable, idxName);
        }

        public WideConnection GetConnection()
        {
            IntPtr wconnptr = BangDBNative.GetWideConnection(_wtable);
            if(wconnptr == null)
                return null;
            return new WideConnection(wconnptr);
        }

        public int CloseAllConnection()
        {
            return BangDBNative.CloseAllWideConnections(_wtable);
        }

        public int DumpData()
        {
            return BangDBNative.WideDumpData(_wtable);
        }

        public string GetName()
        {
            return BangDBNative.GetWideTableName(_wtable);
        }

        public IntPtr GetHandle()
        {
            return _wtable;
        }

        public int CloseTable(DBCloseType flag = DBCloseType.Default)
        {
            int r = BangDBNative.CloseThisWideTable(_wtable, (int)flag);
            BangDBNative.FreeHandle(ref _wtable);
            _wtable = IntPtr.Zero;
            return r;
        }
    }
}
