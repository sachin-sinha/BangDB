/*
 * bangdb_rtf_base.h
 *
 *  Created on: 16-Dec-2018
 *      Author: sachin
 */

#ifndef SRC_HEADERS_BANGDB_RTF_BASE_H_
#define SRC_HEADERS_BANGDB_RTF_BASE_H_

#include "basehdr.h"
#include "bangdb_json_parser.h"
//#include "bangdb_math_expressions.h"
#include <stdio.h>
#include <string.h>

namespace bangdb
{

struct bangdb_udf_val
{
	void *val;
	short len;				// length of val for string, long and double it's 8 or length of string. For array it's len of array
	short type;				// 5 string, 9 long, 11 double, 4 array of string, 3 custom object
	short out_to_del;		// out_to_del = 0 if not to be deleted, else 1
	short out_exp_type;		// expected type of o/p - 5 string, 9 long, 11 double, 4 array of string, 3 custom object
	bangdb_udf_val()
	{
		val = NULL;
		len = 0;
		type = 0;
		out_to_del = 0;
		out_exp_type = 0;
	}
	int serialize(char **out_buf);
	int deserialize(char *buf, int buf_len);
};

struct bangdb_udf_val_ret
{
	short len;
	short type;
	short out_to_del;
	short out_exp_type;
	void copy_from(bangdb_udf_val *v)
	{
		len = v->len;
		type = v->type;
		out_to_del = v->out_to_del;
		out_exp_type = v->out_exp_type;
	}
	void copy_to(bangdb_udf_val *v)
	{
		v->len = len;
		v->type = type;
		v->out_to_del = out_to_del;
		v->out_exp_type = out_exp_type;
	}
};

const int BANGDB_UDF_VAL_RET_SZ = sizeof(bangdb_udf_val_ret);

// this should match with the iqjson type
//type is defined by the iqjson as follows;
/*
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
*/
enum BANGDB_UDF_VAR_TYPE
{
	BANGDB_UDF_VAR_TYPE_LONG=9,
	BANGDB_UDF_VAR_TYPE_DOUBLE=11,
	BANGDB_UDF_VAR_TYPE_STRING=5,
	BANGDB_UDF_VAR_TYPE_ARRAY_LONG=14,
	BANGDB_UDF_VAR_TYPE_ARRAY_DOUBLE=15,
	BANGDB_UDF_VAR_TYPE_ARRAY_STRING=16,
	BANGDB_UDF_VAR_TYPE_CUSTOM_OBJECT=3,

	BANGDB_UDF_VAR_TYPE_INVALID=20
};

//base class for all the udf that should be implemented
class bangdb_rtf_base
{
protected:
    double m_input;     // some data or use a pointer to a larger input object
public:
    virtual void *f(int argc, void* argv[]) = 0;	//must be implemented as this is only way to interact with rtf at run time

    //few already implemented func
    virtual double f(double x)
    {
    	return m_input*x;
    }
    virtual double f(double a, double b)
    {
    	return a + b;
    }
    virtual double mul(double a, double b)
    {
    	return a*b;
    }
    void init(double input) { m_input=input; }

    virtual ~bangdb_rtf_base() {};

    static void *double_ptr(double &d)
    {
    	double* pd = &d;
    	void** p = (void**)pd;
    	void* dp = *p ;
    	//void *val = dp;
    	return dp;//val;
    }

    static double get_double(void *val)
    {
    	double *d = (double*)((void*)&val);
    	return *d;
    }

    static void *long_ptr(long &d)
    {
    	long* pd = &d;
    	void** p = (void**)pd;
    	void* dp = *p ;
    	//void *val = dp;
    	return dp;//val;
    }

    static long get_long(void *val)
    {
    	long *d = (long*)((void*)&val);
    	return *d;
    }
};

}


#endif /* SRC_HEADERS_BANGDB_RTF_BASE_H_ */
