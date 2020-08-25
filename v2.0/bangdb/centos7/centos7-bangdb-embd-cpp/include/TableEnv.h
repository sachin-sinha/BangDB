/*
 * TableEnv.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_TABLEENV_H_
#define SRC_TABLEENV_H_

#include "BangDBCommon.h"

namespace BangDB
{
class TableEnv {
public:
	TableEnv();
	PersistType getDbType();
	void setDbType(PersistType db_type);
	IndexType getIdxType();
	void setIdxType(IndexType idx_type);
	LogType getTableLogType();
	void setTableLogType(LogType table_log_type);
	TableType getTableType();
	void setTableType(TableType table_type);
	KeyType getKeyType();
	void setKeyType(KeyType key_type);
	SortMethod getSortMethod();
	void setSortMethod(SortMethod sort_method);
	SortDirection getSortDirection();
	void setSortDirection(SortDirection sort_direction);
	TableSubType getTblSubType();
	void setTblSubType(TableSubType tbl_sub_type);
	PrimitiveDataType getPrimDataType();
	void setPrimDataType(PrimitiveDataType prim_data_type);
	VersionType getVersionType();
	void setVersionType(VersionType version_type);
	TableSizeHint getTableSizeHint();
	void setTableSizeHint(TableSizeHint table_sz_hint);
	int getKeySize();
	void setKeySize(int key_sz);
	int getLogSizeMb();
	void setLogSizeMb(int log_sz_mb);
	bool getWalEnabled();
	void setWalEnabled(bool wal_enabled);
	bool getAutocommit();
	void setAutocommit(bool autocommit);
	bool getAllowDuplicate();
	void setAllowDuplicate(bool allow_duplicate);
	bool getAllowRevIdx();
	void setAllowRevIdx(bool allow_rev_idx);
	int getTtlsec();
	void setTtlsec(int ttlsec);
	void reset();
	void print();
	virtual ~TableEnv();
	TableEnv(long tev);
	long pttblenv;
private:
	void setFreeFlag(bool flag);
	bool freeFlag;
	friend class BangDBTable;
};
}
#endif /* SRC_TABLEENV_H_ */
