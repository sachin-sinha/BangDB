/*
 * tableenv.h
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

#ifndef TABLEENV_H_
#define TABLEENV_H_

#include "basehdr.h"

namespace bangdb
{

class table_env {
public:

	table_env();

	table_env(short TINY_SMALL_NORMAL_BIG, short persist_type, short BTREE_EXTHASH, short key_size, bool auto_commit, bool log_enabled = false,  short log_type = 0, short log_size_mb = 0);

	table_env* clone_env();

	void reset();

	void set(table_env *tenv);

	/* setters and getters */
	void set_persist_type(short persist_type);
	void set_idx_type(short BTREE_EXTHASH);
	void set_table_type(short _table_type);
	void set_key_size_byte(short key_size);
	void set_log_size_mb(short log_size_mb);
	void set_table_size_hint(short TINY_SMALL_NORMAL_BIG);
	void set_log_state(bool is_log_on);
	void set_log_type(short log_type);
	void set_autocommit_state(bool is_autocommit_on);
	void set_sort_method(short sort_method);
	void set_sort_dirction(short sort_direction);
	void set_key_type(short key_type);
	void set_allow_duplicate(bool allowDuplicate);
	void set_primitive_data_type(short _data_type);
	void set_table_subtype(short _sub_type);
	void set_config_vars();

	short get_persist_type();
	short get_idx_type();
	short get_table_type();
	short get_key_size_byte();
	short get_log_size_mb();
	short get_table_size_hint();
	short get_log_type();
	bool get_log_state();
	bool get_autocommit_state();
	short get_sort_method();
	short get_sort_direction();
	short get_key_type();
	short get_sort_id();
	short get_primitive_data_type();
	short get_table_subtype();
	bool get_allow_duplicate();

	int get_dir_table_size();
	int get_idx_table_size();
	int get_dat_table_size();
	int get_IDX_SIZE();
	short get_page_type();
	short get_maxkey();
	int get_NDPBUFSZ();
	int get_NTXBUFSZ();
	int get_NDPFREEEC();
	int get_NTXFREEEC();
	int get_DPTBLSZ();
	int get_TXTBLSZ();
	int get_DPHDRSZ();
	int get_TXHDRSZ();
	int get_DPHASHTBLSZ();
	int get_TXHASHTBLSZ();
	off_t get_LOGSHMEM();

	bool isTableAttributeEqual(table_env *tenv);

	virtual ~table_env();
private:
	table_env(const table_env &);
	table_env& operator = (const table_env&);
	void _set_table_size();
	void _set_other_vars();
	void _configure_sort();
	void _verify();
	void _set(table_env *tenv);

	short db_type;
	short idx_type;
	short key_sz;
	short table_sz_hint;
	short log_sz_mb;
	short table_log_type;
	short table_type;
	bool wal_enabled;
	bool autocommit;
	short sort_method;
	short sort_direction;
	short key_type;
	short sort_id;
	short prim_data_type;
	short table_subtype;
	bool allow_duplicate;

	/* computed ones */
	off_t LOGSHMEM;
	short IDX_SZ;
	short maxkey;
	int DPTBLSZ;
	int TXTBLSZ;
	int NDPBUFSZ;
	int NTXBUFSZ;
	int DPHASHTBLSZ;
	int TXHASHTBLSZ;
	int NDPFREEEC;
	int NTXFREEEC;
	int DPHDRSZ;
	int TXHDRSZ;
	int hash_table_size_dir;
	int hash_table_size_dat;
	int hash_table_size_idx;
};
}
#endif /* TABLEENV_H_ */
