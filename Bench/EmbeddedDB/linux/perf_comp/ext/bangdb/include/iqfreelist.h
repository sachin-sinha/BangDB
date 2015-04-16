/*
 * iqfreelist.h
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

#ifndef IQFREELIST_H_
#define IQFREELIST_H_

#include "bangdb.h"

namespace bangdb
{

class iqfreelist
{
public:

	virtual int setbufhashtbls(void *buftables[MAX_FILES]) = 0;

	virtual int init(FILEOFF_T _bufsize, SHORT_T _bufstate) = 0;

	virtual void handle_emergency() = 0;

	virtual bheader *getfree() = 0;

	virtual bheader *getfreelist(int listsize) = 0;

	virtual bheader *get_free_list_ofsize(int *listsize) = 0;

	virtual void lock_file_io() = 0;

	virtual void unlock_file_io() = 0;

	virtual void add_to_free_list(bheader *new_hdr_list, bheader *tail, int _numhdrs) = 0;

	virtual void add_to_free_list(bheader *bh) = 0;

	virtual int grow_free_list(FILEOFF_T _bufsize, SHORT_T _bufstate) = 0;

	virtual int get_num_hdrs() = 0;

	virtual int get_free_hdrs() = 0;

	virtual float get_free_page_ratio() = 0;

	virtual int getMinFP() = 0;

	virtual int get_num_bufhash_tbl() = 0;

	virtual int clean_bufhashtbl(int id) = 0;

	virtual int close() = 0;

	virtual ~iqfreelist() {}
};
}
#endif /* IQFREELIST_H_ */
