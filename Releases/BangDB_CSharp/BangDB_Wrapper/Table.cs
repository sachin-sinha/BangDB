using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class Table
    {
        private IntPtr _table;
        private string _tableName;

        internal Table(string tblName, IntPtr table)
        {
            _tableName = tblName;
            _table = table;
        }

        public Connection GetConnection()
        {
            if (GetTableType() != BangDBTableType.NormalTable)
            {
                Common.BangDBLogger("error - the table type (BangDBTableType) is not NormalTable");
                return null;
            }
            IntPtr _conn = BangDBNative.GetConnection(_table);
            Connection conn = new Connection(_conn);
            return conn;
        }

        public PrimConnection GetPrimConnection()
        {
            BangDBTableType tp = GetTableType();
            if (tp != BangDBTableType.PrimitiveTableInt && tp != BangDBTableType.PrimitiveTableLong && tp != BangDBTableType.PrimitiveTableString)
            {
                Common.BangDBLogger("error - the table type (BangDBTableType) is not primitive type");
                return null;
            }
            IntPtr _conn = BangDBNative.GetPrimConnection(_table);
            PrimConnection conn = new PrimConnection(_conn);
            return conn;
        }

        public PersistType GetPersistType()
        {
            return (PersistType)BangDBNative.GetTablePersistType(_table);
        }

        public BangDBTableType GetTableType()
        {
            return (BangDBTableType)BangDBNative.GetTableType(_table);
        }

        public int DumpData()
        {
            return BangDBNative.DumpData(_table);
        }

        public string GetTableName()
        {
            IntPtr nameptr = BangDBNative.GetTableName(_table);
            return nameptr.ToString();
        }

        public int CloseTable(DBCloseType flag = DBCloseType.Default)
        {
            int r = BangDBNative.CloseThisTable(_table, (int)flag);
            BangDBNative.FreeHandle(ref _table);
            _table = IntPtr.Zero;
            return r;
        }

        public IntPtr GetHandle()
        {
            return _table;
        }

        public int GetIndexType()
        {
            return BangDBNative.GetIndexType(_table);
        }

        public int CloseConnection(Connection conn)
        {
            IntPtr _conn = conn.GetHandle();
            int r = BangDBNative.CloseTableConnection(_table, _conn);
            BangDBNative.FreeHandle(ref _conn);
            return r;
        }
    }
}
