/*
 * iqueue_simple.h
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

#ifndef IQUEUE_SIMPLE_H_
#define IQUEUE_SIMPLE_H_

#include "bangdb.h"

namespace bangdb
{

template <class T>
class iqueue_simple
{
public:
	//construct the eventqueue, whether queue is shared or not
	iqueue_simple(char *_name, bool shared);

	//init the queue with initial queuesize, it should be a good guess for better performance
	void init(int queuesize);

	//put item in the queue, put item in queue, will get node(beg) from free list and add to q(beg)
	int put(T x);

	//get item from the queue, remove item from queue, will get the data(tail) and the put the node in free list(beg)
	T get();

	//peek item, don't remove from the queue and put in fl
	T peek();

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
	~iqueue_simple();

private:

	T *q;

	int N;

	int head;

	int tail;

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
};

template <class T>
iqueue_simple<T>::iqueue_simple(char *_name, bool shared)
{
	if(!(name = Strncpy(name, _name)))
		err_sys("iqueue_simple::iqueue_simple error in strncpy");

	isshared = shared;
	qsize = 0;
	numitem_fl = 0;
	numitem_q = 0;
	closed = false;
	queuegoingdown = false;

	q = NULL;
	N = 0;
	head = tail = 0;
}

template <class T>
iqueue_simple<T>::~iqueue_simple()
{
	//err_ret("destroy iqueue_simple starting...");
	if(!closed)
		closequeue();

	delete[] name;
}

template <class T>
void iqueue_simple<T>::willshutdown()
{
	queuegoingdown = true;
	int old_numq, old_numfl;
	old_numq = numitem_q;
	old_numfl = numitem_fl;
	numitem_q = numitem_fl = 1;
	numitem_q = old_numq;
	numitem_fl = old_numfl;
}

template <class T>
void iqueue_simple<T>::closequeue()
{
	//printf("closequeue started\n");
	delete[] q;
	//printf("queue deleted\n");
	closed = true;
	//err_ret("closequeue done");
}

template <class T>
void iqueue_simple<T>::init(int queuesize)
{
	qsize = queuesize;
	N = qsize + 1;
	head = N;
	tail = 0;
	q = new T[N];
	numitem_fl = qsize;
}

//remove from q and add the empty item to fl
template <class T>
T iqueue_simple<T>::get()
{
	if(queuegoingdown || numitem_q == 0)
	{
		return NULL;
	}

	head = head % N;
	T x = q[head++];
	numitem_q--;
	numitem_fl++;

	return x;
}

//just peek, amd don't remove from q and add the empty item to fl
template <class T>
T iqueue_simple<T>::peek()
{
	if(queuegoingdown || numitem_q == 0)
	{
		return NULL;
	}

	head = head % N;
	return q[head];
}

//remove from fl and add to q
template <class T>
int iqueue_simple<T>::put(T x)
{
	if(queuegoingdown || numitem_fl == 0)
	{
		return -1;
	}

	q[tail++] = x;
	tail = tail % N;
	numitem_q++;
	numitem_fl--;
	return 0;
}

template <class T>
int iqueue_simple<T>::getqueuednum()
{
	return numitem_q;
}

template <class T>
int iqueue_simple<T>::getflnum()
{
	return numitem_fl;
}

template <class T>
char* iqueue_simple<T>::queuename()
{
	return name;
}
}

#endif /* IQUEUE_SIMPLE_H_ */
