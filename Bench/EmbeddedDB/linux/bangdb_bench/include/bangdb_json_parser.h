/*
 * bangdb_json_parser.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb library
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

#ifndef BANGDB_JSON_PARSER_H_
#define BANGDB_JSON_PARSER_H_

#include "iqjson.h"
namespace bangdb
{
class bangdb_json_parser : public iqjson
{
public:
	bangdb_json_parser();

	bangdb_json_parser(char *_json);

	void reset();

	void setJson(char *_json);

	bool parseOutPlace(char *_json);

	bool parseInPlace(char jbuf[]);

	char* getValueString(char *key, int *len);

	bool getValueLength(char *key, int *val);

	bool getValueLong(char *key, LONG_T *val);

	bool getValueULong(char *key, ULONG_T *val);

	bool getValueDouble(char *key, double *val);

	bool getValueInt(char *key, int *val);

	bool getValueUInt(char *key, unsigned int *val);

	bool getValueBool(char *key, bool *val);

	bangdb_json_data_type getValue(char *key, void **val, UINT_T *len);

	bangdb_json_data_type getNestedValueVA(void **name, UINT_T *l, char *obj, ...);

	bangdb_json_data_type getNestedValue(char *keys[], int nkeys, void **name, UINT_T *l);

	void createNewDoc();

	void addMemberNumber(char *key);

	void setMemberNumber(char *key, double val);

	void addMemberString(char *key);

	void setMemberString(char *key, char *val, bool copy=false);

	void addMember(char *key, char *val, bool copy=false);

	void addMember(char *key, double val);

	void addMember(char *key, LONG_T val);

	void addObject(char *key);

	void addObjectToObject(char *obj, char *key);

	void addKeyValueToObject(char *objname, char *key, char *val, bool copy=false);

	void addKeyToObject(char *objname, char *key);

	void setValueToObject(char *objname, char *key, char *val, bool copy=false);

	void addEmptyArray(char *key);

	void addEmptyArrayToObject(char *objname, char *arr);

	void pushToArray(char *arr, char *val, bool copy);

	void pushToArray(char *arr, double val);

	void pushArrayToObject(char *objname, char *arr, char *val, bool copy=false);

	void pushArrayToObject(char *objname, char *arr, double val);

	int getArrSize(char *arrname);

	int getArrSize(char *obj, char *arrname);

	const char *getString();

	char *getNewString();

	bangdb_json_data_type getType(char *keyName);

	bangdb_json_data_type getValueType(void *_value);

	bangdb_json_data_type getBaseType(char *keyName);

	bool hasMember(char *key);

	void print();

	virtual ~bangdb_json_parser();
private:
	bangdb_json_data_type _getValue(void *_value, void **val, UINT_T *len);

	char *json;
	void *json_item;
	friend struct json_object;
};

struct json_object : public iqjson_object
{
public:
	json_object(bangdb_json_data_type type, iqjson *bjp);

	void addMember(char *key, char *val, bool copy=false);

	void addMember(char *key, char *val, int vallen, bool copy=false);

	void addMember(char *key, double val);

	void putObject(char *name);

	void putObjectToObject(char *objname, char *obj);

	void putObjectToObjects(char *objname, char *obj, ...);

	void pushToArray(char *arr);

	void pushArrayToObject(char *arr, char *obj);

	void pushArrayToObjects(char *arrname, char *obj, ...);

	virtual ~json_object();

private:
	void *v;
	iqjson *_bjp;
};
}
#endif /* BANGDB_JSON_PARSER_H_ */

