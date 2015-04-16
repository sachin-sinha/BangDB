using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class Database
    {
        private IntPtr _database;
        private bool _dbState = false;
        private string _databaseName;
        private string _configpath;

        public Database(string dbName, string configpath, TransactionType transaction_type=TransactionType.DBTransactionNone, string dbpath = null, string logpath = null)
        {
            _databaseName = dbName;
            if (configpath != null)
            {
                if (!System.IO.Directory.Exists(configpath))
                    throw new Exception("config path is not a valid path");
                _configpath = configpath;
                BangDBNative.SetDllDirectory(configpath);
            }
            if (dbpath != null)
            {
                if(!System.IO.Directory.Exists(dbpath))
                    throw new Exception("db dir path is not a valid path");
            }
            _database = BangDBNative.GetDatabase(dbName, configpath, (int)transaction_type, dbpath, logpath);
            _dbState = true;
        }

        public Table GetTable(string tableName, DBOpenType flag = DBOpenType.Opencreate, TableEnv tblEnv = null)
        {
            IntPtr _tblenv = tblEnv == null ? IntPtr.Zero : tblEnv.GetHandle();
            IntPtr _tbl = BangDBNative.GetTable(_database, tableName, (int)flag, _tblenv);
            return (_tbl != IntPtr.Zero) ? new Table(tableName, _tbl) : null;
        }

        public WideTable GetWideTable(string tableName, DBOpenType flag = DBOpenType.Opencreate, TableEnv tblEnv = null)
        {
            IntPtr _tblenv = tblEnv == null ? IntPtr.Zero : tblEnv.GetHandle();
            IntPtr _tbl = BangDBNative.GetWideTable(_database, tableName, (int)flag, _tblenv);
            return (_tbl != IntPtr.Zero) ? new WideTable(tableName, _tbl) : null;
        }

        public Table GetPrimitiveTable(string tableName, BangDBPrimitiveDataType dataType = BangDBPrimitiveDataType.PrimitiveLong, DBOpenType flag = DBOpenType.Opencreate, TableEnv tblEnv = null)
        {
            IntPtr _tblenv = tblEnv == null ? IntPtr.Zero : tblEnv.GetHandle();
            IntPtr _tbl = BangDBNative.GetPrimitiveTable(_database, tableName, (int)dataType, (int)flag, _tblenv);
            return (_tbl != IntPtr.Zero) ? new Table(tableName, _tbl) : null;
        }

        public int CloseTable(string tableName, DBCloseType flag = DBCloseType.Default)
        {
            int retval = BangDBNative.CloseTable(_database, tableName, (int)flag);
            return retval;
        }

        public int CloseTable(Table tbl, DBCloseType flag = DBCloseType.Default)
        {
            IntPtr _tblhandle = tbl.GetHandle();
            int retval = BangDBNative.CloseTableHandle(_database, _tblhandle, (int)flag);
            _tblhandle = IntPtr.Zero;
            return retval;
        }

        public int CloseTable(WideTable wtbl, DBCloseType flag = DBCloseType.Default)
        {
            IntPtr _tblhandle = wtbl.GetHandle();
            int retval = BangDBNative.CloseWideTableHandle(_database, _tblhandle, (int)flag);
            _tblhandle = IntPtr.Zero;
            return retval;
        }

        public void CloseDatabase(DBCloseType flag = DBCloseType.Default)
        {
            if(_dbState)
                BangDBNative.CloseDatabase(_database, (int)flag);
            _dbState = false;
            _database = IntPtr.Zero;
        }

        public void CleanUp()
        {
            BangDBNative.CleanUp(_database);
        }

        private int TestPiPerf(int a, int b)
        {
            return BangDBNative.TestPerf(a, b);
        }

        public void BeginTransaction(Transaction txn)
        {
            BangDBNative.Begin_Transaction(_database, txn.GetTranPtr());
        }

        public long CommitTransaction(Transaction txn)
        {
            return BangDBNative.Commit_Transaction(_database, txn.GetTranPtr());
        }

        public void AbortTransaction(Transaction txn)
        {
            BangDBNative.Abort_Transaction(_database, txn.GetTranPtr());
        }

        public IntPtr GetHandle()
        {
            return _database;
        }
    }
}
