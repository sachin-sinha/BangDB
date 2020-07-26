using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public static class BangDBNative
    {
        private const string path = "bangdbwin.dll";

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool SetDllDirectory(string lpPathName);

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int memcmp(byte[] b1, byte[] b2, int count);

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern unsafe int memcmp(byte* b1, byte* b2, int count);

        //tableenv functions
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetTableEnv();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void ResetTableEnv(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_persist_type(IntPtr tenv, int persist_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_idx_type(IntPtr tenv, int BTREE_EXTHASH);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_table_type(IntPtr tenv, int _table_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_key_size_byte(IntPtr tenv, int key_size);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_log_size_mb(IntPtr tenv, int log_size_mb);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_table_size_hint(IntPtr tenv, int TINY_SMALL_NORMAL_BIG);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_log_state(IntPtr tenv, int is_log_on);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_log_type(IntPtr tenv, int log_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_autocommit_state(IntPtr tenv, int is_autocommit_on);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_sort_method(IntPtr tenv, int sort_method);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_sort_dirction(IntPtr tenv, int sort_direction);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_key_type(IntPtr tenv, int key_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_allow_duplicate(IntPtr tenv, int allowDuplicate);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_config_vars(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_persist_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_primitive_data_type(IntPtr tenv, int data_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Set_table_subtype(IntPtr tenv, int sub_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_idx_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_table_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_key_size_byte(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_log_size_mb(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_table_size_hint(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_log_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_log_state(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_autocommit_state(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_sort_method(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_sort_direction(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_key_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_primitive_data_type(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_table_subtype(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_sort_id(IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_allow_duplicate(IntPtr tenv);


        //database functions
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetDatabase([MarshalAs(UnmanagedType.LPStr)] string dbname, [MarshalAs(UnmanagedType.LPStr)] string configpath, int transaction_type, [MarshalAs(UnmanagedType.LPStr)] string dbpath, [MarshalAs(UnmanagedType.LPStr)] string logpath);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetTable(IntPtr db, [MarshalAs(UnmanagedType.LPStr)] string tblname, int flag, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetWideTable(IntPtr db, [MarshalAs(UnmanagedType.LPStr)] string tblname, int flag, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetPrimitiveTable(IntPtr db, [MarshalAs(UnmanagedType.LPStr)] string tblname, int primitiveDataType, int flag, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseTable(IntPtr db, [MarshalAs(UnmanagedType.LPStr)] string tblname, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseTableHandle(IntPtr db, IntPtr tbl, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseWideTableHandle(IntPtr db, IntPtr wtbl, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CloseDatabase(IntPtr db, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CleanUp(IntPtr db);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetNewTransaction();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Begin_Transaction(IntPtr db, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Commit_Transaction(IntPtr db, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Abort_Transaction(IntPtr db, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int IsTransactionActive(IntPtr txn);

        //table functions (for table and primitive)
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetConnection(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetPrimConnection(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int DumpData(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetTableName(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseThisTable(IntPtr tbl, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetTablePersistType(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetTableType(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetIndexType(IntPtr tbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseTableConnection(IntPtr tbl, IntPtr conn);

        //wide table method (for wide table)
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetWideConnection(IntPtr wtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int WideDumpData(IntPtr wtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern string GetWideTableName(IntPtr wtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseThisWideTable(IntPtr wtbl, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetWideIndexType(IntPtr wtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int AddIndex(IntPtr wtbl, string idxName, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int AddIndex_Str(IntPtr wtbl, string idxName, int idxSize, int allowDuplicates);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int AddIndex_Num(IntPtr wtbl, string idxName, int allowDuplicates);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int DropIndex(IntPtr wtbl, string idxName);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseAllWideConnections(IntPtr wtbl);


        //connection functions
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get(IntPtr conn, string key, int klen, out IntPtr val, out int vlen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_Tran(IntPtr conn, string key, int klen, out IntPtr val, out int vlen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get(IntPtr conn, byte[] key, int klen, out IntPtr val, out int vlen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_Tran(IntPtr conn, byte[] key, int klen, out IntPtr val, out int vlen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvanced(IntPtr conn, string key, int klen, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvancedTran(IntPtr conn, string key, int klen, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvanced(IntPtr conn, byte[] key, int klen, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvancedTran(IntPtr conn, byte[] key, int klen, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvanced(IntPtr conn, long key, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetAdvancedTran(IntPtr conn, long key, ref IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_Long_Str(IntPtr conn, long key, ref IntPtr val, ref int vallen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Put(IntPtr conn, string key, int klen, string val, int vlen, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Tran(IntPtr conn, string key, int klen, string val, int vlen, int flag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put(IntPtr conn, byte[] key, int klen, byte[] val, int vlen, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Tran(IntPtr conn, byte[] key, int klen, byte[] val, int vlen, int flag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put(IntPtr conn, byte[] key, int klen, string val, int vlen, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Tran(IntPtr conn, byte[] key, int klen, string val, int vlen, int flag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put(IntPtr conn, string key, int klen, byte[] val, int vlen, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Tran(IntPtr conn, string key, int klen, byte[] val, int vlen, int flag, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutAdvanced(IntPtr conn, string key, int keylen, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutAdvanced(IntPtr conn, byte[] key, int keylen, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutAdvanced_Tran(IntPtr conn, string key, int keylen, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutAdvanced_Tran(IntPtr conn, byte[] key, int keylen, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutByte_Long(IntPtr conn, long key, string val, int vallen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutByte_Long_Tran(IntPtr conn, long key, string val, int vallen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutByte_Long_Tran(IntPtr conn, long key, byte[] val, int vallen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutByte_Long(IntPtr conn, long key, byte[] val, int vallen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutByte_Long(IntPtr conn, long key, byte[] val, int vallen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del(IntPtr conn, string key, int klen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_Tran(IntPtr conn, string key, int klen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_Long(IntPtr conn, long key);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_Long_Tran(IntPtr conn, long key, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del(IntPtr conn, byte[] key, int klen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_Tran(IntPtr conn, byte[] key, int klen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Tran(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan(IntPtr conn, byte[] skey, int klen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Tran(IntPtr conn, byte[] skey, int klen, byte[] ekey, int eklen, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Long(IntPtr conn, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Long_Tran(IntPtr conn, long skey, long ekey, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_Tran(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV(IntPtr conn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_Tran(IntPtr conn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_Long(IntPtr conn, long skey, long ekey, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_Long_Tran(IntPtr conn, long skey, long ekey, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Count(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Count(IntPtr conn, byte[] skey, int klen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Count_LONG(IntPtr conn, long skey, long ekey, IntPtr sf);
       
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPersistType(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetIdxType(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseConnection(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void SetAutoCommit(IntPtr conn, int flag);


        //prim connection method
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPrim(IntPtr conn, long key, ref long val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPrimInt(IntPtr conn, int key, ref int val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPrim_Str(IntPtr conn,  string key, int keylen, ref long val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPrim_Byte(IntPtr conn, byte[] key, int keylen, ref long val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutPrim(IntPtr conn, long key, long val, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutPrim_Str(IntPtr conn,  string key, int klen, long val, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutPrim_Byte(IntPtr conn, byte[] key, int klen, long val, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long DelPrim_Str(IntPtr conn,  string key, int keylen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long DelPrim_Byte(IntPtr conn, byte[] key, int keylen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long DelPrim_Long(IntPtr conn, long key);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanPrim_Long(IntPtr conn, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanPrim_Str(IntPtr conn, string skey, int skeylen,  string ekey, int ekeylen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanPrim_Byte(IntPtr conn, byte[] skey, int skeylen, byte[] ekey, int ekeylen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountPrim_Long(IntPtr conn, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountPrim_Str(IntPtr conn, string skey, int skeylen,  string ekey, int ekeylen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountPrim_Byte(IntPtr conn, byte[] skey, int skeylen, byte[] ekey, int ekeylen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountPrim(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void SetAutoCommitPrim(IntPtr conn, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int	 GetPrimPersistType(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int	 GetPrimIdxType(IntPtr conn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int	 ClosePrimConnection(IntPtr conn);

        //wide connection method
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetW(IntPtr wconn, string key, int klen, ref IntPtr oval,  ref int ovlen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_LongW(IntPtr wconn, long key, ref IntPtr val, ref int vallen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetW(IntPtr wconn, byte[] key, int klen, ref IntPtr oval, ref int ovlen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_TranW(IntPtr wconn, string key, int klen, ref IntPtr oval, ref int ovlen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Get_TranW(IntPtr wconn, byte[] key, int klen, ref IntPtr oval, ref int ovlen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutW(IntPtr wconn, string key, int klen, string val, int vlen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutW(IntPtr wconn, string key, int klen, byte[] val, int vlen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutW(IntPtr wconn, byte[] key, int klen, string val, int vlen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutW(IntPtr wconn, byte[] key, int klen, byte[] val, int vlen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_LongW(IntPtr wconn, long key, string val, int vallen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Long_TranW(IntPtr wconn, long key, string val, int vallen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_LongW(IntPtr wconn, long key, byte[] val, int vallen, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Long_TranW(IntPtr wconn, long key, byte[] val, int vallen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_TranW(IntPtr wconn, string key, int klen, string val, int vlen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_TranW(IntPtr wconn, string key, int klen, byte[] val, int vlen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_TranW(IntPtr wconn, byte[] key, int klen, string val, int vlen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_TranW(IntPtr wconn, byte[] key, int klen, byte[] val, int vlen, int insertOption, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long DelW(IntPtr wconn, string key, int klen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long DelW(IntPtr wconn, byte[] key, int klen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_longW(IntPtr wconn, long key);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_TranW(IntPtr wconn, string key, int klen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Del_TranW(IntPtr wconn, byte[] key, int klen, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanW(IntPtr wconn, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanW(IntPtr wconn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_TranW(IntPtr wconn, string skey, int sklen, string ekey, int eklen, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_TranW(IntPtr wconn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_LongW(IntPtr wconn, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountW(IntPtr wconn, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountW(IntPtr wconn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Count_LongW(IntPtr wconn, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Doc(IntPtr wconn, string json_str);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Doc_Long(IntPtr wconn, long key, string json_str, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long Put_Doc_Str(IntPtr wconn, string key, string json_str, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdx(IntPtr wconn, string key, int klen, string val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdx(IntPtr wconn, byte[] key, int klen, string val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdx(IntPtr wconn, string key, int klen, byte[] val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdx(IntPtr wconn, byte[] key, int klen, byte[] val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdxLong(IntPtr wconn, long key, string val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long PutWIdxLong(IntPtr wconn, long key, byte[] val, int vlen, string idxName, string idxVal, int idxLen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanWIdx(IntPtr wconn, string idxName, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanWIdx(IntPtr wconn, string idxName, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx(IntPtr wconn, string idxName, string skey, int sklen, string ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx(IntPtr wconn, string idxName, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx_Long(IntPtr wconn, string idxName, long skey, long ekey, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx_Long_DV(IntPtr wconn, string idxName, long skey, long ekey, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx_DV(IntPtr wconn, string idxName, string skey, int sklen, string ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Doc_Idx_DV(IntPtr wconn, string idxName, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanWIdx_DV(IntPtr wconn, string idxName, string skey, int sklen, string ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanWIdx_DV(IntPtr wconn, string idxName, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void SetAutoCommitW(IntPtr wconn, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetPersistTypeW(IntPtr wconn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetIdxTypeW(IntPtr wconn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CloseConnectionW(IntPtr wconn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long CountAllW(IntPtr wconn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_Long_TranW(IntPtr wconn, long skey, long ekey, IntPtr txn, IntPtr sf);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long	 Del_long_TranW(IntPtr wconn, long key, IntPtr txn);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DVW(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_TranW(IntPtr conn, string skey, int sklen, string ekey, int eklen, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DVW(IntPtr conn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_TranW(IntPtr conn, byte[] skey, int sklen, byte[] ekey, int eklen, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_LongW(IntPtr conn, long skey, long ekey, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr Scan_DV_Long_TranW(IntPtr conn, long skey, long ekey, IntPtr txn, IntPtr sf, IntPtr dat_buf, int dat_buf_len, ref int dat_len, int dat_offt, ref int errflag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetMainConn(IntPtr wconn);


        //resultset method for scan
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetNextKey(IntPtr rs, out IntPtr key, out int len);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long GetNextKeyLong(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetNextKeyStr(IntPtr rs, out string key);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetNextVal(IntPtr rx, out IntPtr val, out int len);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long GetNextValLong(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetNextValStr(IntPtr rs, out string val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Add_Doc(IntPtr rs1, IntPtr rs2, string OrderBy);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Add(IntPtr rs1, IntPtr rs2);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Append(IntPtr rs1, IntPtr rs2);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Intersect(IntPtr rs1, IntPtr rs2);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int HasNext(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void MoveNext(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int Size(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int RSCount(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int RSDataSize(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Begin(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void BeginReverse(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Clear(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void LastEvaluatedKey(IntPtr rs, out IntPtr key, out int len);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long LastEvaluatedKeyLong(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int MoreDataToCome(IntPtr rs);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void SearchValue(IntPtr rs, byte[] key, int keylen, out IntPtr val, out int vallen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void SearchValue(IntPtr rs, string key, int keylen, out IntPtr val, out int vallen);

        //topk
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CreateTopk(string topkName, int swSizeSec, int k, int desc, string uniqueBy);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Put_topk(IntPtr tk, long score, string data, int datalen, string uniqueParam);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetTopk(IntPtr tk, int k);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void	GetTopkJson(IntPtr tk, out IntPtr jstr, int k);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void	CloseTopk(IntPtr tk);

        //swTable
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CreateSWTable(IntPtr db, string tableName, IntPtr tenv, int ttlsec, int archive);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void AddIndexSWTable(IntPtr swtbl, string idxName, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int InitSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetConnectionSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetActiveConnectionSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetPassiveConnectionSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int	 PutSWTable(IntPtr swtbl, string str, int len, int insertOption);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int	 PutSWTableIdx(IntPtr swtbl, string str, int len, string idx, string idxkey, int idxkeylen);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanSWTable(IntPtr swtbl, int period);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanLagSWTable(IntPtr swtbl, int period, int lag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanFullSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr ScanRemainingSWTable(IntPtr swtbl, long from_time, int lag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int GetTTLSWTable(IntPtr swtbl);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int NeedPassiveSWTable(IntPtr swtbl, int windowsec);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CloseSWTable(IntPtr swtbl);

        //swCount & swSlotCount
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CreateSWCount(int swTime, int swExpiry, int countType, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void AddSWCount(IntPtr swcount, string s, int len, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ListSWCount(IntPtr swcount, int span, ref int[] count_list, ref int list_size, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CountSWCount(IntPtr swcount, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CountSpanSWCount(IntPtr swcount, int span, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void FoldSlotsSWCount(IntPtr swcount, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void ResetSWCount(IntPtr swcount, int swtype);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CloseSWCount(IntPtr swcount, int swtype);

        //swEntityCount
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CreateSWEntityCount(string entityName, int swTime, int swExpiry, int nEntity);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int  InitSWEntityCount(IntPtr swentity);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int  AddSWEntity(IntPtr swentity, string entityName, string s, int len);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void AddCreateSWEntity(IntPtr swentoty, string entityName, int entityNameLen, string s, int len, int swType, int countType);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int  CountSWEntity(IntPtr swentity, string entityName);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int  CountSpanEntity(IntPtr swentity, string entityName, int span);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void ListCountSWEntity(IntPtr swentity, out IntPtr list);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void ListCount2SWEntity(IntPtr swentity, out IntPtr list);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CreateEntitySW(IntPtr swentity, string name, int namelen, int swType, int countType);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void  RemoveEntitySW(IntPtr swentity, string name);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ShouldExitSWEntity(IntPtr swentity);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void  ShutDownSWEntity(IntPtr swentity);

        //swTableUnit
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CreateSWTableUnit(IntPtr db, string tableName, IntPtr tenv, int ttlsec);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void AddIndexSWTableUnit(IntPtr _swtu, string idxName, IntPtr tenv);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int CreateTableSWTableUnit(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetConnectionSWTanleUnit(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void CloseSWTableUnit(IntPtr _swtu, int flag);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern  ulong GetCreateTimeStamp(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void StartSWTableUnit(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int HasExpiredSWTableUnit(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ShouldSwitchSWTableUnit(IntPtr _swtu);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int IsStartedSWTableUnit(IntPtr _swtu);

        //timestamp
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong GetCurrentTimeMicroSec();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong GetCurrentTimeMilliSec();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong UniqueTimeStampMicroSec();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong UniqueTimeStampMilliSec();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong GetCurTime();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong SubTime(long nsec);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong AddTime(long nsec);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong UniqueTimeStamp();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong ConvertTimeUnit(long nsec);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern ulong GetLagTime(ulong from_time);

        //misc
        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern long KeyComp(string k1, int l1, string k2, int l2, int sortid);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Bangdb_print_error(int errnum);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void Bangdb_print_last_error();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void FreeBytes(IntPtr val);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void FreeHandle(ref IntPtr h);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern int TestPerf(int a, int b);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void BangDB_Logger(string str);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void BangDB_Logger_Init( string dbpath,   string name, int log_mem_sz_mb, int log_type);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [SuppressUnmanagedCodeSecurity]
        public static extern void BangDB_Logger_Close();
    }
}
