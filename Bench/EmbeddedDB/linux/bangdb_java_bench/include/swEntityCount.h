/*
 * swEntityCount.h
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

#ifndef SWENTITYCOUNT_H_
#define SWENTITYCOUNT_H_

#include "swCount.h"
#include "swSlotCount.h"
#include "hash_tbl.h"
#include "light_lock.h"
#include "bangdb_json_parser.h"

namespace bangdb
{

struct iqcount_item
{
	char *name;
	iqcount *iqc;
	~iqcount_item()
	{
		delete[] name;
		iqc->close();
		delete iqc;
		iqc = NULL;
	}
};

class swEntityCount {
public:
	//nEntity refers to number of entities that should be added roughly, basically table size of hash table
	swEntityCount(const char *entityName, int swTime, int swExpiry, int nEntity = 32);

	int init();

	int add(const char *entityName, const char *s, int len);

	int add(const char *entityName, int entitylen, const char *s, int len);

	void add_create(const char *entityName, const char *s, int len, bangdb_window_type swType, bangdb_count_type countType);

	void add_create(const char *entityName, int entitylen, const char *s, int len, bangdb_window_type swType, bangdb_count_type countType);

	LONG_T count(const char *entityName);

	LONG_T count(const char *entityName, int span);

	//returns json string containing list of all the counts for entities and overall count
	char* list_count_json();

	//returns items which have count greater than zero
	char *list_count_str();

	//in future when we support different entities with different swTime and swExpiry
	//void addEntity(char *name, int swTime, int swExpiry, bangdb_window_type swtype);

	//use the default swTime and swExpiry
	void createEntity(const char *name, bangdb_window_type swType, bangdb_count_type countType);

	void createEntity(const char *name, int len, bangdb_window_type swType, bangdb_count_type countType);

	void removeEntity(const char *name);

	void removeEntity(const char *name, int len);

	bool shouldExit();

	void shutdown();

	virtual ~swEntityCount();

private:

	void _createEntity(const char *name, int nameLen, bangdb_window_type swType, bangdb_count_type countType);

	int _add(const char *entityName, int elen, const char *s, int len);

	LONG_T _count(const char *entityName);

	LONG_T _count(const char *entityName, int span);

	void _foldSlots();

	void _arrange();

	static void *_arrangeTable(void *arg);

	int _init();

	char *ename;

	bool _shouldExit();

	bool _shouldexit;

	bool _exited;

	bool _init_done;

	int _swTime;

	int _swExpiry;

	long SW_COUNT_SLEEP_FREQ;

	hash_tbl<iqcount_item> *entity_list;

	pthread_t _bworker;

	light_mutex_lock _lock;
};
}
#endif /* SWENTITYCOUNT_H_ */
