using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace bangdb_driver
{
    class Program
    {
        public static void testPutGet(int N, int nT, string path)
        {
            bangdb_test.PutGetTest(N, nT, path);
        }

        public static void testPut(int N, int nT, string path)
        {
            bangdb_test.PutTest(N, nT, path);
        }

        public static void testGet(int N, int nT, string path)
        {
            bangdb_test.GetTest(N, nT, path);
        }

        public static void sanitystr(string path)
        {
            bangdb_test.TestSanityAllStr(path);
        }
        public static void sanitybyte(string path)
        {
            bangdb_test.TestSanityAllByte(path);
        }

        static void Main(string[] args)
        {
            //define the path where the app should locate dlls
            string path = ".";

            if (args.Length == 0)
            {
                Console.WriteLine("Uasge test-bangdb-csharp <num_items> <num_threads> <optype[all/put/get]>");
                Console.WriteLine("for ex; to put and get 500,000 itmes using 4 threads use following");
                Console.WriteLine("test-bangdb-csharp 500000 4 all");
                Console.WriteLine("running sanity test now");
                sanitystr(path);
                return;
            }

            if (args.Length == 3)
            {
                int Nitems = Convert.ToInt32(args[0]);
                int nt = Convert.ToInt32(args[1]);
                if(args[2].Equals("all"))
                    testPutGet(Nitems, nt, path);
                if (args[2].Equals("put"))
                    testPut(Nitems, nt, path);
                if (args[2].Equals("get"))
                    testGet(Nitems, nt, path);
                return;
            }
        }
    }
}
