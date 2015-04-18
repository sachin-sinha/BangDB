/*
 * resultset.h
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

#ifndef RESULTSET_H_
#define RESULTSET_H_

#include "fmap.h"

namespace bangdb
{

class fmap;
struct FDTnode;

class resultset
{
public:
	resultset(fmap *fmp);
	void add_doc(resultset *rs, char *orderBy=NULL);
	void add(resultset *rs);
	void append(resultset *rs);
	void intersect(resultset *rs);
	FDT *getNextKey();
	int getNextKeyInt();
	LONG_T getNextKeyLong();
	char *getNextKeyStr();
	FDT *getNextVal();
	int getNextValInt();
	LONG_T getNextValLong();
	char *getNextValStr();
	FDT *searchVal(FDT *key);
	FDTnode *getNode(FDT *key);
	void insert(FDT *key, FDT *val, short _findPos);
	void remove(FDTnode *fnode);
	FDT *lastEvaluatedKey();
	LONG_T lastEvaluatedKeyLong();
	bool moreDataToCome();
	bool hasNext();
	void moveNext();
	int count();
	void updateVal(FDTnode* fn, FDT *v);
	int size();
	int dataSize();
	void begin();
	void begin_reverse();
	void clear();
	void clearIndex();
	fmap *getmap();

private:

	int curpos;
	fmap *recordmap;
};
}
#endif
