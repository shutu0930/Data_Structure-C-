#include "StdAfx.h"
#include "Queue.h"


template<class Queue_entry>
Queue<Queue_entry> :: Queue( )
{
	front = rear = NULL;
}

template<class Queue_entry>
Error_code Queue<Queue_entry> :: append(const Queue_entry item)
{
	Node<Queue_entry> *new_rear = new Node<Queue_entry>;
	new_rear->entry=item;
	if (new_rear == NULL)
		return overflow;
	if (rear == NULL) front = rear = new_rear;
	else 
	{
		rear->next = new_rear;
		rear = new_rear;
	}
	return success;
}

template<class Queue_entry>
Error_code Queue<Queue_entry> :: serve( )
{
	if (front == NULL)
		return underflow;
	Node<Queue_entry> *old_front = front;
	front = old_front->next;
	if (front == NULL)
		rear = NULL;
	delete old_front;
	return success;
}

template<class Queue_entry>
Error_code Queue<Queue_entry>::retrieve(Queue_entry &item) const
{
	if(front==NULL)
		return underflow;
	item=front->entry;
	return success;
}

template<class Queue_entry>
bool Queue<Queue_entry>::empty() const
{
	return (front==NULL && rear==NULL);
}

template<class Queue_entry>
Queue<Queue_entry>::~Queue(void)
{
	while(!empty())
		serve();
}

template<class Queue_entry>
void Queue<Queue_entry>::operator = (const Queue<Queue_entry> &original)
{
	if(&original!=this)
	{
		Clear();
		for(Node<Queue_entry> *temp=original.front->next;temp!=NULL;temp=temp->next)
			{ 
				append(temp->entry);
			}
	}
}
template<class Queue_entry>
int Queue<Queue_entry>::sum()const
{
	int count=0;
	Node<Queue_entry> *temp;
	for(temp=front;temp!=NULL;temp=temp->next)
	{
		count++;
	}
	return count;
}