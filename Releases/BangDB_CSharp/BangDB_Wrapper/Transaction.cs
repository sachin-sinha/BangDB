using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BangDB_CSharp
{
    public class Transaction : IDisposable
    {
        private IntPtr _txn;

        public Transaction()
        {
            _txn = BangDBNative.GetNewTransaction();
        }

        public IntPtr GetTranPtr()
        {
            return _txn;
        }

        public bool IsActive()
        {
            return BangDBNative.IsTransactionActive(_txn) > 0 ? true : false;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                BangDBNative.FreeHandle(ref _txn);
                _txn = IntPtr.Zero;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~Transaction()
        {
            Dispose(false);
        }
    }
}
