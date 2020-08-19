/*
 * BangDBStreamManager.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef BANGDBSTREAMMANAGER_H_
#define BANGDBSTREAMMANAGER_H_

#include "BangDBDatabase.h"
#include "BangDBMLHelper.h"

namespace BangDB
{
class BangDBStreamManager {
public:

	BangDBStreamManager(BangDBDatabase *bdb, BangDBMLHelper *bmlh);

	char *registerSchema(const char *schema_json);

	char *deregisterSchema(const char *schema_name);

	char *addStreams(long schemaid, const char *streams);

	char *deleteStreams(long schemaid, const char *streams);

	char *setStreamState(const char *schema, const char *stream, short st);

	int getStreamState(const char *schema, const char *stream);

	char *addUdfs(long schema_id, const char *udfs);

	char *delUdfs(long schema_id, const char *udfs);

	char *getUdfList();

	ResultSet *scanRegisteredNotif(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	ResultSet *scanNotification(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	char *put(long schemaid, long streamid, const char *doc, int doc_len = 0);

	int putBulk(long schemaid, long streamid, const char *buf, int buflen);

	long uploadTrainData(long schema_id, long stream_id, char *req_json, long *fsz);

	char *put(long schemaid, long streamid, long k, const char *v);

	int get(long schemaid, long streamid, long key, char **val);

	ResultSet *scanDoc(long schemaid, long streamid, ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	ResultSet *scanProcDoc(long schemaid, long streamid, const char *attr_names_json, ResultSet *prev_rs, ScanFilter *sf = NULL);

	long countProc(long schemaid, long streamid, const char *attr_names_json, ScanFilter *sf = NULL);

	long getGpbyName(long schemaid, long streamid, const char *gpby_attr_list, char **out_json);

	long count(long schemaid, long streamid);

	long count(long schemaid, long streamid, FDT *pk_skey, FDT *pk_ekey, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	ResultSet *scanUsage(ResultSet *prev_rs, long fromts, long tots, int rollup, ScanFilter *sf = NULL);

	long getSchemaid(const char *schema_name, bool check_valid = true);

	long getStreamid(const char *schema_name, const char *stream_name, bool check_valid = true);

	char *getSchemaStr(const char *schema_name);

	char *getSchemaFromMetadata(const char *schema_name);

	char *getSchemaDepGraph(long schema_id, bool bfs = true);

	char *getStreamDepGraph(long schema_id, long stream_id, bool only_dep = false);

	void closeBangdbStreamManager(bool force = false);

	virtual ~BangDBStreamManager();

private:

	BangDBStreamManager();

	long ptstrm;
};
}
#endif /* BANGDBSTREAMMANAGER_H_ */
