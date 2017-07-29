#pragma once
enum Error_Code{success,overflow,underflow};
const int MAXSIZE=20;//small value for testing
typedef double Entry_Type;

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
	Error_Code exchange();
	Error_Code summation(Entry_Type &sum);
	Error_Code average(Entry_Type &average);
};