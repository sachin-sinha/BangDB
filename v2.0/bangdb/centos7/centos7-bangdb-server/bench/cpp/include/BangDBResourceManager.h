/*
 * BangDBResourceManager.h
 *
 *  Created on: 23-Jul-2020
 *      Author: sachin
 */

#ifndef BANGDBRESOURCEMANAGER_H_
#define BANGDBRESOURCEMANAGER_H_

#include "BangDBCommon.h"
#include "BangDBEnv.h"

namespace BangDB_Client
{
class BangDBResourceManager {
public:
	BangDBResourceManager(BangDBEnv *bdb);

	int init_brs_meta();

	int create_bucket(const char *bucket_info);

	char *list_buckets(const char *user_info);

	char *list_all_buckets(const char *user_info);

	long count_buckets();

	int delete_bucket(const char *bucket_info);

	long put_object(const char *bucket_info, const char *key, const char *data, long datlen, bool force = false);

	long get_object(const char *bucket_info, const char *key, char **data, long *datlen);

	long put_file(const char *bucket_info, const char *key, const char *fpath, InsertOptions iop, bool force = false);

	long get_file(const char *bucket_info, const char *key, const char *fname, const char *fpath);

	//returns the current number of objects for the bucket if successful else -1
	int del_object(const char *bucket_info, const char *key);

	int count_slices(const char *bucket_info, const char *key);

	long count_objects(const char *bucket_info);

	char *count_objects_details(const char *bucket_info);

	char *list_objects(const char *bucket_info, const char *skey, int list_size_mb);

	int close_bucket(const char *bucket_info);

	int close_resource_manager(CloseType closetype = DEFAULT_AT_CLIENT, bool force = false);

	virtual ~BangDBResourceManager();

	long ptbrs;
};
}
#endif /* BANGDBRESOURCEMANAGER_H_ */
