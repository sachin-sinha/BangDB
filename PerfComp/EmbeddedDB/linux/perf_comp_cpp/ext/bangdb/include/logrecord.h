/*
 * logrecord.h
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

#ifndef BTREELOGRECORD_H_
#define BTREELOGRECORD_H_

#include "bangdb.h"

namespace bangdb
{
struct logrecord
{
	log_hdr loghdr;

	SHORT_T idxtp;
	SHORT_T logtype;

	int olddatlen;
	FILEOFF_T olddatofft;

	char *databuffer;
	char *hdrbuffer;
	char *hdr;

	char *data;

	char tempbuf[RECHDRSZ];

	char *baseaddr;
	logrecord *nextlogrec;

	void init(SHORT_T idxtype, SHORT_T lgtp, FILEOFF_T pLSN, FILEOFF_T tid, SHORT_T optype, SHORT_T filetype, SHORT_T fid);

	void formathdr()
	{
		memcpy(baseaddr, (void*)&loghdr, NLOGHDRSZ);
	}

	void copyloghdr(log_hdr *lghdr)
	{
		loghdr.inithdr(lghdr->LSN, lghdr->reclen, lghdr->prevLSN, lghdr->txnid, lghdr->OPtype, lghdr->ftype, lghdr->id, lghdr->pageid, lghdr->hdrlen, lghdr->datofft, lghdr->datlen);
	}

	void initfrombuf(char *buf)
	{
		memcpy(&loghdr, buf, NLOGHDRSZ);
		memcpy(baseaddr, buf, getreclen());
	}

	void writelog();

	void writedata(FILEOFF_T offt, int len, void *dat);

	void writeidx(int hlen, void *hdrbuf, int offt, int len, void *dat);

	void writeidxhdr(FILEOFF_T offt, int len, void *pgcont);

	void writeidxupd(FILEOFF_T odatofft, int odatlen, int offt, int len, void *dat);

	void writeidxdel(FILEOFF_T offt, int len, void *dat);

	void writemisc();

	void writechkp(int rlen);

	void writedirdouble(FILEOFF_T start, FILEOFF_T end);

	void readdirdouble(FILEOFF_T *start, FILEOFF_T *end);

	void readrecords(SHORT_T idxtype);

	void resetlogrec();

	char* getkey(int *keylen, FILEOFF_T *datofft, int *datlen);

	void setLSN(FILEOFF_T lsn) { loghdr.LSN = (lsn); }
	FILEOFF_T getLSN() { return (loghdr.LSN); }

	void setreclen(int rlen) { loghdr.reclen = (rlen); }
	int getreclen() { return (loghdr.reclen); }

	void setprevLSN(FILEOFF_T prevlsn) { loghdr.prevLSN = (prevlsn); }
	FILEOFF_T getprevLSN() { return (loghdr.prevLSN); }

	void settxnid(FILEOFF_T tid) { loghdr.txnid = (tid); }
	FILEOFF_T gettxnid() { return (loghdr.txnid); }

	void setOPtype(SHORT_T optype) { loghdr.OPtype = (optype); }
	SHORT_T getOPtype() { return (loghdr.OPtype); }

	void setftype(SHORT_T ftp) { loghdr.ftype = (ftp); }
	SHORT_T getftype() { return (loghdr.ftype); }

	void setid(SHORT_T fid) { loghdr.id = (fid); }
	SHORT_T getid() { return (loghdr.id); }

	void setpageid(int pgid) { loghdr.pageid = (pgid); }
	int getpageid() { return (loghdr.pageid); }

	void sethdrlen(int hlen) { loghdr.hdrlen = (hlen); }
	int gethdrlen() { return (loghdr.hdrlen); }

	void setdatofft(FILEOFF_T dofft) { loghdr.datofft = (dofft); }
	FILEOFF_T getdatofft() { return (loghdr.datofft); }

	void setdatlen(int dlen) { loghdr.datlen = (dlen); }
	int getdatlen() { return (loghdr.datlen); }
};

const int RECBUFSZ = sizeof(logrecord);
}
#endif /* BTREELOGRECORD_H_ */
