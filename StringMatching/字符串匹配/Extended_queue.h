#pragma once
#include "queue.h"

class Extended_queue :
	public Queue
{
public:
	Extended_queue(void);
	bool full()const;
	int size()const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &item);
	~Extended_queue(void);
};
