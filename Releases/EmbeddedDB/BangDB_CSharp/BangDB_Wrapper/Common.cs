using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace BangDB_CSharp
{
    public static class Common
    {
        public static void LoadBangDB(string configPath)
        {
            if (configPath != null)
            {
                if (!System.IO.Directory.Exists(configPath))
                    throw new Exception("config path is not a valid path");
                BangDBNative.SetDllDirectory(configPath);
            }
            else
                throw new Exception("config path is null");
        }

        public static IntPtr MarshalToPointer(object data)
        {
            IntPtr buf = Marshal.AllocHGlobal(Marshal.SizeOf(data));
            Marshal.StructureToPtr(data, buf, false);
            return buf;
        }

        public static object MarshalToStruct(IntPtr buf, Type t)
        {
            return Marshal.PtrToStructure(buf, t);
        }

        public static void FreeStructPtr(IntPtr ptr)
        {
            Marshal.FreeHGlobal(ptr);
        }

        public static void BangDBLogger(string str)
        {
            BangDBNative.BangDB_Logger(str);
        }
        public static void BangDBPrintError(int errnum)
        {
            BangDBNative.Bangdb_print_error(errnum);
        }

        public static void BangDBPrintLastError()
        {
            BangDBNative.Bangdb_print_last_error();
        }

        public static string MakeComposite(string[] keys)
        {
            string ck = null;
            int nk = keys.Length;
            ck = keys[0];
            
            for (int i = 1; i < nk; i++)
            {
                ck += ':';
                ck += keys[i];
            }

            return ck;
        }

        public static string MakeComposite(string k1, string k2)
        {
            return k1 + ':' + k2;
        }

        public static string MakeComposite(long k1, long k2)
        {
            return k1.ToString() + ':' + k2.ToString();
        }

        public static string MakeComposite(byte[] k1, byte[] k2)
        {
            return k1.ToString() + ':' + k2.ToString();
        }

        public static string MakeComposite(string k1, long k2)
        {
            return k1 + ':' + k2.ToString();
        }

        public static string MakeComposite(long k1, string k2)
        {
            return k1.ToString() + ':' + k2;
        }

        public static long KeyComp(string s1, string s2, int sortid)
        {
            return BangDBNative.KeyComp(s1, s1.Length, s2, s2.Length, sortid);
        }

        public static ulong GetCurrentTimeMicroSec()
        {
            return BangDBNative.GetCurrentTimeMicroSec();
        }

        public static ulong GetCurrentTimeMilliSec()
        {
            return BangDBNative.GetCurrentTimeMilliSec();
        }

        public static ulong UniqueTimeStampMicroSec()
        {
            return BangDBNative.UniqueTimeStampMicroSec();
        }

        public static ulong UniqueTimeStampMilliSec()
        {
            return BangDBNative.UniqueTimeStampMilliSec();
        }

        public static ulong GetCurrentTime()
        {
            return BangDBNative.GetCurTime();
        }

        public static ulong GetUniqueTimeStamp()
        {
            return BangDBNative.UniqueTimeStamp();
        }

        public static unsafe int CompareBuffers(byte[] buffer1, int offset1, byte[] buffer2, int offset2, int count)
        {
            fixed (byte* b1 = buffer1, b2 = buffer2)
            {
                return BangDBNative.memcmp(b1 + offset1, b2 + offset2, count);
            }
        }
    }
}
