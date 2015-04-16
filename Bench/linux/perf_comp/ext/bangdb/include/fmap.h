/*
 * fmap.h
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

#ifndef FMAP_H_
#define FMAP_H_

#include "FDT.h"
//#include "topk.h"

//class topk;
namespace bangdb
{
struct FDTnode
{
	FDT *key;
	FDT *value;
	FDTnode *next;
	FDTnode *prev;
	FDTnode(FDT *k, FDT *v);
	FDTnode();

	void init(FDT *k, FDT *v);
	void reset();
	void clear();
	void clearFixed();
	void clearLongNormal();
	void clearPrimitive();
	void clearIndex();
};

const int fdtnode_size = sizeof(FDTnode);

class fmap
{
public:
	fmap(bool flag, short _sort_id, short _table_type, bool _allow_duplicate, char *readBuff, int size);

	void add_doc(fmap *fm, char *orderBy = NULL);

	void append_doc(fmap *fm, char *orderBy = NULL);

	void intersect_doc(fmap *fm, char *orderBy = NULL);

	void add(fmap *fm);

	void append(fmap *fm);

	void intersect(fmap *fm);

	void begin();

	void begin_reverse();

	bool isempty();

	bool hasnext();

	bool more_data_to_come();

	void set_more_data_to_come(bool flag);

	FDT *last_evaluated_key();

	FDT* getkey();

	FDT* getval();

	FDT* getval(FDT *key);

	FDTnode *getvalnode(FDT *key);

	FDTnode *getCurNode();

	FDTnode *getPrevNode();

	void set_list_end();

	void movenext();

	void put(FDT *key, FDT *val);

	void put(char *key, char *val);

	void put(void *key, int klen, void *val, int vlen, bool copy_keyval = false);

	void put(FDT *key, FDT *val, FDTnode *fn);

	void insert(FDT *key, FDT *val, short _findPos);

	void remove(FDTnode *fnode);

	void remove(FDT *k);

	int size();

	void set_size(int n);

	void set_datasize(int n);

	void set_sortid(int sid);

	void set_table_type(int tbltp);

	void updateVal(FDTnode* fn, FDT *v);

	void updateKey(FDTnode* fn, FDT *k);

	int dataSize();

	int rssize();

	void incr_datasize(int _incr);

	int delta_compute(int klen, int dlen);

	bool is_limit_breached(int rlen, int limitby, int limit);

	bool get_allow_duplicate();

	bool is_limit_breached(int klen, int dlen, int limitby, int limit);

	void clear();

	void clearIndex();

	char *alloc_mem(int size);

	void undo_alloc(int size);

	bool can_alloc(int size);

	bool is_pre_alloc_buf();

	void set_last_evaluated_key(void *key, int keylen, bool _copy_flag);

	void sort_doc(char *byField = NULL);

	bool should_copy(bool isKey);

	void extend_slice(int bySize);

	bool is_extra_buf_list();

	bool get_sort_flag();

	bool get_copy_levk();

	short get_table_type();

	short get_sort_id();

	FDT *get_levk();

	int get_alloc_sz();

	void set_balloc_mem(int buf_len);

	void format_buffer_for_copy();

	void un_format_buffer_for_copy();

	void set_ndupl(int n);

	int get_ndupl();

	FDT *_copy_data(void *k, int len, bool copyflag);

	void print_fmap();

private:

	FDT *_copy_data_nodel(void *k, int len, bool copyflag, FDT *fk);
	FDT *_copy_data_mem_chunk(void *k, int len, bool copyflag);
	FDT *_get_fdt();
	FDTnode *_get_fdtnode();
	char *_get_chunk_mem(int size);
	FDTnode *_dupl(FDTnode *h, int _option);
	int _get_copy_option(bool f1, bool f2);

	FDTnode *_get_node(FDTnode *head, int idx);
	FDTnode *_mid_node(FDTnode *p1, int low, int high, int *mid);
	FDTnode *_binSearch(FDTnode *first, int ncount, FDT *k, int match, int *exactmatch, short _findPos);
	FDTnode *_makeNodeList(FDTnode *head, FDT *k, FDT *v, short _findPos);
	FDTnode *_makeNodeList_nodel(FDTnode *head, FDT *k, FDT *v, FDTnode *t, short _findPos);
	FDTnode *_allocate_nodes(FDT *k, FDT *v, FDTnode *t);
	FDTnode *_makeNodeList(FDTnode *head, FDTnode *t, short _findPos);
	int _delta_compute(FDTnode *node);
	void _clear_node(FDTnode *t);
	void _remove_last_evaluated_key();
	void _set_pre_alloc_buf(char *readBuff, int bufsize);

	FDTnode *_insert(FDT *k, FDT *v, short _findPos);
	FDTnode *_insert_nodel(FDT *k, FDT *v, FDTnode *fn);
	void _delink(FDTnode *n);
	void _link(FDTnode *n);
	FDTnode* _peek_last_item();
	void _remove_last_item();
	FDTnode *_remove_last_item_nodel();
	FDTnode *_remove_nodel(FDTnode *fnode);
	void _clear_fmap_nodel();

	int _keycmp(FDTnode *a, FDTnode *b, char *byField, int sortid, bool isPk);
	FDTnode *_merge_lists(FDTnode *a, FDTnode *b, FDTnode *rootNode, char *byField, int sortid, bool isPk);
	FDTnode *_mergesort_list(FDTnode *l, FDTnode *rootNode, char *byField, int sortid, bool isPk);
	void _sort_list(FDTnode *bhlist, char *byField, int sortid, bool isPk);
	void _sort_doc(FDTnode *rootNode, char *byField = NULL);

	bool travel_forward;
	bool sortflag;
	bool _more_data_to_come;
	bool _pre_alloc_buf;
	bool _copy_levk;
	bool allow_duplicate;
	bangdb_malloc balloc_buf;
	short table_type;
	short sort_id;
	int numelems;
	int data_size;
	int ndupl;
	int mem_chunk_size;
	FDTnode *fdthead;
	FDTnode *hold_fdthead;
	mem_chunk *extra_buf_list;
	FDT *last_eval_key;
	friend class topk;
};
}
#endif /* FMAP_H_ */
