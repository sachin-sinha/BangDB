/*
 * iqindex.h
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

#ifndef IQINDEX_H_
#define IQINDEX_H_

//define for stats
//#define TRACK_STATS

//#define USE_DIRCACHE
#define CONCURRENT_OPS

#include "resultset.h"
#include "FDT.h"

namespace bangdb
{
struct scan_filter
{
	scan_operator skey_op;	//default GTE
	scan_operator ekey_op;	//default LTE
	scan_limit_by limitby;	//default LIMIT_RESULT_SIZE
	int limit;				//default 2MB (MAX_RESULTSET_SIZE) for LIMIT_RESULT_SETSIZE
	int skip_count;			//this is set by the db during scan when the last key is duplicated, so that in next scan db should skip these many counts
	scan_filter()
	{
		reset();
	}

	void reset()
	{
		skey_op = GTE;
		ekey_op = LTE;
		limitby = LIMIT_RESULT_SIZE;
		limit = MAX_RESULTSET_SIZE;
		skip_count = 0;
	}

	void clone(scan_filter *_sf)
	{
		skey_op = _sf->skey_op;
		ekey_op = _sf->ekey_op;
		limitby = _sf->limitby;
		limit = _sf->limit;
		skip_count = _sf->skip_count;
	}
};

//interface for index
class iqindex
{
public:

	virtual FILEOFF_T initidx(SHORT_T flag) = 0;

	//can be used for all purpose and we can replace this with all fetch funtion
	virtual int fetch(char *key, int klen, char **val, UINT_T *vlen) = 0;

	virtual int fetch(char *key, int klen, char **buf, int buflen, int *data_len, int *read_len, int part_offt, int *flag) = 0;

	//to fetch the data for a given key
	virtual char* fetch(char *key) = 0;

	//to insert or update data for a given key with associated value
	virtual FILEOFF_T putdata(char *key, char *value, SHORT_T flag) = 0;//flag = 0 for INSERT and 1 for UPDATE

	//to delete the data associated with the key
	virtual FILEOFF_T deletedata(char *key) = 0;

	//useful for scan(btree) from startkey to endkey, limitby (either by size of result set or limited num of rows), limit = actual limit(size in bytes, num of rows)
	virtual resultset* scan(char *skey, char *ekey, scan_filter *sf) = 0;

	//count the number of rows with filter
	virtual FILEOFF_T count(char *skey, char *eky, scan_filter *sf) = 0;

	//to fetch the data for a given key
	virtual FDT* fetch(FDT *key) = 0;

	//to insert or update data for a given key with associated value
	virtual FILEOFF_T putdata(FDT *key, FDT *value, SHORT_T flag) = 0;//flag = 0 for INSERT and 1 for UPDATE

	//to delete the data associated with the key
	virtual FILEOFF_T deletedata(FDT *key) = 0;

	//useful for scan(btree) from startkey to endkey
	virtual resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf) = 0;

	virtual resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf, char *readBuff, int bufsize) = 0;

	//count the number of rows with filter
	virtual FILEOFF_T count(FDT *skey, FDT *ekey, scan_filter *sf) = 0;

	virtual int fetch(LONG_T key, LONG_T *val) = 0;

	virtual FILEOFF_T putdata(LONG_T key, LONG_T val, SHORT_T flag) = 0;

	virtual FILEOFF_T deletedata(LONG_T key) = 0;

	virtual FILEOFF_T putdata(LONG_T key, char *val, int vallen, SHORT_T flag) = 0;

	virtual int fetch_data(LONG_T key, char **val, UINT_T *vlen) = 0;

	virtual int fetch_data(LONG_T key, char **buf, int buflen, int *data_len, int *read_len, int part_offt, int *flag) = 0;

	virtual FDT *fetch_data(LONG_T key) = 0;

	virtual int fetch_long(FDT *key, LONG_T *val) = 0;

	//read data at given offset in the data file
	virtual FDT *read_data(FILEOFF_T doff, int dlen) = 0;

	//read all data for given resultset
	virtual resultset *read_all_data(resultset *dofft_set, scan_filter *sf) = 0;

	//read all data for given resultset for doc (as data)
	virtual resultset *read_all_data_doc(resultset *dofft_set, scan_filter *sf) = 0;

	virtual resultset *read_all_data_prebuf(resultset *dofft_set, scan_filter *sf) = 0;

	virtual resultset *read_all_data_doc_prebuf(resultset *dofft_set, scan_filter *sf) = 0;

	virtual void setAllowDuplicates(bool flag) = 0;

	//this is called during init, doesn't do much as of now, might remove this later on as it's not useful as thought during design phase
	virtual void rewind() = 0;

	//to print the stats for the index
	virtual void printstats() = 0;

	//to clean the index
	virtual void clean() = 0;

	//callback function for wal to do rollback/undo insert
	virtual FILEOFF_T uninsert(char *key, DATLEN_T keylen) = 0;

	//callback function for wal to do rollback/undo for update
	virtual FILEOFF_T unupdate(char *key, DATLEN_T keylen, FILEOFF_T offt, DATLEN_T datlen) = 0;

	//callback function for wal to do rollback.undo for delete
	virtual FILEOFF_T undelete(char *key, DATLEN_T keylen, FILEOFF_T datofft, DATLEN_T datlen) = 0;

#ifdef BPOOL_DEBUG_MODE
	//test function for deadlock
	virtual void testdeadlock() = 0;
#endif

	//destructor for index
	virtual ~iqindex() { }
};
}
#endif /* IQINDEX_H_ */
