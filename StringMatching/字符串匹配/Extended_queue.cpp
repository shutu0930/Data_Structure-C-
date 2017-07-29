#include "Extended_queue.h"

Extended_queue::Extended_queue(void)
{
}
int Extended_queue::size() const
/*Post:Return the number of entries in the Extended_queue .*/
{
	return count;
}
bool Extended_queue::full()const
{
	return (count==maxqueue-1);

}
void Extended_queue::clear()
{
	count=0;
	rear=maxqueue-1;
	front=0;
}
Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
	if(count<=0)return underflow;
	count--;
	item=entry[front];
	front=((front+1)==maxqueue)?0:(front+1);
	return success;

}
Extended_queue::~Extended_queue(void)
{
}
