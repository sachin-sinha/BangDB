using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace BangDB_CSharp
{
    public enum PersistType
    {
        InmemOnly,            //only RAM based, cache enabled (no overflow to disk, ideally overflow to other RAM)
        InmemPersist,         //disked backed, cache enabled (over flow to disk)
        PersistOnly,          //many procs one db file, cache disabled
        DefaultConfig,
    };

    public enum IndexType
    {
        Hash,           //depricated
        Exthash,
        Btree,
        Heap,           //not supported
        DefaultConfig,
    };

    public enum DBOpenType
    {
        Opencreate,
        Truncopen,
        Justopen,
    };

    public enum DBCloseType
    {
        Default,
        Conservative,
        Optimistic,
        CleanClose,
    };

    public enum InsertOptions
    {
        InsertUnique,		//if non-existing then insert else return
        UpdateExisting,	    //if existing then update else return
        InsertUpdate,		//insert if non-existing else update
        DeleteExisting,	    //delete if existing
    };

    public enum TransactionType
    {
        DBTransactionNone,
        DBOptimisticTransaction,
        DBPessimisticTransaction,
    };

    public enum BangDBState
    {
        DBClose,
        DBOpen,
    }

    public enum TableSizeHint
    {
        TinyTableSize,
        SmallTableSize,
        NormalTableSize,
        BigTableSize,
    }

    public enum ScanLimitBy
    {
        LimitResultSizeByte,
        LimitResultRow,
    }

    public enum ScanOperator
    {
        GT,
        GTE,
        LT,
        LTE,
    }

    public enum WALState
    {
        Disabled,
        Enabled,
        DefaultConfig,
    }

    public enum BangDBLogType
    {
        SharedLog,
        PrivateLog,
    }

    public enum AutoCommitState
    {
        Disabled,
        Enabled,
        DefaultConfig,
    }

    public enum BangDBTableType
    {
        NormalTable,
        WideTable,
        IndexTable,
        PrimitiveTableInt,
        PrimitiveTableLong,
        PrimitiveTableString,
    }

    public enum BangDBPrimitiveDataType
    {
        PrimitiveInt,
        PrimitiveLong,
        PrimitiveString,
    }

    //denotes whether analytical stuff or not
    public enum BangDBTableSubType
    {
        NonAnalyticalTable,
        SWTable,
        SWEntityCountTable,
        SWTopkTable,
    };

    public enum BangDBWindowType
    {
        NonSlidingWindow,
        SlidingWindowSpan,
        SlidingWindowUnit,
    }

    public enum BangDBCountType
    {
        UniqueCount,
        NonUniqueCount,
    }

    public enum BangDBKeySortMethod
    {
        Lexicograph = 1,
        QuasiLexicograph = 2,
    }

    public enum BangDBKeySortDirection
    {
        SortAscending = 3,
        SortDescending = 4,
    }

    public enum BangDBKeyType
    {
        NormalKey = 1,
        CompositeKey = 3,
        NormalKeyLong = 10,
    }

    public enum BangDBDataOpsFlag
    {
        FlagSetNone = 0,
        DataReadDone = 1,
        MoreDataToCome = 2,
        DataReadOverflow = 3,
        DataReadError = 4,
    }

    public class ScanFilter
    {
        public ScanFilterStruct sfs;

        public ScanFilter()
        {
            sfs.Reset();
        }
        public void Reset()
        {
            sfs.Reset();
        }
        public void Clone(ScanFilter sf)
        {
            sfs.Clone(sf.sfs);
        }
        public ScanOperator skeyOp
        {
            get { return sfs.skeyOp; }
            set { sfs.skeyOp = value; }
        }
        public ScanOperator ekeyOp
        {
            get { return sfs.ekeyOp; }
            set { sfs.ekeyOp = value; }
        }
        public ScanLimitBy limitBy
        {
            get { return sfs.limitBy; }
            set { sfs.limitBy = value; }
        }
        public int limit
        {
            get { return sfs.limit; }
            set { sfs.limit = value; }
        }
        public int skip_count
        {
            get { return sfs.skip_count; }
            set { sfs.skip_count = value; }
        }
    }

    [StructLayout(LayoutKind.Sequential, Pack=1)]
    public struct ScanFilterStruct
    {
        public ScanOperator skeyOp;
        public ScanOperator ekeyOp;
        public ScanLimitBy limitBy;
        public int limit;
        public int skip_count;

        public ScanFilterStruct(ScanOperator skop = ScanOperator.GTE, ScanOperator ekop = ScanOperator.LTE, ScanLimitBy _limitBy = ScanLimitBy.LimitResultSizeByte, int _limit = 0, int _skip_count = 0)
        {
            skeyOp = ScanOperator.GTE;
            ekeyOp = ScanOperator.LTE;
            limitBy = ScanLimitBy.LimitResultSizeByte;
            limit = 2 * 1024 * 1024;
            skip_count = 0;
        }

        public void Reset()
        {
            skeyOp = ScanOperator.GTE;
            ekeyOp = ScanOperator.LTE;
            limitBy = ScanLimitBy.LimitResultSizeByte;
            limit = 2*1024*1024;
            skip_count = 0;
        }

        public void Clone(ScanFilterStruct sf)
        {
            skeyOp = sf.skeyOp;
            ekeyOp = sf.ekeyOp;
            limitBy = sf.limitBy;
            limit = sf.limit;
            skip_count = sf.skip_count;
        }
    }
}
