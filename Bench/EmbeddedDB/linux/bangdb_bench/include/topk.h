/*
 * topk.h
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

#ifndef TOPK_H_
#define TOPK_H_

#include "resultset.h"
#include "freelist.h"
#include "hash_tbl.h"
#include "timestamp.h"

namespace bangdb
{

struct FDTnode;
class topk;
class fmap;
class resultset;
class freelist;
struct u_item;


class topk {
public:

	topk(const char *topkName, int swSizeSec, int k, bool desc, char *uniqueBy);
	void put(long score, char *data, int datalen, char *uniqueParam);
	void put(long score, char *data, int datalen, char *uniqueParam, int paramlen);
	resultset *getTopK(int k = 0);
	char *getTopKJson(int k = 0);
	void close();
	virtual ~topk();

private:

	resultset *_getTopK(int k);
	char *_getTopKJson(int k);
	void _put(long score, char *data, int datalen, char *uniqueParam, int paramlen);
	u_item *_find_key(char *p);
	u_item *_find_key(unsigned int key);
	void _remove_min();
	void _remove_oldest();
	int _insert(FDT *k, FDT *v, unsigned int key, char *uniqueParam, int paramlen);
	void _update(FDTnode *fn, FDT *k, FDT *v);
	long _min_score();
	long _cmp_score(long s1, long s2);
	bool _shouldExit();
	static void *_expireRecords(void *arg);
	void _expire();
	bool _shouldExpire(u_item *u);
	int _init();

	char* name;
	long swSize;
	int K;
	int sort_id;
	int nk;
	char *uniqueByName;
	long sleep_time;
	bool _shouldexit;
	bool _exited;
	fmap *fm;
	freelist *tsl;				//time sorted list, basically lru list
	hash_tbl<u_item> *ulist;	//unique list
	light_mutex_lock _lock;
	pthread_t _bworker;
};
}
#endif /* TOPK_H_ */
