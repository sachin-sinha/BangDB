/*
 * BangDBRTFManager.h
 *
 *  Created on: 23-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBRTFMANAGER_H_
#define SRC_BANGDBRTFMANAGER_H_

#include "BangDBCommon.h"
#include "BangDBMLHelper.h"
#include "BangDBResourceManager.h"

namespace BangDB
{
class BangDBRTFManager {
public:
	BangDBRTFManager(BangDBMLHelper *_bmlh = NULL, BangDBResourceManager *_brs = NULL);
	char *add_udf(const char *udf_req);
	char *remove_udf(const char *lib_name);
	int add_code(const char *code, const char *lib_name, const char *baseclass = "bangdb_rtf_base.h", const char *create_func = "maker");
	int add_code_file(const char *base_path, const char *lib_name, const char *baseclass = "bangdb_rtf_base.h", const char *create_func = "maker");
	int load_lib(const char *base_path, const char *lib_name, const char *create_func = "maker");
	int exec_rtf(const char *lib_name, int argc, void *arg[], void **ret);
	int exec_rtf(long lib_id, int argc, void *arg[], void **ret);
	char *exec_rtf(const char *req);
	char *get_udf_list();
	void close_rtf_manager(bool force = false);
	virtual ~BangDBRTFManager();
	long ptrtf;
};
}
#endif /* SRC_BANGDBRTFMANAGER_H_ */
