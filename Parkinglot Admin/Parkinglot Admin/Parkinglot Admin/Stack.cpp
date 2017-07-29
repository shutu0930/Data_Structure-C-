#include "StdAfx.h"
#include "Stack.h"

template<class Entry_Type>
Stack<Entry_Type>::Stack()
{
	count=0;
}
template<class Entry_Type>
Error_Code Stack<Entry_Type>::push(const Entry_Type item)
{
	if(count>=MAXSIZE)
		return Overflow;

	entry[count]=item;
	count++;
	return Success;
}
template<class Entry_Type>
Error_Code Stack<Entry_Type>::pop()
{
	if(count==0)
		return Underflow;

	count--;
	return Success;
}
template<class Entry_Type>
Error_Code Stack<Entry_Type>::top(Entry_Type &item)const
{
	if(count==0)
		return Underflow;

	item=entry[count-1];
	return Success;
}
template<class Entry_Type>
bool Stack<Entry_Type>::empty()const
{
	if(count==0)
		return true;
	else
		return false;
}
template<class Entry_Type>
int Stack<Entry_Type>::sum()const
{
	return count;
}