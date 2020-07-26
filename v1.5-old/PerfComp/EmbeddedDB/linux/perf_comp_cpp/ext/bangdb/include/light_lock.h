/*
 * light_lock.h
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

#ifndef LIGHT_LOCK_H_
#define LIGHT_LOCK_H_

#include "basehdr.h"

namespace bangdb
{
class light_mutex_cond_lock
{
public:
	light_mutex_cond_lock()
	{
		Pthread_mutex_init_private(&_lock);
		Pthread_cond_init_private(&_cond);
		_wakeup = false;
		_state = 0;
	}
	void lock()
	{
		Pthread_mutex_lock(&_lock);
	}
	void unlock()
	{
		Pthread_mutex_unlock(&_lock);
	}
	void wait()
	{
		Pthread_cond_wait(&_cond, &_lock);
	}
	void signal()
	{
		Pthread_cond_signal(&_cond);
	}
	void broadcast()
	{
		Pthread_cond_broadcast(&_cond);
	}
	void wakeup()
	{
		_wakeup = true;
	}
	void sleep()
	{
		_wakeup = false;
	}
	bool isAwake()
	{
		return _wakeup;
	}
	bool isAsleep()
	{
		return !_wakeup;
	}
	void setState(SHORT_T state)
	{
		_state = state;
	}
	SHORT_T getState()
	{
		return _state;
	}
	~light_mutex_cond_lock()
	{
		Pthread_mutex_destroy(&_lock);
		Pthread_cond_destroy(&_cond);
	}
private:
	pthread_mutex_t _lock;
	pthread_cond_t _cond;
	bool _wakeup;
	SHORT_T _state;
};

class light_mutex_lock
{
public:
	light_mutex_lock()
	{
		Pthread_mutex_init_private(&_lock);
	}
	void lock()
	{
		Pthread_mutex_lock(&_lock);
	}
	void unlock()
	{
		Pthread_mutex_unlock(&_lock);
	}
	~light_mutex_lock()
	{
		Pthread_mutex_destroy(&_lock);
	}
private:
	pthread_mutex_t _lock;
};

class light_spin_lock
{
public:
	light_spin_lock()
	{
		Pthread_spin_init(&_lock, PTHREAD_PROCESS_PRIVATE);
	}
	void lock()
	{
		Pthread_spin_lock(&_lock);
	}
	void unlock()
	{
		Pthread_spin_unlock(&_lock);
	}
	~light_spin_lock()
	{
		Pthread_spin_destroy(&_lock);
	}
private:
	pthread_spinlock_t _lock;
};

class light_rw_lock
{
public:
	light_rw_lock()
	{
		Pthread_rwlock_init_private(&_lock);
	}
	void readlock()
	{
		Pthread_rwlock_rdlock(&_lock);
	}
	void writelock()
	{
		Pthread_rwlock_wrlock(&_lock);
	}
	void unlock()
	{
		Pthread_rwlock_unlock(&_lock);
	}
	~light_rw_lock()
	{
		Pthread_rwlock_destroy(&_lock);
	}
private:
	pthread_rwlock_t _lock;
};
}
#endif /* LIGHT_LOCK_H_ */
