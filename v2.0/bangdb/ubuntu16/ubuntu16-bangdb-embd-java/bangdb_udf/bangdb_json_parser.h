/*
 * bangdb_json_parser.h
 *
 *  Created on: 23-Mar-2014
 *      Author: sachin
 */

#ifndef BANGDB_JSON_PARSER_H_
#define BANGDB_JSON_PARSER_H_

#include "iqjson.h"
//#include "array_list.h"

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

	bool parseOutPlaceSelf();

	bool parseInPlace(char jbuf[]);

	char* getValueString(const char *key, int *len);

	bool getValueLength(char *key, int *val);

	bool getValueLong(const char *key, long *val);

	bool getValueULong(char *key, unsigned long *val);

	bool getValueDouble(char *key, double *val);

	bool getValueInt(char *key, int *val);

	bool getValueUInt(char *key, unsigned int *val);

	bool getValueBool(char *key, bool *val);

	const char *getKey(void *obj);
	
	int getArraySize(void *arr);

	int getSize();
	
	void *getFirstObject();

	bangdb_json_data_type getElementType(void *e);
	
	void setNumberArrayElement(void *arr, int idx, char *key, long val);
	
	void addNumberArrayElement(char *arr, int idx, char *key, long val);
	
	void addStringArrayElement(char *arr, int idx, char *key, char* val, bool copy=false);
	
	void removeMemberFromArrayElement(char *arr, int idx, char *key);

	void getArrayElement(void *arr, int idx, const char *key , query_value *jval);

	void getObjectElement(void *obj, char *key, query_value *jval);

	bangdb_json_data_type getValue(const char *key, void **val, unsigned int *len);

	bangdb_json_data_type getValue(const char *key, void **val, long *len);

	void getValue(char *key, query_value *jval);

	void getValue_rtf(char *key, query_value *jval);

	bangdb_json_data_type getNestedValueVA(void **name, unsigned int *l, char *obj, ...);

	bangdb_json_data_type getNestedValue(char *keys[], int nkeys, void **name, unsigned int *l);

	void getNestedValue(char *keys[], int nkeys, query_value *jval);

	bangdb_json_data_type getNestedValue(char *keys[], int nkeys, void **name, long *l);

	bangdb_json_data_type getNestedValueDVA(void **name, unsigned int *l, int depth, ...);

	bangdb_json_data_type getNestedValueD(void **name, unsigned int *l, int depth, void* path[]);

	bangdb_json_data_type getNestedValueValDVA(void *_value, void **name, unsigned int *l, int depth, ...);

	bangdb_json_data_type getNestedValueValD(void *_value, void **name, unsigned int *l, int depth, void* path[]);

	bangdb_json_data_type getNestedValueAllType(char *keys[], int keys_idx[], int nkeys, void **name, unsigned int *l);

	bangdb_json_data_type getValue(void *_value, void **val, unsigned int *len);

	void createNewDoc();

	bool isEmptyDoc();

	void addMemberNumber(char *key);

	void setMemberNumber(char *key, long val);
	
	void setMemberNumber(char *key, double val);

	void addMemberString(char *key);

	void addMemberString(char *key, int klen, bool copy);

	void setMemberString(char *key, char *val, bool copy=false);

	void setMemberString_givenWidthLong(char *key, long val, int width, bool copy=false);

	void addMember(char *key, char *val, bool copy=false);

	void addMember(char *key, int klen, bool copy_key, char *val, int vlen, bool copy_val);

	void addMemberString_givenWidthLong(char *key, long val, int width, bool copy=false);

	void addMember(char *key, double val);

	void addMember(char *key, long val);

	void addMember(char *key, unsigned long val);

	void addMember(char *key, void *object);


	void addMember(char *key, int klen, bool copy_key, double val);

	void addMember(char *key, int klen, bool copy_key, long val);

	void addMember(char *key, int klen, bool copy_key, unsigned long val);

	void addMember(char *key, int klen, bool copy_key, void *object);


	void removeMember(char *key);
	
	void removeMemberFromObject(char *objname, char *key);
	
	void addObject(char *key);

	void addObjectToObject(char *obj, char *key);

	void* getArrayMember(char *arr, char *val, int vallen);

	void addObjectToArray(char *arr, void *obj);

	void delObjectFromArray(char *arr, int i);

	void addKeyValueToObject(char *objname, char *key, char *val, bool copy=false);

	void addKeyValueToObject(char *objname, char *key, long val);

	void addKeyValueToObject(char *objname, char *key, double val);

	void addKeyValueToObject(char *objname, char *key, bool val);

	void addKeyToObject(char *objname, char *key);

	void setValueToObject(char *objname, char *key, char *val, bool copy=false);

	void insertOrUpdateKeyValueToObject(char* objname, char* key, long val);

	void addEmptyArray(char *key);

	void addEmptyArrayToObject(char *objname, char *arr);

	void addEmptyArrayToArray(char *arr);

	//void* is Value
	//void pushObjectToObject(char *obj1, void *obj2);

	void pushToArray(char *arr, char *val, bool copy);

	void pushToArray(char *arr, double val);

	void pushToArray(char *arr, long val);

	void pushArrayToObject(char *objname, char *arr, char *val, bool copy=false);

	void pushArrayToObject(char *objname, char *arr, double val);

	void pushToSubArray(char *arr, long val, int index);

	void pushToSubArray(char *arr, const char* val, int index);

	int getArrSize(char *arrname);

	int getArrSize(char *obj, char *arrname);

	const char *getString();

	const char *getString(void *val_arr);

	const char *getString(void *val_arr, int idx);

	const char *getObjString(void *obj);

	char *getNewString();

	bangdb_json_data_type getType(const char *keyName);

	bangdb_json_data_type getValueType(void *_value);

	bangdb_json_data_type getBaseType(char *keyName);

	bool hasMember(char *key);

	void *getJsonItem();

	void print();

	void print(void *val);

	void print(void *val_arr, int idx);

    bool IsRootJson();


    //iterator for json object
    void *get_itr();

    bool has_next(void **itr);

    void move_next(void **itr);

   // bool has_next(void *itr);

    void move_next(void **itr, int i);

    char *get_name(void *itr, int *len);

    void get_val(void *itr, bangdb_json_data_type dt, query_value *qv);

    bangdb_json_data_type get_val(void *itr, query_value *qv);

	virtual ~bangdb_json_parser();
private:
	bangdb_json_data_type _getValue(void *_value, void **val, unsigned int *len);

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

	void addMember(char *key, int klen, bool copy_key, char *val, int vlen, bool copy_val);

	void addMember(char *key, double val);

	void addMember(char *key, long val);

	void addMemberBool(char *key, bool val);
	
	void addEmptyObject(char *key);

	void removeMember(char *key);

	void pushArrayInToObject(char *objname, char* key);

#ifdef _MAC_OS_COMPILE_
	//just for compile under mac
	void addMember(char *key, long val);
#endif
	void addEmptyArray(char *key);

	void putObject(char *name);

	void putObjectToObject(char *objname, char *obj);

	void putObjectToObjects(char *objname, char *obj, ...);

	void pushObjectToObject(json_object* pjobj, char *objname);

	void pushToArray(char *arr);

	void pushInToArray(char *arr, json_object* tv);

	void pushInToArray(char *arr, char* val, int vallen, bool copy);

	bool hasArrayMember(char *arr, char *val, int vallen);

	void pushInToArray(char *arr, long val);

	void pushInToObjectArray(char* objname, char *arr, char* val, int vallen, bool copy);

	void pushArrayToObject(char *arr, char *obj);

	void pushArrayToObjects(char *arrname, char *obj, ...);

	const char* getString();

	virtual ~json_object();

private:
	void *v;
	iqjson *_bjp;
};

struct query_value
{
	query_value()
	{
		reset();
	}
	query_value(void *v, unsigned int l, bangdb_json_data_type dtype)
	{
		val = v;
		len = l;
		dt = dtype;
		nf = false;
	}
	bangdb_json_data_type getType()
	{
		return dt;
	}
	int getLength()
	{
		return (unsigned int)len;
	}
	const char *getValStr()
	{
		return (const char*)val;
	}
	long getValLong()
	{
		return (long)(val);
	}
	bool getValBool()
	{
		return (bool)(val);
	}
	double getValDouble()
	{
		/*
		long l = (long)val;
		return conv_long_to_dbl(l);
		*/

		double *d = (double*)((void*)&val);
		return *d;
	}
	void *getVal()
	{
		return val;
	}
	bool isValNull()
	{
		return val ? false : true;
	}
	void reset()
	{
		val = NULL;
		len = 0;
		nf = false;
		dt = INVALIDTYPE;
	}
	void set(void *v, unsigned int l, bangdb_json_data_type dtype, bool copy = false)
	{
		if (copy)
		{
			val = (void*)calloc (1,l);
			memcpy (val, v, l);
			nf = true;
		}
		else
		{
			val = v;
			nf = false;
		}
		len = l;
		dt = dtype;
	}
	void set(double d, unsigned int l, bangdb_json_data_type dtype)
	{
		/*
		long ld = conv_dbl_to_long(d);
		val = (void*)&ld;
		*/

		double* pd = &d;
		void** p = (void**)pd;
		void* dp = *p ;
		val = dp;

		len = l;
		dt = dtype;
		nf = false;
	}
	void set(long lv, unsigned int l, bangdb_json_data_type dtype)
	{
		val = (void*)lv;
		len = l;
		dt = dtype;
		nf = false;
	}
	void reset2()
	{
		if (nf)
		{
			free (val);
		}
		val = NULL;
		len = 0;
	}
private:
	void *val;
	unsigned int len;
	bangdb_json_data_type dt;
	bool nf;		// need to free memory on reset or delete.
	friend class bangdb_json_parser;
};

bool isqvlongType(query_value *qv);
bool isqvfixedType(query_value *qv);
bool isqvlongType(bangdb_json_data_type dt);
bool isqvfixedType(bangdb_json_data_type dt);
bool _get_int_type(bangdb_json_data_type tp);
bool _get_double_type(bangdb_json_data_type tp);
}
#endif /* BANGDB_JSON_PARSER_H_ */

