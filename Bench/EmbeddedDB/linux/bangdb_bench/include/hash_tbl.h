/*
 * hash_tbl.h
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

#ifndef HASH_TBL_H_
#define HASH_TBL_H_

#include "bangdb.h"
#include "light_lock.h"

namespace bangdb
{
//simple thread safe hash table. It works with any item (for ex; table_info). User can store key, val into the hash table. The key has to
//be ULONG_T type and value could be any item. User is responsible for creating and freeing memory for the item, the table would just store it
template <class T>
class hash_tbl
{
public:
	hash_tbl(int tbl_size)
	{
		//printf("creating hash_tbl\n");
		_tbl_sz = tbl_size;
		tbl = new slot*[tbl_size];
		for(int i = 0; i<tbl_size; i++)
		{
			tbl[i] = NULL;
		}
		_num_items = 0;
		_iterate_idx = 0;
		_iterate_slot = NULL;
	}

	void clean(bool _clean = true)
	{
		//printf("cleaning hash_tbl\n");
		for(int i = 0; i<_tbl_sz; i++)
		{
			slot *s = tbl[i];
			while(s)
			{
				slot *ts = s;
				s = s->next;
				item *ti = ts->obj;
				if(_clean)
					delete (T*)(ti->item_obj);
				delete ti;
				delete ts;
			}
		}
		delete[] tbl;
		tbl = NULL;
		_num_items = 0;
	}

	void clean_items(bool _clean = true)
	{
		//printf("cleaning hash_tbl\n");
		for(int i = 0; i<_tbl_sz; i++)
		{
			slot *s = tbl[i];
			while(s)
			{
				slot *ts = s;
				s = s->next;
				item *ti = ts->obj;
				if(_clean)
					delete (T*)(ti->item_obj);
				delete ti;
				delete ts;
			}
			tbl[i] = NULL;
		}
		_num_items = 0;
	}

	int count()
	{
		_lock();
		int n = _num_items;
		_unlock();
		return n;
	}

	int count_nolock()
	{
		return _num_items;
	}

	void lock()
	{
		_lock();
	}

	void unlock()
	{
		_unlock();
	}

	//user will take lock before calling this and unlock when done
	//this method iterate over the table and returns reference to the item one by one
	//returns NULL when done
	void begin_iterate()
	{
		_iterate_idx = 0;
		_iterate_slot = tbl[_iterate_idx];
	}

	T *getnext()
	{
		bool slot_set = false;

		while(_iterate_idx < _tbl_sz)
		{
			if(slot_set)
				_iterate_slot = tbl[_iterate_idx];
			if(!_iterate_slot)
			{
				_iterate_idx++;
				slot_set = true;
				continue;
			}
			T *obj = _iterate_slot->obj->item_obj;
			_iterate_slot = _iterate_slot->next;
			return obj;
		}
			return NULL;
	}

	T *find_object(ULONG_T iid)
	{
		//printf("finding [%ld]\n", iid);
		T *obj = NULL;
		_lock();
		slot *s = _find_slot(iid);
		if(s)
			obj = s->obj->item_obj;
		_unlock();
		return obj;
	}

	int add_object(ULONG_T iid, T *obj)
	{
		//printf("adding [%ld]\n", iid);
		int r = 0;
		_lock();
		r = _add(iid, obj);
		_unlock();
		return r;
	}

	T *del_object(ULONG_T iid)
	{
		//printf("deleting [%ld]\n", iid);
		T *obj = NULL;
		_lock();
		obj = _remove(iid);
		_unlock();
		return obj;
	}
private:
	struct item
	{
		ULONG_T item_id;
		T *item_obj;
		item()
		{
			item_id = -1;
			item_obj = NULL;
		}
		item(ULONG_T iid, T *obj)
		{
			item_id = iid;
			item_obj = obj;
		}
		~item()
		{
			item_id = -1;
		}
		bool compare(ULONG_T id)
		{
			return (id == item_id)?true:false;
		}
	};

	struct slot
	{
		slot *next;
		slot *prev;
		int id;
		item *obj;

		slot()
		{
			next = prev = NULL;
			id = -1;
			obj = NULL;
		}

		~slot()
		{
			next = prev = NULL;
			id = -1;
			obj = NULL;
		}
	};

	light_spin_lock _mlock;
	slot **tbl;
	int _tbl_sz;
	int _num_items;
	int _iterate_idx;
	slot *_iterate_slot;

	void _lock()
	{
		_mlock.lock();
	}

	void _unlock()
	{
		_mlock.unlock();
	}

	slot *_find_slot(ULONG_T iid)
	{
		slot *s = tbl[iid%_tbl_sz];
		while(s)
		{
			if(s->obj && s->obj->compare(iid))
				break;
			s = s->next;
		}
		return s;
	}

	int _add(ULONG_T iid, T *obj)
	{
		if(_find_slot(iid))
			return -1;
		int n = iid%_tbl_sz;
		slot *s = tbl[n];
		item *it = new item(iid, obj);

		slot *ts = new slot();
		ts->id = iid%_tbl_sz;
		ts->obj = it;

		if(!s)
			tbl[n] = ts;
		else
		{
			ts->next = s->next;
			if(s->next)
				s->next->prev = ts;
			ts->prev = s;
			s->next = ts;
		}
		return ++_num_items;
	}

	T *_remove(ULONG_T iid)
	{
		slot *s = NULL;
		if((s = _find_slot(iid)) == NULL)
			return NULL;

		slot *ts = tbl[iid%_tbl_sz];

		if(s == ts)
			tbl[iid%_tbl_sz] = s->next;
		else
			s->prev->next = s->next;

		if(s->next)
			s->next->prev = s->prev;
		T *_obj = s->obj->item_obj;
		delete s->obj;
		delete s;
		s = NULL;
		--_num_items;
		return _obj;
	}
};
}
#endif /* HASH_TBL_H_ */
