/*
 * BangDBMLHelper.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBMLHELPER_H_
#define SRC_BANGDBMLHELPER_H_

#include "BangDBCommon.h"
#include "ResultSet.h"
#include "BangDBDatabase.h"

namespace BangDB
{
class BangDBMLHelper {
public:

	BangDBMLHelper(BangDBDatabase *bdb, long mem_budget = 0);

	int createBucket(const char *bucket_info);

	void setBucket(const char *bucket_info);

	long uploadFile(const char *key, const char *fpath, InsertOptions iop);

	char *trainModel(const char *req);

	char *getModelStatus(const char *req);

	int delModel(const char *req);

	int delTrainRequest(const char *req);

	char *predict(const char *req, void *arg = NULL);

	ResultSet *getTrainingRequests(const char *accountid, const char *levk = NULL);

	char *getRequest(const char *req);

	int setStatus(const char *status);

	char *getModelPredStatus(const char *req);

	int delPredRequest(const char *req);

	long uploadFile(const char *bucket_info, const char *key, const char *fpath, InsertOptions iop);

	long downloadFile(const char *bucket_info, const char *key, const char *fname, const char *fpath);

	long getObject(const char *bucket_info, const char *key, const char **data, long *datlen);

	int delFile(const char *bucket_info, const char *key);

	int delBucket(const char *bucket_info);

	long countBuckets();

	int countSlices(const char *bucket_info, const char *key);

	long countObjects(const char *bucket_info);

	char *countObjectsDetails(const char *bucket_info);

	long countModels(const char *accountid);

	char *listObjects(const char *bucket_info, const char *key = NULL, int list_size_mb = 0);

	char *listBuckets(const char *user_info);

	int closeBangDBMLHelper(bool force = false);

	virtual ~BangDBMLHelper();

	long ptml;
private:

	BangDBMLHelper();
};
}
#endif /* SRC_BANGDBMLHELPER_H_ */
