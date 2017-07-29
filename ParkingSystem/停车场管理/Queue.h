#pragma once
#include "Stack.h"
#define QUEUE_INIT_SIZE 100 //���г�ʼ����
#define QUEUE_INCR_SIZE 50  //��������

class Queue
{//˳����У���ʼ100������50
private:
 CarNodePtr _base;//˳�����ͷָ��
 int _front,_reer;//�α�(�±����)
 int _queue_capacity;//���д�С
 int _queue_size;//����ʹ�ô�С
 int _queue_sum;//��������
public:
 Queue();
 Queue(Queue& carQueue);
 ~Queue();
 bool IncSize(int size=QUEUE_INCR_SIZE);//�������ݡ����ݺ��ƾɶ��е���Ϣ����ɾ���ɶ��С�
 bool ReSetQueue(int capacity);//ɾ���������¶���
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
