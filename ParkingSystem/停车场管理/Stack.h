#pragma once
#include "Time.h"
#include <string>
#define STACK_INIT_SIZE 100 //ջ��ʼ����
#define STACK_INCR_SIZE 50  //ջ����


typedef struct CarNode
{//������Ϣ�ṹ��
 string _carNum;
 int _carType;//�����������ִ���ռλ�õĴ�С
 Time _timeArr;//����ʱ��
 Time _timeBgn;//�복��ʱ��,��һ�����ͽ��복��������_timeArr���,����Ϊ���복���ĵ�ǰϵͳʱ��
}CarNode,*CarNodePtr;


class Stack
{//˳��ջ����ʼ100��50����
private:
 CarNodePtr _base,_top;//ͷβָ��
 int _stack_capacity;//ջ��С
 int _stack_size;//ջʹ�ô�С
 int _stack_sum;//��������
public:
 Stack();
 Stack(Stack& oldStack);//�˲���������oldStack
 ~Stack();
 bool IncSize(int size=STACK_INCR_SIZE);//ջ���ݡ��˲�������һ�����ݵ���ջ�������Ƶ�ǰջ�����ݣ�Ȼ��ɾ���ɵ�ջ��
 bool ReSetStack(int capacity);//ɾ��������ջ
 bool Empty()const;//ջ��û��Ԫ�ط���true,����false
 bool Full()const;
 bool Clear();//��ա�����_topָ�룬Ԫ�ص�ֵ�����
 int  StackCapacity()const;//����ջ����
 int  StackSize()const;//����ջʹ�ô�С
 int  StackSum()const;//������������
 bool Find(const CarNode& target)const;//�ҳ���λ��
 CarNodePtr GetBase()const;//����ջ��ָ��
 CarNodePtr GetTop()const;//����ջ��Ԫ��ָ��(ջ��ָ���ǰһ��)
 bool Push(const CarNode& car);//carѹ��ջ��
 CarNode Pop();//ջ��Ԫ�ص���
 friend ostream& operator<<(ostream& out,const Stack& carStack);
 friend ostream& operator<<(ostream& out,const CarNode carNode);
 friend istream& operator>>(istream& ins,CarNode& carNode);
};