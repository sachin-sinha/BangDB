/*
 * iqbpool.h
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

#ifndef IQBPOOL_H_
#define IQBPOOL_H_

#include "bangdb.h"
#include "iqlog.h"

namespace bangdb
{

class iqlog;

class iqbpool {
public:

	virtual int init(bool fastwarm = false, bool only_idx = false) = 0;

	virtual bheader* creadpage(SHORT_T ft, FILEOFF_T offt, SHORT_T whence, char **buf, DATLEN_T len, bool tocopy, bool rwlock) = 0;

	virtual bheader* cwritepage(SHORT_T ft, FILEOFF_T *offt, SHORT_T whence, char **buf, DATLEN_T len, bool tocopy, bool issync) = 0;

	virtual bheader** creaddata(SHORT_T ft, FILEOFF_T offt, SHORT_T whence, char *buf, DATLEN_T len, BLOCKNUM_T *numhdr, bool rwlock) = 0;

	virtual bheader** cwritedata(SHORT_T ft, FILEOFF_T *offt, SHORT_T whence, char *buf, DATLEN_T len, bool issync, BLOCKNUM_T *numhdr) = 0;

	virtual int copybuffer(bheader *bh, char *buf, DATLEN_T len, bool tocopy, bool issync) = 0;

	virtual int blockwrite(bheader *bh, bool issync) = 0;

	virtual void setrootoffset(FILEOFF_T roff, bool lock) = 0;

	virtual void copyrootpage(char *buf) = 0;

	virtual FILEOFF_T getrootoffset(bool lock = false) = 0;

	virtual char *getrootpage(bool rwlock) = 0;

	virtual void setdirparams(int igd, FILEOFF_T dirsz) = 0;

	virtual void getdirparams(int *igd, FILEOFF_T *dirsz) = 0;

	virtual void readrootoffset() = 0;

	virtual void readdirparams() = 0;

	virtual void lock_dir(bool rwlock = true) = 0;

	virtual void unlock_dir() = 0;

	virtual void updatepagelsn(bheader *bh, FILEOFF_T plsn) = 0;

	virtual FILEOFF_T readpagelsn(bheader *bh) = 0;

	virtual int writehdr() = 0;

	virtual int readhdr() = 0;

	virtual void setfilefds(int fds[]) = 0;

	virtual void markdirty(bheader *bh) = 0;

	virtual FILEOFF_T seekend(SHORT_T ft, DATLEN_T len) = 0;

	virtual void blockrelease(bheader *bh, bool putatend=true) = 0;

	virtual void blockrelease(bheader **bh, BLOCKNUM_T numhdr, bool putatend=true) = 0;

	virtual int flushpage(bheader *bhdr) = 0;

	virtual void initmaptest() = 0;

	virtual int remove_from_freelist() = 0;

	virtual int closebpool(bool forced = false) = 0;

	virtual int shutdown(bool flushbuf) = 0;

	virtual void kill_buf_cache_workers() = 0;

	virtual void setflog(iqlog *fgl) = 0;

	virtual void setfid(SHORT_T _fid) = 0;

	virtual void warmbuffer() = 0;

	virtual int flushbuffer(bool optimistic = true) = 0;

	virtual int getpageinmem(SHORT_T ftype, SHORT_T fid, BLOCKNUM_T pageid) = 0;

	virtual int init_workers() = 0;

#ifdef BPOOL_DEBUG_MODE
	void testdeadlock() = 0;
#endif

	virtual ~iqbpool() { }
};
}
#endif /* IQBPOOL_H_ */
