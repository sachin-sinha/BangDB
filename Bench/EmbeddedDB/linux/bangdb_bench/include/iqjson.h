/*
 * iqjson.h
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

#ifndef IQJSON_H_
#define IQJSON_H_

#include "bangdb.h"
#include <iostream>

namespace bangdb
{

enum bangdb_json_data_type
{
	NULLTYPE = 0,
	FALSETYPE = 1,
	TRUETYPE = 2,
	OBJECTTYPE = 3,
	ARRAYTYPE = 4,
	STRINGTYPE = 5,
	NUMBERTYPE = 6,
	INTTYPE = 7,
	UINTTYPE = 8,
	LONGTYPE = 9,
	ULONGTYPE = 10,
	DOUBLETYPE = 11,
	BOOLTYPE = 12,
	INVALIDTYPE = 13,
};

class iqjson
{
public:
	virtual void reset() = 0;

	virtual void setJson(char *_json) = 0;

	virtual bool parseOutPlace(char *_json) = 0;

	virtual bool parseInPlace(char jbuf[]) = 0;

	virtual char* getValueString(char *key, int *len) = 0;

	virtual bool getValueLength(char *key, int *val) = 0;

	virtual bool getValueLong(char *key, LONG_T *val) = 0;

	virtual bool getValueULong(char *key, ULONG_T *val) = 0;

	virtual bool getValueDouble(char *key, double *val) = 0;

	virtual bool getValueInt(char *key, int *val) = 0;

	virtual bool getValueUInt(char *key, unsigned int *val) = 0;

	virtual bool getValueBool(char *key, bool *val) = 0;

	virtual bangdb_json_data_type getValue(char *key, void **val, UINT_T *len) = 0;

	virtual bangdb_json_data_type getNestedValueVA(void **name, UINT_T *l, char *obj, ...) = 0;

	virtual bangdb_json_data_type getNestedValue(char *keys[], int nkeys, void **name, UINT_T *l) = 0;

	virtual void createNewDoc() = 0;

	virtual void addMemberNumber(char *key) = 0;

	virtual void setMemberNumber(char *key, double val) = 0;

	virtual void addMemberString(char *key) = 0;

	virtual void setMemberString(char *key, char *val, bool copy=false) = 0;

	virtual void addMember(char *key, char *val, bool copy=false) = 0;

	virtual void addMember(char *key, double val) = 0;

	virtual void addMember(char *key, LONG_T val) = 0;

	virtual void addObject(char *key) = 0;

	virtual void addObjectToObject(char *obj, char *key) = 0;

	virtual void addKeyValueToObject(char *objname, char *key, char *val, bool copy=false) = 0;

	virtual void addKeyToObject(char *objname, char *key) = 0;

	virtual void setValueToObject(char *objname, char *key, char *val, bool copy=false) = 0;

	virtual void addEmptyArray(char *key) = 0;

	virtual void addEmptyArrayToObject(char *objname, char *key) = 0;

	//void* is Value
	//virtual void pushObjectToObject(char *obj1, void *obj2) = 0;

	virtual void pushToArray(char *arr, char *val, bool copy) = 0;

	virtual void pushToArray(char *arr, double val) = 0;

	virtual void pushArrayToObject(char *objname, char *arr, char *val, bool copy=false) = 0;

	virtual void pushArrayToObject(char *objname, char *arr, double val) = 0;

	virtual int getArrSize(char *arrname) = 0;

	virtual int getArrSize(char *obj, char *arrname) = 0;

	virtual const char *getString() = 0;

	virtual char *getNewString() = 0;

	virtual bangdb_json_data_type getType(char *keyName) = 0;

	virtual bangdb_json_data_type getValueType(void *_value) = 0;

	virtual bangdb_json_data_type getBaseType(char *keyName) = 0;

	virtual bool hasMember(char *key) = 0;

	virtual void print() = 0;

	virtual ~iqjson() { }
};

class iqjson_object
{
public:

	virtual void addMember(char *key, char *val, bool copy=false) = 0;

	virtual void addMember(char *key, char *val, int vallen, bool copy=false) = 0;

	virtual void addMember(char *key, double val) = 0;

	virtual void putObject(char *name) = 0;

	virtual void putObjectToObject(char *objname, char *obj) = 0;

	virtual void putObjectToObjects(char *objname, char *obj, ...) = 0;

	virtual void pushToArray(char *arr) = 0;

	virtual void pushArrayToObject(char *arr, char *obj) = 0;

	virtual void pushArrayToObjects(char *arrname, char *obj, ...) = 0;

	virtual ~iqjson_object() { }
};
}

#endif /* IQJSON_H_ */
