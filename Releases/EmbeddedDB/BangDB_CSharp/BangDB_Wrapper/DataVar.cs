using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class DataVar
    {
        private byte[] buf;
        private GCHandle _handle;
        private IntPtr pBuffer;
        private int data_buf_len;
        private int data_len;
        private int data_offt;
        private BangDBDataOpsFlag flag;

        public DataVar(int sizeInBytes)
        {
            data_buf_len = sizeInBytes;
            buf = new byte[sizeInBytes];
            _handle = GCHandle.Alloc(buf, GCHandleType.Pinned);
            //pBuffer = Marshal.UnsafeAddrOfPinnedArrayElement(buf, 0);
            pBuffer = _handle.AddrOfPinnedObject();
            data_len = 0;
            data_offt = 0;
            flag = BangDBDataOpsFlag.FlagSetNone;
        }
        
        public void Copy(string _buf, int len)
        {
            Buffer.BlockCopy(Encoding.UTF8.GetBytes(_buf), 0, buf, 0, len);
            data_len = len;
        }

        public void Copy(byte[] _buf, int len)
        {
            Buffer.BlockCopy(_buf, 0, buf, 0, _buf.Length);
            data_len = len;
        }

        public string Read()
        {
            return System.Text.Encoding.UTF8.GetString(buf, 0, data_len);
        }

        public string Read(int len)
        {
            return System.Text.Encoding.UTF8.GetString(buf, 0, len);
        }

        public byte[] ReadByte()
        {
            return buf;
        }

        public byte[] ReadByte(int len)
        {
            return buf;
        }

        public bool BufferEquals(string _buf, int len)
        {
            return BangDBNative.memcmp(Encoding.UTF8.GetBytes(_buf), buf, len) == 0 ? true : false;
        }

        public bool BufferEquals(byte[] _buf, int len)
        {
            return BangDBNative.memcmp(_buf, buf, len) == 0 ? true : false;
        }

        public bool Equals(string _buf, int len)
        {
            return BangDBNative.memcmp(Encoding.UTF8.GetBytes(_buf), buf, len) == 0 ? true : false;
        }

        public bool Equals(byte[] _buf, int len)
        {
            return BangDBNative.memcmp(_buf, buf, len) == 0 ? true : false;
        }

        public bool Equals(byte[] buffer1, int offset1, byte[] buffer2, int offset2, int count)
        {
            return Common.CompareBuffers(buffer1, offset1, buffer2, offset2, count) == 0 ? true : false;
        }

        public byte[] buffer
        {
            get { return buf; }
            set { Buffer.BlockCopy(value, 0, buf, 0, value.Length); }
        }

        public int bufferLength
        {
            get { return data_buf_len; }
        }

        public int dataLength
        {
            get { return data_len; }
            set { data_len = value; }
        }

        public int dataOffset
        {
            get { return data_offt; }
            set { data_offt = value; }
        }

        public BangDBDataOpsFlag opsFlag
        {
            get { return flag; }
            set { flag = value; }
        }

        public void Reset()
        {
            data_len = 0;
            data_offt = 0;
            flag = BangDBDataOpsFlag.FlagSetNone;
        }

        public IntPtr bufferPointer
        {
            get { return pBuffer; }
            set { pBuffer = value; }
        }

        ~DataVar()
        {
            _handle.Free();
        }
    }
}
