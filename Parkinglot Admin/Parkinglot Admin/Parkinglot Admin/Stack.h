#pragma once

enum Error_Code{Success,Overflow,Underflow};
const int MAXSIZE=2;

template<class Entry_Type>
class Stack
{
private:
	int count;
	Entry_Type entry[MAXSIZE];

public:
	Stack();
	Error_Code push(const Entry_Type item);
	Error_Code pop();
	Error_Code top(Entry_Type &item)const;
	bool empty()const;
	int sum()const;
};