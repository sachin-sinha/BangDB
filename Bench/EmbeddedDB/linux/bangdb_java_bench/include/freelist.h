/*
 * freelist.h
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

#ifndef FREELIST_H_
#define FREELIST_H_

#include "fmap.h"

namespace bangdb
{
struct FDTnode;
/*
 * simple lock less(unsafe in concurrent environment) free list, user should provide u which they wish to have free list for
 */

struct u_item
{
	UINT_T key;
	char *name;	//only for debug purpose
	FDTnode *node;
	ULONG_T ts;
	u_item *next;
	u_item *prev;
	u_item()
	{
		init();
	}
	void init()
	{
		key = 0;
		name = NULL;
		node = NULL;
		ts = 0;
		next = prev = NULL;
	}

	void reset()
	{
		key = 0;
		if(name)
			delete[] name;
		node = NULL;
		ts = 0;
		next = prev = NULL;
	}

	~u_item()
	{
		reset();
	}
};

const int u_item_size = sizeof(u_item);

class freelist {
public:
	freelist(int size);

	//gets a new item from freelist, removes from free list and returns
	u_item *get_from_freelist();

	//given an item it links in lru at the back always
	void link_in_lru(u_item *obj);

	//given an item, it delinks from the lru list
	void  delink_from_lru(u_item *obj);

	//given an item it links in free list
	void link_in_freelist(u_item *obj);

	//it peeks the oldest item, basically front of lru list
	u_item *peek_oldest();

	//it delinks item from front of lru
	u_item *free_oldest();

	//gets a new item from freelist, removes from free list and returns
	FDTnode *get_from_freelist_fdt();

	//given an item it links in free list
	void link_in_freelist_fdt(FDTnode *obj);

	//cleans up the uitems created in freelist at the start and other resources
	void close();

	virtual ~freelist();
private:

	int _init();
	int nsize;
	int bufsize;
	char *bufaddr;
	u_item *fl;
	u_item *lru;
	FDTnode *fl_fdt;
};
}
#endif /* FREELIST_H_ */
