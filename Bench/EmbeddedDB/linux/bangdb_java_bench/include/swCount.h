/*
 * swCount.h
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

#ifndef SWCOUNT_H_
#define SWCOUNT_H_

#include "hyperloglog.h"
#include "absoluteCount.h"
#include "light_lock.h"
#include "iqcount.h"

namespace bangdb
{

class swCount : public iqcount
{

public:
	swCount(int swTime, int swExpiry, bangdb_count_type countType);

	void add(const char *s, int len);

	int list(int span, int **count_list, int *size);

	LONG_T count();

	LONG_T count(int span);

	void foldSlots();

	void reset();

	void close();

	virtual ~swCount();

private:

	/* for multi slot add and single slot count - useful for continuous sliding window (ex: rightnow calc) */
	void _addsw(const char *s, int len);

	LONG_T _countsw();

	/* for simple one slot add and multi slot count ops - useful for slot wise computation*/
	//adds to a slot
	void _add(const char *s, int len);

	//counts for swTime (whole sliding window)
	LONG_T _count();

	//counts for given span less than swTime, span in sec
	LONG_T _count(int span);

	iqcountAlgo **_swTable;

	//total sliding window time
	int _swTime;

	int _swExpiry;

	int _nslots;

	long SW_COUNT_SLEEP_FREQ;

	//slots in the table, increases every min/sec (based on expriy)
	short _t;

	bool _first_round;

	light_spin_lock _lock;
};
}
#endif /* SWCOUNT_H_ */
