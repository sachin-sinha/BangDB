/*
 * FDT.h
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

#ifndef FDT_H_
#define FDT_H_

#include "bangdb.h"

namespace bangdb
{
struct FDT
{
	FDT()
	{
		data = NULL;
		length = 0;
	}
	FDT(void *_data, DATLEN_T _len)
	{
		data = _data;
		length = _len;
	}

	void copy(FDT * v)
	{
		char *_v = new char[v->length];
		memcpy(_v, v->data, v->length);
		data = _v;
		length = v->length;
	}

	void free()
	{
		if(data != NULL && length > 0)
			delete[] (char*)data;
		data = NULL;
	}
	~FDT()
	{
	}

	DATLEN_T length;
	void *data;
};

const int fdt_size = sizeof(FDT);

struct DATA_VAR
{
	void *data_buf;		//the pointer to pre allocated buffer. for write db will read from it and for read db would write to it. User should clear the buffer
	int data_buf_len;	//the allocated buffer length (db doesn't touch this)
	int data_len;		//actual length of the read data (returned by db) or length of data to write to db (provided by user)
	int data_offt; 		//for write db takes the bytes from data_buf from the data_offt and for read db reads data in db from data_offt
						//data_offt + data_len <= data_buf_len, else data will be curtailed
	int flag;			//db sets if more data is to come for read(MORE_DATA_TO_READ)
	DATA_VAR()
	{
		reset();
	}
	void reset()
	{
		data_buf = 0;
		data_buf_len = data_len = data_offt = flag = 0;
	}
};

const int data_var_size = sizeof(DATA_VAR);
}
#endif /* FDT_H_ */
