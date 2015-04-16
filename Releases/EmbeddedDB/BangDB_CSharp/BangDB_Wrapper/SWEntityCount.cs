using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class SWEntityCount
    {
        private IntPtr _swentity;

        public SWEntityCount(string name, int swTime, int swExpiry, int nEntity = 32)
        {
            _swentity = BangDBNative.CreateSWEntityCount(name, swTime, swExpiry, nEntity);
        }

        public int Init()
        {
            return BangDBNative.InitSWEntityCount(_swentity);
        }

        public int Add(string entityName, string s)
        {
            return BangDBNative.AddSWEntity(_swentity, entityName, s, s.Length);
        }

        public void AddCreate(string entityName, string s, BangDBWindowType swType, BangDBCountType countType)
        {
            BangDBNative.AddCreateSWEntity(_swentity, entityName, entityName.Length, s, s.Length, (int)swType, (int)countType);
        }

        public int Count(string entityName)
        {
            return BangDBNative.CountSWEntity(_swentity, entityName);
        }

        public int Count(string entityName, int span)
        {
            return BangDBNative.CountSpanEntity(_swentity, entityName, span);
        }

        public string ListCount_Json()
        {
            IntPtr list = IntPtr.Zero;
            BangDBNative.ListCountSWEntity(_swentity, out list);
            string str = Marshal.PtrToStringAnsi(list);
            BangDBNative.FreeHandle(ref list);
            return str;
        }

        public string ListCount_Str()
        {
            IntPtr list = IntPtr.Zero;
            BangDBNative.ListCount2SWEntity(_swentity, out list);
            string str = Marshal.PtrToStringAnsi(list);
            BangDBNative.FreeHandle(ref list);
            return str;
        }

        public void CreateEntity(string name, BangDBWindowType swType, BangDBCountType countType)
        {
            BangDBNative.CreateEntitySW(_swentity, name, name.Length, (int)swType, (int)countType);
        }

        public void RemoveEntity(string name)
        {
            BangDBNative.RemoveEntitySW(_swentity, name);
        }

        public bool ShouldExit()
        {
            return BangDBNative.ShouldExitSWEntity(_swentity) > 0 ? true : false;
        }

        public void ShutDown()
        {
            BangDBNative.ShutDownSWEntity(_swentity);
        }

        ~SWEntityCount()
        {
            BangDBNative.FreeHandle(ref _swentity);
            _swentity = IntPtr.Zero;
        }
    }
}
