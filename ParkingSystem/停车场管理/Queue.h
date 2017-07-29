#pragma once
#include "Stack.h"
#define QUEUE_INIT_SIZE 100 //队列初始容量
#define QUEUE_INCR_SIZE 50  //队列增量

class Queue
{//顺序队列，初始100，增量50
private:
 CarNodePtr _base;//顺序队列头指针
 int _front,_reer;//游标(下标控制)
 int _queue_capacity;//队列大小
 int _queue_size;//队列使用大小
 int _queue_sum;//汽车数量
public:
 Queue();
 Queue(Queue& carQueue);
 ~Queue();
 bool IncSize(int size=QUEUE_INCR_SIZE);//队列扩容。增容后复制旧队列的信息，并删除旧队列。
 bool ReSetQueue(int capacity);//删除并重设新队列
 bool Empty()const;
 bool Full()const;
 bool Clear();
 int  QueueSize()const;
 int  QueueCapacity()const;
 int  QueueSum()const;
 bool Find(const CarNode& target)const;
 CarNodePtr GetBase()const;
 CarNode GetFront()const;
 CarNode GetReer()const;
 bool EnQueue(CarNode& carNode);
 CarNode DeQueue();
 friend ostream& operator<<(ostream& out,const Queue& carQueue);
};
