#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
typedef char Queue_entry;
enum Error_code{success,overflow,underflow};
const int maxqueue=10;
class Queue
{
public:
	Queue(void);
	bool empty()const;
	Error_code serve();
	Error_code append(const Queue_entry &item);
	Error_code retrieve(Queue_entry &item)const;
	~Queue(void);
protected:
	int count;
	int front,rear;
	Queue_entry entry[maxqueue];
};
