/*
 * iqueue_dynamic.h
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

#ifndef IQUEUE_DYNAMIC_H_
#define IQUEUE_DYNAMIC_H_
#include "bangdb.h"

#ifndef DYNAMIC_QUEUE
#define DYNAMIC_QUEUE
#endif

namespace bangdb
{

template <class T>
class iqueue_dynamic
{
public:
	//construct the eventqueue, whether queue is shared or not
	iqueue_dynamic(char *_name, bool shared);

	//init the queue with initial queuesize, it should be a good guess for better performance
	void init(int queuesize);

	//put item in the queue, put item in queue, will get node(beg) from free list and add to q(beg)
	void put(T x);

	//this is non blocking version of put
	void try_put(T x);

	//get item from the queue, remove item from queue, will get the data(tail) and the put the node in free list(beg)
	T get();

	//moitor the queue for it's backlog
	void monitorq();

	//discard queue
	void closequeue();

	//signal to shutdown
	void willshutdown();

	//get num of items in the queue at the moment
	int getqueuednum();

	//get the num of items in the fl at the moment
	int getflnum();

	char* queuename();

	//the destructor
	~iqueue_dynamic();

private:

#ifdef DYNAMIC_QUEUE
	//if needed grow the queue, in case running out of free item node
	int _growqueue();

	//if too many free nodes, free memory, should happen once a threshold is reached, ideally
	int _shrinkqueue();

	//the individual item on the queue, as queue is a link list
	struct item
	{
		T data;
		item *next;
		item *prev;
		item(T x)
		{
			data = x;
			next = prev = NULL;
		}
		~item()
		{
			next = prev = NULL;
			//note that the data is not deleted. This is because after get the data has been returned to the caller
			//and the item has been removed from the queue and attached to the free list
		}
	};

	//the free list for the queue, note the first node is the dummy node
	//all nodes/items will be in free list initially
	item *fl;

	//the tail of the queue for instant removal for get
	item *tail;

	//the queue, note the first node is the dummy node, items added on the head for put
	item *q;
#else

	T *q;

	int N;

	int head;

	int tail;
#endif

	//name of the queue
	char *name;

	//is the queue shared with multiprocesses
	bool isshared;

	//size of the queue, in terms of total number of items that can be in the queue
	int qsize;

	//the current number of item in the fl
	int numitem_fl;

	//the current number of item in the q
	int numitem_q;

	//flag to check if the queue is closed
	bool closed;

	//flag to indicate the queue is going down
	bool queuegoingdown;

	//the mutex to lock queue
	pthread_mutex_t q_lock;

	//the condition var to notify all the sleeping thread if there is an item added in the queue
	pthread_cond_t q_cond;

	//the mutex to lock free list
	pthread_mutex_t fl_lock;

	//the condition var to notify all the sleeping thread if there is an item added in the freelist
	pthread_cond_t fl_cond;
};

template <class T>
iqueue_dynamic<T>::iqueue_dynamic(char *_name, bool shared)
{
	if(!(name = Strncpy(name, _name)))
		err_sys("iqueue_dynamic::iqueue_dynamic error in strncpy");

	isshared = shared;
	qsize = 0;
	numitem_fl = 0;
	numitem_q = 0;
	closed = false;
	queuegoingdown = false;

#ifdef DYNAMIC_QUEUE
	fl = new item(NULL);
	q = new item(NULL);
	tail = NULL;
#else
	q = NULL;
	N = 0;
	head = tail = 0;
#endif

	pthread_mutexattr_t mattr;
	pthread_condattr_t cattr;

	//init for queue
	Pthread_mutexattr_init(&mattr);
	if(shared)
		Pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_PRIVATE);
	Pthread_mutex_init(&q_lock, &mattr);
	Pthread_mutexattr_destroy(&mattr);

	Pthread_condattr_init(&cattr);
	if(shared)
		Pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_PRIVATE);
	Pthread_cond_init(&q_cond, &cattr);
	Pthread_condattr_destroy(&cattr);

	//init for free list
	Pthread_mutexattr_init(&mattr);
	if(shared)
		Pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_PRIVATE);
	Pthread_mutex_init(&fl_lock, &mattr);
	Pthread_mutexattr_destroy(&mattr);

	Pthread_condattr_init(&cattr);
	if(shared)
		Pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_PRIVATE);
	Pthread_cond_init(&fl_cond, &cattr);
	Pthread_condattr_destroy(&cattr);
}

template <class T>
iqueue_dynamic<T>::~iqueue_dynamic()
{
	//err_ret("destroy iqueue_dynamic starting...");
	if(!closed)
		closequeue();

	delete[] name;
	Pthread_mutex_destroy(&q_lock);
	Pthread_cond_destroy(&q_cond);
	Pthread_mutex_destroy(&fl_lock);
	Pthread_cond_destroy(&fl_cond);
}

template <class T>
void iqueue_dynamic<T>::willshutdown()
{
	queuegoingdown = true;
	int old_numq, old_numfl;
	old_numq = numitem_q;
	old_numfl = numitem_fl;
	numitem_q = numitem_fl = 1;
	int count = 0;
	while(true)
	{
		if(count >= MAX_THREADS) break;
		//note that the cond var is being used to wake up all threads with the queuegoingdown as true so that threads can stop poll on queue and return
		Pthread_cond_broadcast(&fl_cond);
		Pthread_cond_broadcast(&q_cond);
		sleep_us(10);
		count++;
	}
	numitem_q = old_numq;
	numitem_fl = old_numfl;
}

template <class T>
void iqueue_dynamic<T>::closequeue()
{
	//printf("closequeue started\n");
#ifdef DYNAMIC_QUEUE
	item *t;

	for(int i = 0; i<numitem_fl; i++)
	{
		t = fl->next;
		fl->next = t->next;
		delete t;
	}
	for(int i = 0; i<numitem_q; i++)
	{
		t = q->next;
		q->next = t->next;
		delete t;
	}
	delete fl;
	delete q;
	/*
	while(fl != NULL)
	{
		t = fl;
		fl = fl->next;
		delete t;
	}

	while(q != NULL)
	{
		t = q;
		q = q->next;
		delete t;
	}
	*/
#else
	delete[] q;
	//printf("queue deleted\n");
#endif
	closed = true;
	//err_ret("closequeue done");
}

template <class T>
void iqueue_dynamic<T>::init(int queuesize)
{
#ifdef DYNAMIC_QUEUE
	//add only in free list
	for(int i = 0; i<queuesize; i++)
	{
		item *t = new item(NULL);
		if(fl->next != NULL)
			fl->next->prev = t;
		t->next = fl->next;
		t->prev = fl;
		fl->next = t;
		qsize++;
		numitem_fl++;
	}
#else
	qsize = queuesize;
	N = qsize + 1;
	head = N;
	tail = 0;
	q = new T[N];
	numitem_fl = qsize;
#endif
}
#ifdef DYNAMIC_QUEUE
template <class T>
T iqueue_dynamic<T>::get()
{
	Pthread_mutex_lock(&q_lock);

	while(numitem_q == 0)
		Pthread_cond_wait(&q_cond, &q_lock);

	if(queuegoingdown)
	{
		Pthread_mutex_unlock(&q_lock);
		//Pthread_cancel(pthread_self());
		return NULL;
	}

#ifdef DEBUG_MODE
	printf("trying to get\n");
	if(tail == NULL)
		err_ret("tail NULL error");
#endif

	//remove from queue tail
	T x = tail->data;
	item *t = tail;
	if(tail->prev != q)
	{
		tail = tail->prev;
		tail->next = NULL;
	}
	else
		tail = NULL;
	t->next = t->prev = NULL;
	numitem_q--;

	Pthread_mutex_unlock(&q_lock);

	Pthread_mutex_lock(&fl_lock);

	//add to fl beg
	if(fl->next != NULL)
		fl->next->prev = t;
	t->next = fl->next;
	t->prev = fl;
	fl->next = t;
	numitem_fl++;

	if(numitem_fl == 1)
		Pthread_cond_broadcast(&fl_cond);

#ifdef DEBUG_MODE
	printf("get complete\n");
#endif

	Pthread_mutex_unlock(&fl_lock);

	return x;
}

template <class T>
void iqueue_dynamic<T>::put(T x)
{
	Pthread_mutex_lock(&fl_lock);

	while(numitem_fl == 0)
		Pthread_cond_wait(&fl_cond, &fl_lock);

	if(queuegoingdown)
	{
		//printf("thread %d will go down\n", (int)pthread_self());
		Pthread_mutex_unlock(&fl_lock);
		//Pthread_cancel(pthread_self());
		return;
	}

#ifdef DEBUG_MODE
	printf("trying to insert\n");
#endif

	//remove from beg of fl
	item *t = fl->next;
	fl->next = t->next;
	if(t->next != NULL)
		t->next->prev = fl;
	t->next = t->prev = NULL;
	numitem_fl--;

	Pthread_mutex_unlock(&fl_lock);

	Pthread_mutex_lock(&q_lock);
	//add to beg of q
	t->data = x;
	if(q->next != NULL)
		q->next->prev = t;
	t->next = q->next;
	t->prev = q;
	q->next = t;
	if(tail == NULL)
		tail = t;
	numitem_q++;

	if(numitem_q == 1)
		Pthread_cond_broadcast(&q_cond);

#ifdef DEBUG_MODE
	printf("inserted item\n");
#endif

	Pthread_mutex_unlock(&q_lock);
}
#else
//remove from q and add the empty item to fl
template <class T>
T iqueue<T>::get()
{
	Pthread_mutex_lock(&q_lock);

	while(numitem_q == 0) //queue is empty
		Pthread_cond_wait(&q_cond, &q_lock);

	if(queuegoingdown)
	{
		Pthread_mutex_unlock(&q_lock);
		//Pthread_cancel(pthread_self());
		return -1;
	}

	head = head % N;
	T x = q[head++];
	numitem_q--;
	numitem_fl++;

	if(numitem_fl == 1)
		Pthread_cond_broadcast(&fl_cond);

	//printf("poped = %d --]\n", x);
	Pthread_mutex_unlock(&q_lock);

	return x;
}

//remove from fl and add to q
template <class T>
void iqueue<T>::try_put(T x)
{
	if(Pthread_mutex_trylock(&q_lock) == -1)
		return;

	/*
	while(numitem_fl == 0)	//queue is full
		Pthread_cond_wait(&fl_cond, &q_lock);
		*/

	if(numitem_fl == 0)
	{
		Pthread_mutex_unlock(&q_lock);
		return;
	}

	if(queuegoingdown)
	{
		//printf("thread %d will go down\n", (int)pthread_self());
		Pthread_mutex_unlock(&q_lock);
		//Pthread_cancel(pthread_self());
		return;
	}

	q[tail++] = x;
	tail = tail % N;
	numitem_q++;
	numitem_fl--;

	if(numitem_q == 1)
		Pthread_cond_broadcast(&q_cond);

	//printf("[--put = %d\n", x);
	Pthread_mutex_unlock(&q_lock);
}

//remove from fl and add to q
template <class T>
void iqueue<T>::put(T x)
{
	Pthread_mutex_lock(&q_lock);

	while(numitem_fl == 0)	//queue is full
		Pthread_cond_wait(&fl_cond, &q_lock);

	if(queuegoingdown)
	{
		//printf("thread %d will go down\n", (int)pthread_self());
		Pthread_mutex_unlock(&q_lock);
		//Pthread_cancel(pthread_self());
		return;
	}

	q[tail++] = x;
	tail = tail % N;
	numitem_q++;
	numitem_fl--;

	if(numitem_q == 1)
		Pthread_cond_broadcast(&q_cond);

	//printf("[--put = %d\n", x);
	Pthread_mutex_unlock(&q_lock);
}
#endif

template <class T>
int iqueue_dynamic<T>::getqueuednum()
{
	return numitem_q;
}

template <class T>
int iqueue_dynamic<T>::getflnum()
{
	return numitem_fl;
}

template <class T>
char* iqueue_dynamic<T>::queuename()
{
	return name;
}

}

#endif /* IQUEUE_DYNAMIC_H_ */
