#include "StdAfx.h"
#include "Stack.h"
#include <iostream>

Stack::Stack()
{
	count=0;
}

Error_Code Stack::push(const Entry_Type item)
/*Pre:None.
Post:If the Stack is not full,item is added to the top of the Stack.If the Stack 
is full,an Error_code of overflow is returned and the Stack is left unchanged.*/
{
	if(count>=MAXSIZE)
		return overflow;

	entry[count]=item;
	count++;
	return success;
}

Error_Code Stack::pop()
/*Pre:None.
Post:If the Stack is not empty,the top of the Stack is removerd.If the Stack is 
empty,an Error_code of underflow is returned*/
{
	if(count==0)
		return underflow;

	count--;
	return success;
}

Error_Code Stack::top(Entry_Type &item)const
/*Pre:None.
Post:If the Stack is not empty,the top of the Stack is returned in item.If the Stack is 
empty,an Error_code of underflow is returned*/
{
	if(count==0)
		return underflow;

	item=entry[count-1];
	return success;
}

bool Stack::empty()const
/*Pre:None.
Post:If the Stack is empty,true is returned,otherwose false is returned*/
{
	if(count==0)
		return true;
	else
		return false;
}
Error_Code Stack::exchange()
{
	if(count>=2)
	{
		entry[count-2]=entry[count-1]-entry[count-2];
		entry[count-1]=entry[count-1]-entry[count-2];
		entry[count-2]=entry[count-1]+entry[count-2];
		return success;
	}else
	{
		return underflow;	
	}
	

}
Error_Code Stack::summation(Entry_Type &sum)
{
	if(empty()==0)
	{
		sum=0;
		for(int i=0;i<count;i++)
		{
			sum+=entry[i];
		}
		return success;	
	
	}else
	{
		return underflow;
	
	}

}
Error_Code Stack::average(Entry_Type &average)
{
	
	if(empty()==false)
	{
		double sum=0.0;
		summation(sum);
		average=sum/count;
		return success;
	
	
	}else
	{
		return underflow;
	}



}