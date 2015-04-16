using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class SWTable
    {
        private IntPtr _swTable;

        public SWTable(Database db, string tableName, TableEnv tenv, int ttlSec, bool archive)
        {
            _swTable = BangDBNative.CreateSWTable(db.GetHandle(), tableName, tenv.GetHandle(), ttlSec, archive ? 1 : 0);
        }

        public int Initialize()
        {
            return BangDBNative.InitSWTable(_swTable);
        }

        public void AddIndex(string idxName, TableEnv tenv)
        {
            BangDBNative.AddIndexSWTable(_swTable, idxName, tenv.GetHandle());
        }

        public IntPtr GetConnection()
        {
            return BangDBNative.GetConnectionSWTable(_swTable);
        }

        public IntPtr GetActiveConnection()
        {
            return BangDBNative.GetActiveConnectionSWTable(_swTable);
        }

        public IntPtr GetPassiveConnection()
        {
            return BangDBNative.GetPassiveConnectionSWTable(_swTable);
        }

        public int Put(string str, InsertOptions flag)
        {
            return BangDBNative.PutSWTable(_swTable, str, str.Length, (int)flag);
        }

        public int Put(string str, string idxName, string idxKey)
        {
            return BangDBNative.PutSWTableIdx(_swTable, str, str.Length, idxName, idxKey, idxKey.Length);
        }

        public ResultSet Scan(int period)
        {
            IntPtr rs = BangDBNative.ScanSWTable(_swTable, period);
            if (rs == null)
                return null;
            return new ResultSet(rs);
        }

        public ResultSet Scan(int period, int lag)
        {
            IntPtr rs = BangDBNative.ScanLagSWTable(_swTable, period, lag);
            if (rs == null)
                return null;
            return new ResultSet(rs);
        }

        public ResultSet ScanFull()
        {
            IntPtr rs = BangDBNative.ScanFullSWTable(_swTable);
            if (rs == null)
                return null;
            return new ResultSet(rs);
        }

        public ResultSet ScanRemaining(long fromTime, int lag)
        {
            IntPtr rs = BangDBNative.ScanRemainingSWTable(_swTable, fromTime, lag);
            if (rs == null)
                return null;
            return new ResultSet(rs);
        }

        public int GetTTLSec()
        {
            return BangDBNative.GetTTLSWTable(_swTable);
        }

        public bool NeedPassive(int windowsec)
        {
            return BangDBNative.NeedPassiveSWTable(_swTable, windowsec) > 0 ? true : false;
        }

        public void Close()
        {
            BangDBNative.CloseSWTable(_swTable);
            BangDBNative.FreeHandle(ref _swTable);
            _swTable = IntPtr.Zero;
        }
    }
}
