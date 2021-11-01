/*
 * BangDBNotificationManager.h
 *
 *  Created on: 20-Jul-2020
 *      Author: sachin
 */

#ifndef SRC_BANGDBNOTIFICATIONMANAGER_H_
#define SRC_BANGDBNOTIFICATIONMANAGER_H_

#include "ResultSet.h"
#include "ScanFilter.h"
#include "TableEnv.h"
#include "BangDBDatabase.h"

namespace BangDB
{
class BangDBNotificationManager {
public:

	BangDBNotificationManager(BangDBDatabase *bdb, int nthreads = 4);

	int registerNotification(const char *notif_meta);

	// state = 0 means pause, 1 means activate, -1 means delete completely
	void deregisterNotification(long notifid, short state);

	// pkts is the pk (timestamp) of the data which is in stream strm
	// This checks if notification is needed or not and if needed, then it queues the notifid for further work. Queued item must be sent
	// If it doesn't need to send the notification then it calls send_notification with op = 0 to update the cnt, lts etc. and returns - it doesn't queue
	int put(long notifid, long pkts, long orig_streamid, const char *notif);

	ResultSet *scanDoc(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	ResultSet *scanRegisteredNotif(ResultSet *prev_rs, FDT *pk_skey = NULL, FDT *pk_ekey = NULL, const char *idx_filter_json = NULL, ScanFilter *sf = NULL);

	int closeNotificationManager(bool force = false);

	virtual ~BangDBNotificationManager();

private:

	BangDBNotificationManager();

	long ptnmgr;
};
}
#endif /* SRC_BANGDBNOTIFICATIONMANAGER_H_ */
