/*
 * iqlog.h
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

#ifndef IQLOG_H_
#define IQLOG_H_

#include "logrecord.h"
#include "iqindex.h"
#include "iqbpool.h"

namespace bangdb
{

class iqbpool;

class iqlog {
public:

	virtual void set_table_params(SHORT_T fid, iqbpool *_bp, table_env *_tenv) = 0;

	//we need to set the index pointer as _undo callsback into index
	virtual void setidx(iqindex *_idx, SHORT_T fid = 0) = 0;

	virtual void unset_table_params(SHORT_T fid) = 0;

	virtual int initflog() = 0;

	//get a new tran id
	virtual FILEOFF_T gettxnid() = 0;

	//get a new log record, user can pass the common hdr of the log while requesting new log for efficiency
	virtual logrecord* getlogrec(SHORT_T logtype, FILEOFF_T pLSN, FILEOFF_T tid, SHORT_T optype, SHORT_T filetype, SHORT_T fid) = 0;

	//write rec logrec into log and returns LSN of the record in success, -1 for error
	virtual FILEOFF_T writelogrec(logrecord *logrec) = 0;

	//this one takes lock from flog itself, one less lock in the process but larger code path
	virtual FILEOFF_T writelogrec2(logrecord *logrec) = 0;

	//read log rec at a given LSN retrurns logrec for success NULL for error
	virtual logrecord* readlogrec(FILEOFF_T LSN) = 0;

	//free the logrecord
	virtual void freelogrec(logrecord *logrec) = 0;

	virtual FILEOFF_T flush(FILEOFF_T uptoLSN = 0) = 0;

	//sync the master log file to disk
	virtual int flush_master() = 0;

	//returns the master log ptr
	virtual void *getmasterlog() = 0;

	//this method is to update the db file from log files in case of some issue
	virtual int updatedbfile(bool shouldanalyze) = 0;

	//to set the bufflushedlsn in the ml, called from _write_buffer() from bpool
	virtual void setbufflushedlsn(FILEOFF_T bflsn) = 0;

	//this removes the entry from dptable, note it creates the key before doing that
	virtual void removefromdbtbl(SHORT_T ftype, SHORT_T fid, BLOCKNUM_T pageid) = 0;

	virtual void removefromdbtbl(SHORT_T ftype, SHORT_T fid, BLOCKNUM_T frompageid, BLOCKNUM_T endpageid) = 0;

	virtual int undo(FILEOFF_T txnid = -1) = 0;

	virtual int closeflog() = 0;

	//stop and kill background workers
	virtual void kill_log_workers() = 0;

	//check masterlog sanity and also update master dbclose
	virtual void master_sanity() = 0;

	//to lock master
	virtual void lockmaster() = 0;

	//to release lock on master
	virtual void releasemaster() = 0;

	//function to undo a transaction, it's difficult to test rollback or undo for a single trasaction boundary, hence a helper function for test as well
	virtual int undotran(FILEOFF_T txnid) = 0;

	virtual int inithousekeep() = 0;

	//set the undoflag for forced undo
	virtual void setundo(bool _undoflag) = 0;

	virtual FILEOFF_T getnextlsn() = 0;

	virtual bangdb_log_type get_log_type() = 0;

	//destructor
	virtual ~iqlog() {}
};
}
#endif /* IQLOG_H_ */
