/**
 * Copyright (c) 2012 YCSB contributors. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You
 * may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License. See accompanying
 * LICENSE file.
 */

/**
 * BangDB client binding for YCSB.
 *
 */

package site.ycsb.db;

import site.ycsb.ByteIterator;
import site.ycsb.DB;
import site.ycsb.DBException;
import site.ycsb.Status;
import site.ycsb.StringByteIterator;
import com.bangdb.*;

import com.google.gson.Gson;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.Vector;


/**
 * YCSB binding for <a href="http://bangdb.com/">BangDB</a>.
 *
 * See {@code redis/README.md} for details.
 */
public class BangdbClient extends DB {

  private BangDBEnv dbenv;
  private BangDBDatabase db;
  private BangDBTable tbl;
  private TableEnv te;
  private static boolean flag = true;
  private static int count = 0;
  private Gson gson;

  public void init() throws DBException {
    System.loadLibrary("bangdb-client-java");
    DBParam dbp = new DBParam();
    dbp.set_host("127.0.0.1");
    dbp.set_port("10101");
    dbp.setTransactionType(TransactionType.DB_MULTIOPS_TRANSACTION_NONE);
    dbenv = BangDBEnv.getInstance(dbp);
    if(dbenv == null) {
      System.out.println("bangdb env couldn't be initialized");
    }
    db = dbenv.openDatabase("ycsb", dbp);

    te = new TableEnv();
    te.setTable_type(TableType.WIDE_TABLE);
    //te.setLogState(false);

    tbl = db.getTable("usertable", te, OpenType.OPENCREATE);
    gson = new Gson();
  }

  public void cleanup() throws DBException {
    //tbl.closeTable(CloseType.DEFAULT_AT_SERVER, false);
    //dbenv.closeDatabase(CloseType.DEFAULT_AT_SERVER);
    //dbenv.close();
  }

  @Override
  public Status read(String table, String key, Set<String> fields,
      Map<String, ByteIterator> result) {
    byte[] rs = tbl.get(key, null);

    if (rs == null) {
      System.out.println("READ ERROR");
      return Status.ERROR;
    } else {
      if (fields == null) {
        String srs = new String(rs);
        result = gson.fromJson(srs, result.getClass());
      } else {
        System.out.println("Read not implemented");
        return Status.ERROR;
      }
    }
    return result.isEmpty() ? Status.ERROR : Status.OK;
  }

  @Override
  public Status insert(String table, String key,
      Map<String, ByteIterator> values) {
    String inputJson = gson.toJson(StringByteIterator.getStringMap(values));
    if (tbl.putDoc(inputJson, key, null, InsertOptions.INSERT_UNIQUE) < 0) {
      return Status.ERROR;
    }
    return Status.OK;
  }

  @Override
  public Status delete(String table, String key) {
    return tbl.del(key, null) < 0 ? Status.ERROR : Status.OK;
  }

  @Override
  public Status update(String table, String key,
      Map<String, ByteIterator> values) {
    String inputJson = gson.toJson(StringByteIterator.getStringMap(values));
    return tbl.putDoc(inputJson, key, null, InsertOptions.UPDATE_EXISTING) < 0 ? Status.ERROR : Status.OK;
  }

  @Override
  public Status scan(String table, String startkey, int recordcount,
      Set<String> fields, Vector<HashMap<String, ByteIterator>> result) {
    ScanFilter sf = new ScanFilter();
    sf.limitBy = ScanLimitBy.LIMIT_RESULT_ROW;
    sf.limit = recordcount;
    sf.setFilter();
    ResultSet rs = null;
    int nitr = 0;
    while(true) {
      rs = tbl.scanDoc(rs, startkey, null, null, sf);
      if(rs == null) {
        break;
      }
      HashMap<String, ByteIterator> values = new HashMap<String, ByteIterator>(rs.count());
      while(rs.hasNext()) {
        values.put(rs.getNextKeyStr(), new StringByteIterator(rs.getNextValStr()));
        result.add(values);
        rs.moveNext();
        values.clear();
      }
      ++nitr;
    }
    return nitr > 0 ? Status.OK : Status.ERROR;
/*
    rs = tbl.scanDoc(rs, startkey, null, null, sf);
    if (rs != null) {
      HashMap<String, ByteIterator> values = new HashMap<String, ByteIterator>(rs.count());
      while(rs.hasNext()) {
        values.put(rs.getNextKeyStr(), new StringByteIterator(rs.getNextValStr()));
        result.add(values);
        rs.moveNext();
        values.clear();
      }
      rs.clear();
      return Status.OK;
    }

    return Status.ERROR;
*/
  }

}
