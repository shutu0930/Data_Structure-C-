#include "Stack.h"


Stack::Stack()
{
 _base=new CarNode[STACK_INIT_SIZE];
 for (int i=0;i<STACK_INIT_SIZE;++i)
 {
  _base[i]._carType=0;
 }//for
 _top=_base;
 _stack_capacity=STACK_INIT_SIZE;
 _stack_size=0;
 _stack_sum=0;
}//Stack

Stack::Stack(Stack& oldStack)
{
 CarNodePtr pOldStack=oldStack._base;
 int oldsum=oldStack._stack_sum;
 _base=new CarNode[oldStack._stack_capacity];
 _top=_base;
 for (int i=0;i<oldsum;++i)
 {
  _top->_carNum=pOldStack->_carNum;
  _top->_carType=pOldStack->_carType;
  _top->_timeArr=pOldStack->_timeArr;
  _top->_timeBgn=pOldStack->_timeBgn;
  _top++;
  pOldStack++;
 }//for
 _stack_sum=oldStack._stack_sum;
 _stack_size=oldStack._stack_size;
 _stack_capacity=oldStack._stack_capacity;
}


Stack::~Stack()
{
 delete [] _base;
 _base=_top=NULL;
}


bool Stack::IncSize(int size)
{
 CarNodePtr pCarNode,pOldStack=_base;
 pCarNode=new CarNode[_stack_capacity+size];
 _top=pCarNode;//暂存
 for (int i=0;i<_stack_sum;++i)
 {
  pCarNode->_carNum=pOldStack->_carNum;
  pCarNode->_carType=pOldStack->_carType;
  pCarNode->_timeArr=pOldStack->_timeArr;
  pCarNode->_timeBgn=pOldStack->_timeBgn;
  pCarNode++;
  pOldStack++;
 }//for
 delete [] _base;
 _base=_top;//交换
 _top=pCarNode;
 _stack_capacity+=size;
 return true;
}

bool Stack::ReSetStack(int capacity)
{
 delete [] _base;
 _base=new CarNode[capacity];
 _top=_base;
 _stack_capacity=capacity;
 _stack_size=0;
 _stack_sum=0;
 return true;
}

bool Stack::Empty()const
{
 return _stack_sum==0;//or_stack_size<=0;
}


bool Stack::Full()const
{
 return _stack_size>=_stack_capacity;
}


bool Stack::Clear()
{
 _top=_base;
 _stack_sum=0;
 _stack_size=0;
 return true;
}

 

int Stack::StackCapacity()const
{
 return _stack_capacity;
}

int Stack::StackSize()const
{
 return _stack_size;
}

int Stack::StackSum()const
{
 return _stack_sum;
}


bool Stack::Find(const CarNode& target)const
{
// int pos=0;
 CarNodePtr pTemp=_base;
 while (pTemp!=_top)
 {
//  pos++;
  if (pTemp->_carNum==target._carNum)
  {//找到
//   break;
   return true;
  }//if
  pTemp++;
 }//while
// return pos;
 return false;
}


CarNodePtr Stack::GetTop()const
{
 return _top-1;
}

CarNodePtr Stack::GetBase()const
{
 return _base;
}


bool Stack::Push(const CarNode& car)
{//去掉了栈满判断，以及自动增容功能
 _top->_carNum=car._carNum;
 _top->_carType=car._carType;
 _top->_timeArr=car._timeArr;
 _top->_timeBgn=car._timeBgn;
 _top++;
 _stack_size+=car._carType;//位置
 _stack_sum++;
 return true;
}


CarNode Stack::Pop()
{//去掉了栈空判断
 _top--;
 _stack_size-=_top->_carType;
 _stack_sum--;
 return *_top;
}


ostream& operator<<(ostream& out,const Stack& carStack)
{
 int count=0;
 CarNodePtr pLink_base=carStack._base,pLink_top=carStack._top;
 out<<"Index/tCarNumber/tCarType/t/tArrTime/t/tBgnTime"<<endl;
 while (pLink_base!=pLink_top)
 {
  out<<++count<<"/t"<<pLink_base->_carNum<<"/t/t"<<pLink_base->_carType<<"/t/t"<<pLink_base->_timeArr<<"/t/t"<<pLink_base->_timeBgn<<endl;
  pLink_base++;
 }//while
 cout<<"Stack Capacity:"<<carStack._stack_capacity<<"/tStack Size:"<<carStack._stack_size<<"/tStack Sum:"<<carStack._stack_sum<<endl;
 return out;
}

 

ostream& operator<<(ostream& out,const CarNode carNode)
{
 out<<carNode._carNum<<"/t/t"<<carNode._carType<<"/t"<<carNode._timeArr<<"/t"<<carNode._timeBgn;
 return out;
}


istream& operator>>(istream& ins,CarNode& carNode)
{
 getline(ins,carNode._carNum,',');//受到终止符号的限制，输入命令时必须小心。
 ins>>carNode._carType;
 ins.ignore();
 ins>>carNode._timeArr;
 return ins;
}
