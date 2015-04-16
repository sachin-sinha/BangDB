/*
 * atomic.h
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

#ifndef ATOMIC_H_
#define ATOMIC_H_

namespace bangdb
{

//Atomic type.
typedef struct {

    volatile int counter;

} atomic_t;


#define ATOMIC_INIT(i)  { (i) }

/**

 * Read atomic variable

 * @param v pointer of type atomic_t

 * Atomically reads the value of @v.

 */

#define atomic_read(v) ((v)->counter)

/**

 * Set atomic variable

 * @param v pointer of type atomic_t

 * @param i required value

 */

#define atomic_set(v,i) (((v)->counter) = (i))

/**

 * Add to the atomic variable

 * @param i integer value to add

 * @param v pointer of type atomic_t

 */

static inline void atomic_add( int i, atomic_t *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}

/**

 * Subtract the atomic variable

 * @param i integer value to subtract

 * @param v pointer of type atomic_t

 *

 * Atomically subtracts @i from @v.

 */

static inline void atomic_sub( int i, atomic_t *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

/**

 * Subtract value from variable and test result

 * @param i integer value to subtract

 * @param v pointer of type atomic_t

 * Atomically subtracts @i from @v and returns

 * true if the result is zero, or false for all

 * other cases.

 */

static inline int atomic_sub_and_test( int i, atomic_t *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

/**

 * Increment atomic variable

 * @param v pointer of type atomic_t

 * Atomically increments @v by 1.

 */

static inline void atomic_inc( atomic_t *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}


//get and then add, returns old value
static inline int atomic_get_inc(atomic_t *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

//returns new value
static inline int atomic_inc_get(atomic_t *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

/**

 * @brief decrement atomic variable

 * @param v: pointer of type atomic_t

 * Atomically decrements @v by 1.  Note that the guaranteed

 * useful range of an atomic_t is only 24 bits.

 */

static inline void atomic_dec( atomic_t *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

static inline int atomic_get_dec( atomic_t *v )
{
      return __sync_fetch_and_sub(&v->counter, 1);
}

static inline int atomic_dec_get( atomic_t *v )
{
      return __sync_sub_and_fetch(&v->counter, 1);
}

/**

 * @brief Decrement and test

 * @param v pointer of type atomic_t

 * Atomically decrements @v by 1 and

 * returns true if the result is 0, or false for all other

 * cases.

 */
static inline int atomic_dec_and_test( atomic_t *v )
{

       return !(__sync_sub_and_fetch(&v->counter, 1));
}

/**

 * @brief Increment and test

 * @param v pointer of type atomic_t

 * Atomically increments @v by 1

 * and returns true if the result is zero, or false for all

 * other cases.

 */
static inline int atomic_inc_and_test( atomic_t *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

/**

 * @brief add and test if negative

 * @param v pointer of type atomic_t

 * @param i integer value to add

 * Atomically adds @i to @v and returns true

 * if the result is negative, or false when

 * result is greater than or equal to zero.

 */
static inline int atomic_add_negative( int i, atomic_t *v )
{
       return (__sync_add_and_fetch(&v->counter, i) < 0);
}
/* for 64 bit, basically architecture independent but for long long type as well
 * can be used for int or long long based on the _FILE_OFFSET_BITS defined as compiler option
 */

static inline bool atomic_compare_and_swap( atomic_t *p, int oldVal, int newVal)
{
	return __sync_bool_compare_and_swap(&p->counter, oldVal, newVal);
}

/**

 * Atomic type.

 */
typedef struct {

    volatile off_t counter;

} atomic_FILEOFF_T;

#define ATOMIC_FILEOFF_T_INIT(i)  { (i) }

/**

 * Read atomic variable

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically reads the value of @v.

 */
#define atomic_FILEOFF_T_read(v) ((v)->counter)

/**

 * Set atomic variable

 * @param v pointer of type atomic_FILEOFF_T

 * @param i required value

 */
#define atomic_FILEOFF_T_set(v,i) (((v)->counter) = (i))

/**

 * Add to the atomic variable

 * @param i integer value to add

 * @param v pointer of type atomic_FILEOFF_T

 */
static inline void atomic_FILEOFF_T_add( off_t i, atomic_FILEOFF_T *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}

/**

 * Subtract the atomic variable

 * @param i integer value to subtract

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically subtracts @i from @v.

 */
static inline void atomic_FILEOFF_T_sub( off_t i, atomic_FILEOFF_T *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

/**

 * Subtract value from variable and test result

 * @param i integer value to subtract

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically subtracts @i from @v and returns

 * true if the result is zero, or false for all

 * other cases.

 */
static inline off_t atomic_FILEOFF_T_sub_and_test( off_t i, atomic_FILEOFF_T *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

/**

 * Increment atomic variable

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically increments @v by 1.

 */
static inline void atomic_FILEOFF_T_inc( atomic_FILEOFF_T *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}

//incr; get and then add, returns old value
static inline off_t atomic_FILEOFF_T_get_inc(atomic_FILEOFF_T *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

//incr; returns new value
static inline off_t atomic_FILEOFF_T_inc_get(atomic_FILEOFF_T *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

//add x; get and then add, returns old value
static inline off_t atomic_FILEOFF_T_get_add(atomic_FILEOFF_T *v, int x)
{
	return __sync_fetch_and_add(&v->counter, x);
}

//add x; returns new value
static inline off_t atomic_FILEOFF_T_add_get(atomic_FILEOFF_T *v, int x)
{
	return __sync_add_and_fetch(&v->counter, x);
}

/**

 * @brief decrement atomic variable

 * @param v: pointer of type atomic_FILEOFF_T

 * Atomically decrements @v by 1.  Note that the guaranteed

 * useful range of an atomic_FILEOFF_T is only 24 bits.

 */
static inline void atomic_FILEOFF_T_dec( atomic_FILEOFF_T *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

/**

 * @brief Decrement and test

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically decrements @v by 1 and

 * returns true if the result is 0, or false for all other

 * cases.

 */
static inline off_t atomic_FILEOFF_T_dec_and_test( atomic_FILEOFF_T *v )
{
       return !(__sync_sub_and_fetch(&v->counter, 1));
}

/**

 * @brief Increment and test

 * @param v pointer of type atomic_FILEOFF_T

 * Atomically increments @v by 1

 * and returns true if the result is zero, or false for all

 * other cases.

 */
static inline off_t atomic_FILEOFF_T_inc_and_test( atomic_FILEOFF_T *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

/**

 * @brief add and test if negative

 * @param v pointer of type atomic_FILEOFF_T

 * @param i integer value to add

 * Atomically adds @i to @v and returns true

 * if the result is negative, or false when

 * result is greater than or equal to zero.

 */

static inline off_t atomic_FILEOFF_T_add_negative( int i, atomic_t *v )

{

       return (__sync_add_and_fetch(&v->counter, i) < 0);

}

static inline bool atomic_FILEOFF_T_compare_and_swap( atomic_FILEOFF_T *p, off_t oldVal, off_t newVal)
{
	return __sync_bool_compare_and_swap(&p->counter, oldVal, newVal);
}

/* explicitly for long long type
 * 64 bit type
 */

/**

 * Atomic type.

 */


typedef struct {

    volatile long long counter;

} atomic64_t;

#define ATOMIC64_INIT(i)  { (i) }

/**

 * Read atomic variable

 * @param v pointer of type atomic64_t

 * Atomically reads the value of @v.

 */
#define atomic64_read(v) ((v)->counter)

/**

 * Set atomic variable

 * @param v pointer of type atomic64_t

 * @param i required value

 */
#define atomic64_set(v,i) (((v)->counter) = (i))

/**

 * Add to the atomic variable

 * @param i integer value to add

 * @param v pointer of type atomic64_t

 */
static inline void atomic64_add( int i, atomic64_t *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}



/**

 * Subtract the atomic variable

 * @param i integer value to subtract

 * @param v pointer of type atomic64_t

 *

 * Atomically subtracts @i from @v.

 */

static inline void atomic64_sub( int i, atomic64_t *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

/**

 * Subtract value from variable and test result

 * @param i integer value to subtract

 * @param v pointer of type atomic64_t

 *

 * Atomically subtracts @i from @v and returns

 * true if the result is zero, or false for all

 * other cases.

 */
static inline int atomic64_sub_and_test( int i, atomic64_t *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

/**

 * Increment atomic variable

 * @param v pointer of type atomic64_t

 *

 * Atomically increments @v by 1.

 */
static inline void atomic64_inc( atomic64_t *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}

//get and then add, returns old value
static inline long long atomic64_get_inc(atomic64_t *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

//returns new value
static inline long long atomic64_inc_get(atomic64_t *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

/**

 * @brief decrement atomic variable

 * @param v: pointer of type atomic64_t

 *

 * Atomically decrements @v by 1.  Note that the guaranteed

 * useful range of an atomic_t is only 24 bits.__sync_fetch_and_sub

 */
static inline void atomic64_dec( atomic64_t *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

/**

 * @brief Decrement and test

 * @param v pointer of type atomic64_t

 *

 * Atomically decrements @v by 1 and

 * returns true if the result is 0, or false for all other

 * cases.

 */
static inline int atomic64_dec_and_test( atomic64_t *v )
{
       return !(__sync_sub_and_fetch(&v->counter, 1));
}

/**

 * @brief Increment and test

 * @param v pointer of type atomic64_t

 *

 * Atomically increments @v by 1

 * and returns true if the result is zero, or false for all

 * other cases.

 */
static inline int atomic64_inc_and_test( atomic64_t *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

/**

 * @brief add and test if negative

 * @param v pointer of type atomic64_t

 * @param i integer value to add

 *

 * Atomically adds @i to @v and returns true

 * if the result is negative, or false when

 * result is greater than or equal to zero.

 */

static inline int atomic64_add_negative( int64_t i, atomic64_t *v )
{
       return (__sync_add_and_fetch(&v->counter, i) < 0);
}

static inline bool atomic64_compare_and_swap( atomic64_t *p, long long oldVal, long long newVal)
{
	return __sync_bool_compare_and_swap(&p->counter, oldVal, newVal);
}

}
#endif /* ATOMIC_H_ */
