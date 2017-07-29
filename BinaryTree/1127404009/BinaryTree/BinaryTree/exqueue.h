#pragma once
#include "queue.h"

template <class Queue_entry>
class Extended_Queue :
	public Queue<Queue_entry>
{
public:
	bool full()const;
	int size()const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);

};
template <class Queue_entry>
bool Extended_Queue<Queue_entry>::full()const
{
	if(count>=maxqueue)
		return true;
	else return false;
}

template <class Queue_entry>
void Extended_Queue<Queue_entry>::clear()
{
	count=0;
	rear=maxqueue-1;
	front=0;
}

template <class Queue_entry>
int Extended_Queue<Queue_entry>::size()const
{
	return count;
}

template <class Queue_entry>
Error_code Extended_Queue<Queue_entry>::serve_and_retrieve(Queue_entry &item)
{
	if(retrieve(item))
		if(serve())
			return success;
		else return underflow;
	else return underflow;
}