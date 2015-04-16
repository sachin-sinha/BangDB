/*
 * timestamp.h
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

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include "basehdr.h"

namespace bangdb
{

namespace bangdb_timestamp_var
{
	extern atomic64_t LAST_TIME_MicroSec;
	extern atomic64_t LAST_TIME_MilliSec;
}
using namespace bangdb_timestamp_var;

ULONG_T getCurrentTimeMicroSec();

ULONG_T getCurrentTimeMilliSec();

ULONG_T uniqueTimeStampMicroSec();

ULONG_T uniqueTimeStampMilliSec();

ULONG_T subTimeMicroSec(ULONG_T curTimeMicroSec, long nsec);

ULONG_T subTimeMilliSec(ULONG_T curTimeMilliSec, long nsec);

ULONG_T addTimeMicroSec(ULONG_T curTimeMicroSec, long nsec);

ULONG_T addTimeMilliSec(ULONG_T curTimeMilliSec, long nsec);

ULONG_T getCurrentTime();

ULONG_T subTime(long nsec);

ULONG_T addTime(long nsec);

ULONG_T uniqueTimeStamp();

ULONG_T convertTimeUnit(long nsec);

ULONG_T getLagTime(ULONG_T from_time);
}
#endif /* TIMESTAMP_H_ */
