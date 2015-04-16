using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class TableEnv
    {
        private IntPtr _tblenv;

        public TableEnv()
        {
            _tblenv = BangDBNative.GetTableEnv();
        }

        public PersistType persistType
        {
            get { return (PersistType)BangDBNative.Get_persist_type(_tblenv); }
            set { BangDBNative.Set_persist_type(_tblenv, (int)value); }
        }

        public IndexType indexType
        {
            get { return (IndexType)BangDBNative.Get_idx_type(_tblenv); }
            set { BangDBNative.Set_idx_type(_tblenv, (int)value); }
        }

        public BangDBTableType tableType
        {
            get { return (BangDBTableType)BangDBNative.Get_table_type(_tblenv); }
            set { BangDBNative.Set_table_type(_tblenv, (int)value); }
        }

        public int keySize
        {
            get { return BangDBNative.Get_key_size_byte(_tblenv); }
            set { BangDBNative.Set_key_size_byte(_tblenv, value); }
        }

        public int logSizeMB
        {
            get { return BangDBNative.Get_log_size_mb(_tblenv); }
            set { BangDBNative.Set_log_size_mb(_tblenv, value); }
        }

        public TableSizeHint tableSizeHint
        {
            get { return (TableSizeHint)BangDBNative.Get_table_size_hint(_tblenv); }
            set { BangDBNative.Set_table_size_hint(_tblenv, (int)value); }
        }

        public WALState walState
        {
            get { return (WALState)BangDBNative.Get_log_state(_tblenv); }
            set { BangDBNative.Set_log_state(_tblenv, (int)value); }
        }

        public BangDBLogType logType
        {
            get { return (BangDBLogType)BangDBNative.Get_log_type(_tblenv); }
            set { BangDBNative.Set_log_type(_tblenv, (int)value); }
        }

        public AutoCommitState autoCommitState
        {
            get { return (AutoCommitState)BangDBNative.Get_autocommit_state(_tblenv); }
            set { BangDBNative.Set_autocommit_state(_tblenv, (int)value); }
        }

        public BangDBKeySortMethod sortMethod
        {
            get { return (BangDBKeySortMethod)BangDBNative.Get_sort_method(_tblenv); }
            set { BangDBNative.Set_sort_method(_tblenv, (int)value); }
        }

        public BangDBKeySortDirection sortDirection
        {
            get { return (BangDBKeySortDirection)BangDBNative.Get_sort_direction(_tblenv); }
            set { BangDBNative.Set_sort_dirction(_tblenv, (int)value); }
        }

        public BangDBKeyType keyType
        {
            get { return (BangDBKeyType)BangDBNative.Get_key_type(_tblenv); }
            set { BangDBNative.Set_key_type(_tblenv, (int)value); }
        }

        public BangDBPrimitiveDataType primitiveDataType
        {
            get { return (BangDBPrimitiveDataType)BangDBNative.Get_primitive_data_type(_tblenv); }
            set { BangDBNative.Set_primitive_data_type(_tblenv, (int)value); }
        }

        public BangDBTableSubType tableSubType
        {
            get { return (BangDBTableSubType)BangDBNative.Get_table_subtype(_tblenv); }
            set { BangDBNative.Set_table_subtype(_tblenv, (int)value); }
        }

        public bool allowDuplicate
        {
            get { return BangDBNative.Get_allow_duplicate(_tblenv) == 0 ? false : true; }
            set { BangDBNative.Set_allow_duplicate(_tblenv, value ? 1 : 0); }
        }

        public void SetConfigVars()
        {
            BangDBNative.Set_config_vars(_tblenv);
        }

        public void Reset()
        {
            BangDBNative.ResetTableEnv(_tblenv);
        }

        public IntPtr GetHandle()
        {
            return _tblenv;
        }

        ~TableEnv()
        {
            BangDBNative.FreeHandle(ref _tblenv);
            _tblenv = IntPtr.Zero;
        }
    }
}
