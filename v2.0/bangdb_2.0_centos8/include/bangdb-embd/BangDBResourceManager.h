/*
 * BangDBResourceManager.h
 *
 *  Created on: 23-Jul-2020
 *      Author: sachin
 */

#ifndef BANGDBRESOURCEMANAGER_H_
#define BANGDBRESOURCEMANAGER_H_

#include "BangDBCommon.h"
#include "BangDBDatabase.h"

namespace BangDB
{
class BangDBResourceManager {
public:
	BangDBResourceManager(BangDBDatabase *bdb);

	int init_brs_meta();

	int create_bucket(char *bucket_info);

	char *list_buckets(char *user_info);

	char *list_all_buckets(char *user_info);

	long count_buckets();

	int delete_bucket(char *bucket_info);

	long put_object(char *bucket_info, char *key, char *data, long datlen, bool force = false);

	long get_object(char *bucket_info, char *key, char **data, long *datlen);

	long put_file(char *bucket_info, char *key, char *fpath, InsertOptions iop, bool force = false);

	long get_file(char *bucket_info, char *key, char *fname, char *fpath);

	//returns the current number of objects for the bucket if successful else -1
	int del_object(char *bucket_info, char *key);

	int count_slices(char *bucket_info, char *key);

	long count_objects(char *bucket_info);

	char *count_objects_details(char *bucket_info);

	char *list_objects(char *bucket_info);

	int close_bucket(char *bucket_info);

	int close_resource_manager(CloseType closetype = DEFAULT, bool force = false);

	virtual ~BangDBResourceManager();

	long ptbrs;
};
}
#endif /* BANGDBRESOURCEMANAGER_H_ */
