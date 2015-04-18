/*
 * bheader.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb library
 *
 *  Copyright (C) 2015 IQLECT All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BHEADER_H_
#define BHEADER_H_
#include "basehdr.h"

namespace bangdb
{

#ifdef BUF_DIRECT_WRITE
#undef BUF_DIRECT_WRITE
#endif

#ifdef COMPUTE_SPLIT_TIME
#undef COMPUTE_SPLIT_TIME
#endif

#define MAX_FILES 				3
#define NUM_PAGE_PER_QUEUE 		3

//typical sizes of structures
#define HDR_SIZE 				sizeof(bheader)
#define MEMBUF_SIZE 			sizeof(membuf)
#define BPOOLST_SIZE 			sizeof(bpoolstat)
#define FILEMETA_SIZE			sizeof(filemeta)


//status of a bheader, these are mutually exclusive, hence can be just assigned
#define 	SET_BUF_NEW 					0
#define 	SET_BUF_CLEAN 					1
#define 	SET_BUF_UPTODATE	 			2
#define 	SET_BUF_DIRTY 					3
#define 	SET_BUF_NOLOCK					4
#define 	SET_BUF_READLOCK 				5
#define 	SET_BUF_WRITELOCK 				6
#define 	SET_BUF_IOSCHEDULE				7
#define 	SET_BUF_NOIOSCHEDULE			8
#define 	SET_BUF_INVALID					9

#define 	set_buf_state(x, state)			((x) = ((x&0) | SET_BUF_##state))
#define 	check_buf_state(x, state)		(((x) == SET_BUF_##state) ? 1 : 0)

//order is important as i have maintained the order of the array as well for _base_buffer, _hash_queue and _freelist
//0 - idx, 1 - dat, 2 - dir(for ehash only)
enum ftype
{
	F_IDX,
	F_DAT,
	F_DIR,
	FL_H,
	F_INV,		//the first one is always invalid
};

enum buf_cache_bg_state
{
	FLUSH_DIRTY_PAGES,
	RECLAIM_FREE_PAGES,
	FLUSH_DIRTY_PAGES_AGGRESSIVE,
	RECLAIM_FREE_PAGES_AGGRESSIVE,
	FLUSH_DIRTY_PAGES_INPROGRESS,
	RECLAIM_FREE_PAGES_INPROGRESS,
	FLUSH_DIRTY_PAGES_IDLE,
	RECLAIM_FREE_PAGES_IDLE,
	EXIT_FLUSHER,
	EXIT_RECLAIMER,
	EXITED_FLUSHER,
	EXITED_RECLAIMER,
	EXIT_READER,
	PC_READ_IN_PROGRESS,
	PC_READ_NOT_IN_PROGRESS,
	EMERGENCY_HANDLING_INPROGRESS,
	EMERGENCY_HANDLING_NOT_INPROGRESS,
};

struct bheader
{
	SHORT_T state;
	SHORT_T lock_type;
	SHORT_T io_schedule;
	SHORT_T type;
	int blocknum;
	atomic_t ucount;
	char *data;
	bheader *next_hdr;
	bheader *prev_hdr;
	bheader *next_lru;
	bheader *prev_lru;
	bheader *next_dirty;
	bheader *prev_dirty;
	bheader *next_read;
	bheader *prev_read;
	pthread_rwlock_t bhlock;

	bheader()
	{
		//init(SET_BUF_CLEAN, -1, NULL, F_INV);
		setbufstate(SET_BUF_CLEAN);
		set_buf_state(lock_type, NOLOCK);
		set_buf_state(io_schedule, NOIOSCHEDULE);
		type = F_INV;
		ucount.counter = 0;
		blocknum = -1;
		data = NULL;
		//Pthread_rwlock_init_private(&bhlock);
		//bhlock = PTHREAD_RWLOCK_INITIALIZER;

		next_hdr = prev_hdr = next_lru = prev_lru = next_dirty = prev_dirty = next_read = prev_read = NULL;
	}

	void setbufstate(SHORT_T bhstate)
	{
		switch(bhstate)
		{
			case SET_BUF_NEW:
				set_buf_state(state, NEW);
				break;
			case SET_BUF_CLEAN:
				set_buf_state(state, CLEAN);
				break;
			case SET_BUF_UPTODATE:
				set_buf_state(state, UPTODATE);
				break;
			case SET_BUF_DIRTY:
				set_buf_state(state, DIRTY);
				break;
			case SET_BUF_INVALID:
				set_buf_state(state, INVALID);
				break;
		}
	}

	void init(SHORT_T bhstate, int blknum, char *datbuf, SHORT_T tp)
	{
		setbufstate(bhstate);
		set_buf_state(lock_type, NOLOCK);
		set_buf_state(io_schedule, NOIOSCHEDULE);
		type = tp;
		ucount.counter = 0;
		blocknum = blknum;
		data = datbuf;
		Pthread_rwlock_init_private(&bhlock);
		//bhlock = PTHREAD_RWLOCK_INITIALIZER;

		next_hdr = prev_hdr = next_lru = prev_lru = next_dirty = prev_dirty = next_read = prev_read = NULL;
	}

	void destry_lock()
	{
		Pthread_rwlock_destroy(&bhlock);
	}

	~bheader()
	{
		//Pthread_rwlock_destroy(&bhlock);
	}
};

//to gather the bpool stats
struct bpoolstat
{
	BUFFER_T idxbufsize;
	BUFFER_T datbufsize;
	BUFFER_T dirbufsize;

	BUFFER_T hdrbufsize;
	BUFFER_T totbufsize;

	LCOUNT_T idxcachehit;
	LCOUNT_T idxcachemiss;
	LCOUNT_T idxnumread;
	LCOUNT_T idxnumwrite;

	LCOUNT_T datcachehit;
	LCOUNT_T datcachemiss;
	LCOUNT_T datnumread;
	LCOUNT_T datnumwrite;

	LCOUNT_T dircachehit;
	LCOUNT_T dircachemiss;
	LCOUNT_T dirnumread;
	LCOUNT_T dirnumwrite;

	pthread_mutex_t statlock;

	void init(BUFFER_T idxbsz, BUFFER_T datbsz, BUFFER_T dirbsz, BUFFER_T hdrbsz)
	{
		idxbufsize = idxbsz;
		datbufsize = datbsz;
		dirbufsize = dirbsz;
		hdrbufsize = hdrbsz;
		totbufsize = idxbsz+datbsz+dirbsz+hdrbsz;

		Pthread_mutex_init_private(&statlock);
	}
};

struct filemeta
{
private:
	atomic_FILEOFF_T endoffset;
	FILEOFF_T curoffset;
	BLOCKNUM_T endblock;

public:
	void init()
	{
		atomic_FILEOFF_T_set(&endoffset, 0);
		curoffset = 0;
		endblock = 0;
	}

	void setendoffset(FILEOFF_T eofft)
	{
		atomic_FILEOFF_T_set(&endoffset, eofft);
	}

	FILEOFF_T getendoffset()
	{
		return atomic_FILEOFF_T_read(&endoffset);
	}

	FILEOFF_T seekend(DATLEN_T len)
	{
		return atomic_FILEOFF_T_get_add(&endoffset, len);
	}
};

struct membuf
{
	UINT_T totalrec;
	UINT_T recsize;
	char *baseaddr;
	char *curraddr;
	char *endaddr;

	void init(char *baddr, int nrec, int rsize)
	{
		totalrec = 0;
		recsize = rsize;
		baseaddr = curraddr = baddr;
		endaddr = baseaddr + (nrec*rsize);
	}

	//caller should check for NULL
	char* getslot(UINT_T i)
	{
		if(i>totalrec)
			return NULL;
		return (baseaddr + (i*recsize));
	}

	int setcurrent(UINT_T i)
	{
		curraddr = baseaddr + i*recsize;
		totalrec = i;

		if(curraddr > endaddr)
		{
			err_ret("error in membuf set current function");
			return -1;
		}
		return 0;
	}

	//caller should check for NULL
	char* allocslot()
	{
		totalrec++;
		curraddr += recsize;
		//this check might not be required as we do init in at the startup time and also take care of boundaries, but may come handy for debug purpose
		//put it inside DEBUG macro
		if(curraddr > endaddr)
		{
			curraddr -= recsize;
			return NULL;
		}
		return (curraddr - recsize);
	}
};
}
#endif /* BHEADER_H_ */
