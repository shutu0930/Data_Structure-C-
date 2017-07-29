#pragma once
#include "Time.h"
#include <string>
#define STACK_INIT_SIZE 100 //栈初始容量
#define STACK_INCR_SIZE 50  //栈增量


typedef struct CarNode
{//汽车信息结构体
 string _carNum;
 int _carType;//汽车类型数字代表占位置的大小
 Time _timeArr;//到达时间
 Time _timeBgn;//入车场时间,若一来到就进入车场，则与_timeArr相等,否则为进入车场的当前系统时间
}CarNode,*CarNodePtr;


class Stack
{//顺序栈，初始100，50递增
private:
 CarNodePtr _base,_top;//头尾指针
 int _stack_capacity;//栈大小
 int _stack_size;//栈使用大小
 int _stack_sum;//车辆总数
public:
 Stack();
 Stack(Stack& oldStack);//此操作部销毁oldStack
 ~Stack();
 bool IncSize(int size=STACK_INCR_SIZE);//栈扩容。此操作创建一个增容的新栈，并复制当前栈中内容，然后删除旧的栈。
 bool ReSetStack(int capacity);//删除重设新栈
 bool Empty()const;//栈中没有元素返回true,否则false
 bool Full()const;
 bool Clear();//清空。重置_top指针，元素的值不理会
 int  StackCapacity()const;//返回栈容量
 int  StackSize()const;//返回栈使用大小
 int  StackSum()const;//返回汽车数量
 bool Find(const CarNode& target)const;//找车辆位置
 CarNodePtr GetBase()const;//返回栈底指针
 CarNodePtr GetTop()const;//返回栈顶元素指针(栈顶指针的前一项)
 bool Push(const CarNode& car);//car压入栈顶
 CarNode Pop();//栈顶元素弹出
 friend ostream& operator<<(ostream& out,const Stack& carStack);
 friend ostream& operator<<(ostream& out,const CarNode carNode);
 friend istream& operator>>(istream& ins,CarNode& carNode);
};