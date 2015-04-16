/*
 * logheader.h
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

#ifndef LOGHEADER_H_
#define LOGHEADER_H_

#include "basehdr.h"

namespace bangdb
{
//to replay the log at start
#define RPLAY_LOG_AT_START 0

//*******end - log related macros************

enum OPTYPE
{
	INSERT,
	UPDATE,
	DELETE,
	END_TRAN,
	BEGIN_CHKPNT,
	END_CHKPNT,
	CLR_INSERT,			//for UNINSERT, UNDELETE, UNUPDATE
	CLR_UPDATE,
	CLR_DELETE,
	IGNORE_LOG_TYPE
};
enum LOGTYPE
{
	INV_LOG,
	HDR_IDX,
	HDR_DAT,
	HDR_DIR,
	INSERT_NOSPLIT_IDX,
	INSERT_SPLIT_IDX,
	UPDATE_IDX,
	DELETE_IDX,
	INSERT_DAT,
	UPDATE_DAT,
	DELETE_DAT,
	INSERT_DIR,
	UPDATE_DIR,
	DELETE_DIR,
	END_TRAN_LOG,
	BEG_CHK_LOG,
	END_CHK_LOG,
	CLR_LOG,
	IGNORE_LOG
};
enum LOGSTATE
{
	LOGFREE,
	LOGBUSY
};
enum TBLTYPE
{
	DPTBL,
	TXTBL
};

struct logparam
{
	SHORT_T type;
	int logfd;
	int mlogfd;
	FILEOFF_T nexttolastflushedLSN;
	FILEOFF_T logeof;
	FILEOFF_T mlogeof;
	pthread_mutex_t logplock;
	pthread_cond_t logpcond;

	void getlogparamlock()
	{
		Pthread_mutex_lock(&logplock);
	}
	void releaselogparamlock()
	{
		Pthread_mutex_unlock(&logplock);
	}
	void init(FILEOFF_T lflsn)
	{
		nexttolastflushedLSN = lflsn;
		Pthread_mutex_init_private(&logplock);
		Pthread_cond_init_private(&logpcond);
	}
};

const int LOGPARAMSZ	=		sizeof(logparam);		//doesn't require anything

//transaction related stuff
struct txnparam
{
private:
	atomic_FILEOFF_T nexttxnid;

public:

	void init(FILEOFF_T ntxnid)
	{
		atomic_FILEOFF_T_set(&nexttxnid, ntxnid);
	}
	FILEOFF_T getnexttxnid()
	{
		return atomic_FILEOFF_T_get_inc(&nexttxnid);
	}

	FILEOFF_T gettxnid()
	{
		return atomic_FILEOFF_T_read(&nexttxnid);
	}
};

const int TXNPARAMSZ	=		sizeof(txnparam);		//doesn't require anything

//the header of the log record
struct log_hdr
{
	SHORT_T empty;
	SHORT_T OPtype;
	SHORT_T ftype;
	SHORT_T id;
	int pageid;
	int hdrlen;
	int reclen;
	int datlen;
	FILEOFF_T LSN;
	FILEOFF_T prevLSN;
	FILEOFF_T txnid;
	FILEOFF_T datofft;


	log_hdr(){}

	log_hdr(FILEOFF_T _lsn, int _reclen, FILEOFF_T _prevlsn, FILEOFF_T _txnid, SHORT_T _optype, SHORT_T _ftype, SHORT_T _fid, int _pageid, int _hdrlen, FILEOFF_T _datofft, int _datlen)
	{
		LSN = (_lsn);
		reclen = (_reclen);
		prevLSN = (_prevlsn);
		txnid = (_txnid);
		OPtype = (_optype);
		ftype = (_ftype);
		id = (_fid);
		pageid = (_pageid);
		hdrlen = (_hdrlen);
		datofft = (_datofft);
		datlen = (_datlen);
		empty = -1;
	}

	void inithdr(FILEOFF_T _lsn, int _reclen, FILEOFF_T _prevlsn, FILEOFF_T _txnid, SHORT_T _optype, SHORT_T _ftype, SHORT_T _fid, int _pageid, int _hdrlen, FILEOFF_T _datofft, int _datlen)
	{
		LSN = (_lsn);
		reclen = (_reclen);
		prevLSN = (_prevlsn);
		txnid = (_txnid);
		OPtype = (_optype);
		ftype = (_ftype);
		id = (_fid);
		pageid = (_pageid);
		hdrlen = (_hdrlen);
		datofft = (_datofft);
		datlen = (_datlen);
	}

	//getters and setters
	void setLSN(FILEOFF_T lsn) { LSN = (lsn); }
	FILEOFF_T getLSN() { return (LSN); }

	void setreclen(int rlen) { reclen = (rlen); }
	int getreclen() { return (reclen); }

	void setprevLSN(FILEOFF_T prevlsn) { prevLSN = (prevlsn); }
	FILEOFF_T getprevLSN() { return (prevLSN); }

	void settxnid(FILEOFF_T tid) { txnid = (tid); }
	FILEOFF_T gettxnid() { return (txnid); }

	void setOPtype(SHORT_T optype) { OPtype = (optype); }
	SHORT_T getOPtype() { return (OPtype); }

	void setftype(SHORT_T ftp) { ftype = (ftp); }
	SHORT_T getftype() { return (ftype); }

	void setid(SHORT_T fid) { id = (fid); }
	SHORT_T getid() { return (id); }

	void setpageid(int pgid) { pageid = (pgid); }
	int getpageid() { return (pageid); }

	void sethdrlen(int hlen) { hdrlen = (hlen); }
	int gethdrlen() { return (hdrlen); }

	void setdatofft(FILEOFF_T dofft) { datofft = (dofft); }
	FILEOFF_T getdatofft() { return (datofft); }

	void setdatlen(int dlen) { datlen = (dlen); }
	int getdatlen() { return (datlen); }
};

const int NLOGHDRSZ = sizeof(log_hdr);
}
#endif /* LOGHEADER_H_ */
