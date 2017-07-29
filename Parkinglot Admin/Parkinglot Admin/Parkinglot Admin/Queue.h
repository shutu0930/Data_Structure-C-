#pragma once

enum Error_code{underflow,success,overflow,not_present,range_error};

template<class Node_entry>
struct Node
{
	// data members
	Node_entry entry;
	Node *next; //use before definition
	// constructors
	Node()
	{
		next = NULL;
	}
	Node(const Node_entry item, Node *add_on = NULL)
	{
		entry = item;
		next = add_on;
	}
};


template<class Queue_entry>
class Queue
{
public:
	// standard Queue methods
	Queue( );
	bool empty( ) const;
	Error_code append(const Queue_entry item);
	Error_code serve( );
	Error_code retrieve(Queue_entry &item) const;
	// safety features for linked structures
	~Queue( );
	void operator = (const Queue<Queue_entry> &original);
	int sum( )const;
protected:
	Node<Queue_entry> *front;
	Node<Queue_entry> *rear;
};