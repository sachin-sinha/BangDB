/*
 * swEntityCount.h
 *
 *  Author: Sachin Sinha
  *  Libbangdb-client library
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

#include "hash_tbl.h"
#include "light_lock.h"
#include "bangdb_json_parser.h"
#include "bangdbEnv.h"
namespace bangdb_client
{
class bangdbEnv;
struct client_context;

class swEntityCount {
public:
	//nEntity refers to number of entities that should be added roughly, basically table size of hash table
	swEntityCount(bangdbEnv *dbEnv, char *entityName, int swTime, int swExpiry, int nEntity = 32);

	int init();

	int add(client_context *c, char *entityName, char *s, int len);

	int add(client_context *c, char *entityName, int entitylen, char *s, int len);

	void add_create(client_context *c, char *entityName, char *s, int len, bangdb_window_type swType, bangdb_count_type countType);

	void add_create(client_context *c, char *entityName, int entitylen, char *s, int len, bangdb_window_type swType, bangdb_count_type countType);

	LONG_T count(client_context *c, char *entityName);

	LONG_T count(client_context *c, char *entityName, int span);

	//returns json string containing list of all the counts for entities and overall count
	char* list_count_json(client_context *c);

	//returns items which have count greater than zero
	char *list_count_str(client_context *c);

	//in future when we support different entities with different swTime and swExpiry
	//void addEntity(char *name, int swTime, int swExpiry, bangdb_window_type swtype);

	//use the default swTime and swExpiry
	void createEntity(client_context *c, char *name, bangdb_window_type swType, bangdb_count_type countType);

	void createEntity(client_context *c, char *name, int len, bangdb_window_type swType, bangdb_count_type countType);

	void removeEntity(client_context *c, char *name);

	void removeEntity(client_context *c, char *name, int len);

	//bool shouldExit();

	void shutdown(bangdb_close_type swclose = DEFAULT_AT_CLIENT);

	virtual ~swEntityCount();

private:

	bangdbEnv *_dbEnv;

	char *ename;

	ULONG_T tid;

	int _swTime;

	int _swExpiry;

	int _nEntity;
};
}
#endif /* SWENTITYCOUNT_H_ */
