/*
 * bangdb_error_msg.h
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


#ifndef BANGDB_ERROR_MSG_H_
#define BANGDB_ERROR_MSG_H_

namespace bangdb
{
/* connection */
#define BANGDB_ERR_00_02_001 -51
#define BANGDB_ERR_00_02_002 -52
#define BANGDB_ERR_00_02_003 -53
#define BANGDB_ERR_00_02_004 -54
#define BANGDB_ERR_00_02_005 -55
#define BANGDB_ERR_00_02_006 -56
#define BANGDB_ERR_00_02_007 -57
#define BANGDB_ERR_00_02_008 -58
#define BANGDB_ERR_00_02_009 -59
#define BANGDB_ERR_00_02_010 -60
#define BANGDB_ERR_00_02_011 -61
#define BANGDB_ERR_00_02_012 -62
#define BANGDB_ERR_00_02_013 -63
#define BANGDB_ERR_00_02_014 -64
#define BANGDB_ERR_00_02_015 -65
#define BANGDB_ERR_00_02_016 -66
#define BANGDB_ERR_00_02_017 -67
#define BANGDB_ERR_00_02_018 -68

/* database */
#define BANGDB_ERR_00_00_001 -115
#define BANGDB_ERR_00_00_002 -116
#define BANGDB_ERR_00_00_003 -117
#define BANGDB_ERR_00_00_004 -118
#define BANGDB_ERR_00_00_005 -119
#define BANGDB_ERR_00_00_006 -120
#define BANGDB_ERR_00_00_007 -121
#define BANGDB_ERR_00_00_008 -122
#define BANGDB_ERR_00_00_009 -123
#define BANGDB_ERR_00_00_010 -124
#define BANGDB_ERR_00_00_011 -125
#define BANGDB_ERR_00_00_012 -126
#define BANGDB_ERR_00_00_013 -127
#define BANGDB_ERR_00_00_014 -128
#define BANGDB_ERR_00_00_015 -129
#define BANGDB_ERR_00_00_016 -130

/* table */
#define BANGDB_ERR_00_01_001 -240
#define BANGDB_ERR_00_01_002 -241
#define BANGDB_ERR_00_01_003 -242
#define BANGDB_ERR_00_01_004 -243
#define BANGDB_ERR_00_01_005 -244
#define BANGDB_ERR_00_01_006 -245
#define BANGDB_ERR_00_01_007 -246
#define BANGDB_ERR_00_01_008 -247
#define BANGDB_ERR_00_01_009 -248
#define BANGDB_ERR_00_01_010 -249
#define BANGDB_ERR_00_01_011 -250
#define BANGDB_ERR_00_01_012 -251
#define BANGDB_ERR_00_01_013 -252
#define BANGDB_ERR_00_01_014 -253
#define BANGDB_ERR_00_01_015 -254
#define BANGDB_ERR_00_01_016 -255
#define BANGDB_ERR_00_01_017 -256
#define BANGDB_ERR_00_01_018 -257
#define BANGDB_ERR_00_01_019 -258
#define BANGDB_ERR_00_01_020 -259
#define BANGDB_ERR_00_01_021 -260
#define BANGDB_ERR_00_01_022 -261

/* swEntityCount */
#define BANGDB_ERR_00_60_001 -300

/* swTable */
#define BANGDB_ERR_00_61_001 -400

/* swTableUnit */
#define BANGDB_ERR_00_62_001 -500

/* wideTable */
#define BANGDB_ERR_00_63_001 -600
#define BANGDB_ERR_00_63_002 -601
#define BANGDB_ERR_00_63_003 -602
#define BANGDB_ERR_00_63_004 -603
#define BANGDB_ERR_00_63_005 -604
#define BANGDB_ERR_00_63_006 -605
#define BANGDB_ERR_00_63_007 -606

/*  */
#define BANGDB_ERR_00_64_001 -720
#define BANGDB_ERR_00_64_002 -721

/* general */
#define BANGDB_ERR_OP_NOT_SUPPORTED	-2000


void bangdb_print_error(int errnum);

//ensure that no method is called before this
void bangdb_print_last_error();
}
#endif /* BANGDB_ERROR_MSG_H_ */
