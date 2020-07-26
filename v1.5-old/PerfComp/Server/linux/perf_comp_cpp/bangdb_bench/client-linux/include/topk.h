/*
 * topk.h
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

#ifndef TOPK_H_
#define TOPK_H_

#include "resultset.h"
//#include "freelist.h"
#include "hash_tbl.h"
#include "timestamp.h"
#include "bangdbEnv.h"
namespace bangdb_client
{
struct FDTnode;
class topk;
class fmap;
class resultset;
class freelist;
struct u_item;
/*
 * using hash_string_32 for hashing the name (uniqueparam) and not hash_string_64, this is because
 * we overload the FDT length for key with the hash value. This is important because we use hash of unique param
 * to identify the node in the fmap but we need reference from fmap to hash tbl and this can be only done by unique param or hash of it
 * Hence since length is DATLEN_T (unsigned int) hence use hash_string_32 which returns unsigned int
 *
 * Three lists  - famp (sorted by key)
 * 				- lru (for least recently used)
 * 				- hashmap (for O(1) access to the item)
 * We use pre allocated memory for FDTNode and FDT. But still copy the value for each insert and delete the value for each remove.
 * We may avoid these memory allocation as well by having a memory slab pre allocated
 *
 * Also we may have getTopK with user supplied buffer on which we may write our results
 */

class topk {
public:
	//sortid should always be more than 30 bacause the sorting would be done by score (Asc or desc)
	topk(bangdbEnv *dbEnv, char *topkName, int swSizeSec, int k, bool desc, char *uniqueBy);
	void put(client_context *c, long score, char *data, int datalen, char *uniqueParam);
	void put(client_context *c, long score, char *data, int datalen, char *uniqueParam, int paramlen);
	resultset *getTopK(client_context *c, int k = 0);
	char *getTopKJson(client_context *c, int k = 0);
	void close(bangdb_close_type topk_close = DEFAULT_AT_CLIENT);
	bangdbEnv *getDBEnvRef();
	virtual ~topk();

private:

	bangdbEnv *_dbEnv;
	char *_topkName;
	int _swSize;
	int _k;
	ULONG_T tid;
	bool _desc;
	char *_uniqueBy;
};
}
#endif /* TOPK_H_ */
