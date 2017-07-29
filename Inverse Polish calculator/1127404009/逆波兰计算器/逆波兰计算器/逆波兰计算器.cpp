// 逆波兰计算器.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
#include "Stack.h"
using namespace std;
char get_command()
{
	char command;
	bool waiting=true;
	cout<<"Select command and press <Enter>:";
	while(waiting)
	{
		cin>>command;
		command=tolower(command);
		if(	command=='?' || command=='=' || command=='+' ||
			command=='-' || command=='*' || command=='/' ||
			command=='e'||command=='s'|| command=='a'||command=='q')waiting=false;
		else
		{
			cout<<"Please enter a balid command:"<<endl
				<<"[?]push to stack [=]print top"<<endl
				<<"[+][-][*][/] are arithmetic operations"<<endl
				<<"[e]exchange the top two value"<<endl		//交换栈顶的两个数值
				<<"[s]calculate the summation of tall the value"<<endl		//累加栈中的所有数值
				<<"[a]calculate the average of tall the value"<<endl		//求栈中的所有数值的平均值
				<<"[Q]uit."<<endl;
		}
	}
	return command;
}
bool do_command(char command,Stack &numbers)
/*Pre:The first parameter specifies a valid calculator command.
Post:The command specified by the second parameter.A result of true is returned unless command=='q'.
Uses:The class Stack.*/
{
	double q,p;
	switch(command)
	{
	case'?':
		cout<<"Enter a real number:"<<flush;
		cin>>p;
		if(numbers.push(p)==overflow)
			cout<<"Warning:Stack full,lost number"<<endl;
		break;
	case'=':
		if(numbers.top(p)==underflow)
			cout<<"Stack empty"<<endl;
		else
			cout<<p<<endl;
		break;
	case'+':
		if(numbers.top(p)==underflow)
			cout<<"Stack empty"<<endl;
		else
		{
			numbers.pop();
			if(numbers.top(q)==underflow)
			{
				cout<<"Stack has just one entry"<<endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if(numbers.push(q+p)==underflow)
					cout<<"Warning:Stack full ,lost result"<<endl;
			}
		}
		break;
	case '-':
		if (numbers.top(p) == underflow) cout << "Stack empty" << endl;
		else {
			numbers.pop();
			if (numbers.top(q) == underflow) {
			cout << "Stack has just one entry" << endl;
			numbers.push(p);
		}
		else {
			numbers.pop();
			if (numbers.push(q - p) == overflow)
			cout << "Warning: Stack full, lost result" << endl;
			}
		}
		break;
	case '*':
		if (numbers.top(p) == underflow) cout << "Stack empty" << endl;
		else{
			numbers.pop();
			if (numbers.top(q) == underflow){
			cout << "Stack has just one entry" << endl;
			numbers.push(p);
			}
			else{
				numbers.pop();
				if (numbers.push(q * p) == overflow)
				cout << "Warning: Stack full, lost result" << endl;
			}
		}
		break;
	case '/':
		if (numbers.top(p) == underflow) cout << "Stack empty" << endl;
		else if (p == 0.0)
		{
			cerr << "Division by 0 fails; no action done." << endl;
			numbers.push(p); // Restore stack to its prior state.
		}
		else
		{
			numbers.pop();
			if (numbers.top(q) == underflow) 
			{
				cout << "Stack has just one entry" << endl;
				numbers.push(p);
			}
			else
			{
				numbers.pop();
				if (numbers.push(q / p) == overflow)
				cout << "Warning: Stack full, lost result" << endl;
			}
		}
		break;
	case'e'://交换栈顶的两个数值
		if(numbers.exchange()==success)
		{
			cout<<"Successfully exchange the top two."<<endl;
		}else
			cout<<"Fail to exchange the top two."<<endl;
		break;
	case's'://累加栈中的所有数值
		double sum;
		if(numbers.summation(sum)==success)
		{
			cout<<"All the value's summation is"<<sum<<endl;
		
		}else
		{
			cout<<"Fail to sum up all the value."<<endl;
		
		}
		break;
	case'a'://求栈中的所有数值的平均值
		double average;
		if(numbers.average(average)==success)
		{
			cout<<"The average of all the value is"<<average<<endl;
		}else
		{
			cout<<"Fail to get the average."<<endl;
		}
	case'q':
		cout<<"Calculation finished.\n";
		return false;
	}
	return true;
}
void instructions()
/*
Pre: None.
Post: Instructions for using the Calcstra.
*/
{
	cout<<"Welcome to use the Calcstra."<<endl;
	cout<<"This calculator uses a array. "<<endl;
	cout<<"The program has executed simple arithmetic commands entered by the user."<<endl;

}

void main()
/*Post:The program has executed simple arithmetic commands entered by the user.
Uses:The class Stack and funtions introduction,do_command and andget command.*/
{
	Stack stored_numbers;
	instructions();
	while(do_command(get_command(),stored_numbers));
}

