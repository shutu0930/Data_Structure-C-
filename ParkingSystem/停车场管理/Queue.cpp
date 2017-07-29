#include "Queue.h"

Queue::Queue()
{
 _base=new CarNode[QUEUE_INIT_SIZE];
 _front=_reer=0;
 _queue_capacity=QUEUE_INIT_SIZE;
 _queue_size=0;
 _queue_sum=0;
}


Queue::Queue(Queue &carQueue)
{
 int oldSize=carQueue._queue_capacity;
 int oldSum=carQueue._queue_sum;//不用多次调用
 _base=new CarNode[oldSize];
 _queue_capacity=oldSize;
 _front=0;
 for (_queue_sum=0;_queue_sum<oldSum;++_queue_sum)
 {
  _base[_queue_sum]._carNum=carQueue._base[_queue_sum]._carNum;
  _base[_queue_sum]._carType=carQueue._base[_queue_sum]._carType;
  _base[_queue_sum]._timeArr=carQueue._base[_queue_sum]._timeArr;
  _base[_queue_sum]._timeBgn=carQueue._base[_queue_sum]._timeBgn;
 }//for
 _reer=_queue_sum;
 _queue_size=carQueue._queue_size;
}

Queue::~Queue()
{
 delete [] _base;
 _base=NULL;
}

bool Queue::IncSize(int size)
{
 CarNodePtr pCarNode=new CarNode[_queue_capacity+size];
 for (int i=0;i<_queue_sum;++i)
 {
  pCarNode[i]._carNum=_base[_front]._carNum;
  pCarNode[i]._carType=_base[_front]._carType;
  pCarNode[i]._timeArr=_base[_front]._timeArr;
  pCarNode[i]._timeBgn=_base[_front]._timeBgn;
  _front=(_front+1)%_queue_capacity;
 }
 delete [] _base;
 _base=pCarNode;
 _front=0;
 _reer=_queue_sum;
 _queue_capacity+=size;
 return true;
}


bool Queue::ReSetQueue(int capacity)
{
 delete [] _base;
 _base=new CarNode[capacity];
 _front=_reer=0;
 _queue_capacity=capacity;
 _queue_size=0;
 _queue_sum=0;
 return true;
}


bool Queue::Empty()const
{
 return _queue_sum==0;//or_queue_size<=0;
}

bool Queue::Full()const
{
 return _queue_size>=_queue_capacity;
}


bool Queue::Clear()
{
 _front=_reer=0;
 _queue_size=0;
 _queue_sum=0;
 return true;
}


int Queue::QueueSize()const
{
 return _queue_size;
}


int Queue::QueueCapacity()const
{
 return _queue_capacity;
}

int Queue::QueueSum()const
{
 return _queue_sum;
}


CarNode Queue::GetFront()const
{
 return _base[_front];
}


CarNode Queue::GetReer()const
{
 return _base[(_reer-1+_queue_capacity)%_queue_capacity];
}

CarNodePtr Queue::GetBase()const
{
 return _base;
}


bool Queue::Find(const CarNode& target)const
{
 int pos=_front;
 for (int i=0;i<_queue_sum;++i)
 {
//  pos++;
  if (_base[pos]._carNum==target._carNum)
  {
//   break;
   return true;
  }//if
  pos=(pos+1)%_queue_capacity;
 }//for
// return pos;
 return false;
}


bool Queue::EnQueue(CarNode &carNode)
{//去掉了队列满检测，自动增容
 _base[_reer]._carNum=carNode._carNum;
 _base[_reer]._carType=carNode._carType;
 _base[_reer]._timeArr=carNode._timeArr;
 _base[_reer]._timeBgn=carNode._timeBgn;
 _reer=(_reer+1)%_queue_capacity;
 _queue_size+=carNode._carType;
 _queue_sum++;
 return true;
}


CarNode Queue::DeQueue()
{
 int i=_front;
 _front=(_front+1)%_queue_capacity;
 _queue_size-=_base[i]._carType;
 _queue_sum--;
 return _base[i];
}

ostream& operator<<(ostream& out,const Queue& carQueue)
{
 out<<"Index/tCarNumber/tCarType/t/tArrTime/t/tBgnTime"<<endl;
 int front=carQueue._front,count=carQueue.QueueSum(),capacity=carQueue._queue_capacity;
 for (int i=0;i<count;++i)
 {
  out<<i+1<<"/t"<<carQueue._base[front]._carNum<<"/t/t"<<carQueue._base[front]._carType<<"/t/t"<<carQueue._base[front]._timeArr<<"/t/t"<<carQueue._base[front]._timeBgn<<endl;//输入错误(错误的换行符),修改~
  front=(front+1)%capacity;
 }
 cout<<"Queue Capacity:"<<carQueue._queue_capacity<<"/tQueue Size:"<<carQueue._queue_size<<"/tQueue Sum:"<<carQueue._queue_sum<<endl;
 return out;
}
