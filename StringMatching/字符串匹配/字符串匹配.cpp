// 字符串匹配.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "queue.h"
#include "Extended_queue.h"
#include <iostream>
using namespace std;
int main()
{
	Extended_queue left_queue;
	Extended_queue right_queue;
	cout << "输入一行字符，两部分组成，中间用冒号‘：’隔开："<< endl;
	char c;
	while ((c = cin.get()) != '\n' && c != ':')		
	{
		left_queue.append(c);//左边字符串输入赋值
	}
	if (c == '\n') 
	{
		cout << "N" << endl;//遇到'\n'说明没有冒号即'N'
	}
	else
	{
		while ((c = cin.get()) != '\n' && c != ':')
		{
			right_queue.append(c);//右边字符串输入赋值
		}
		
		if (left_queue.size() > right_queue.size()) //如果左边部分比右边部分长即'L'
		{
			cout << "L" << endl;
		}
		else if (left_queue.size() < right_queue.size()) //如果右边部分比左边部分长即'R'
		{
			cout << "R" << endl;
		}
		else
		{
			char l =0, r =0;
			while (!left_queue.empty()) 
			{
				left_queue.serve_and_retrieve(l);//判断两边部分是否完全相同
				right_queue.serve_and_retrieve(r);
				if (l != r) break;
			}
		if (l == r) cout << "S" << endl;//完全相同即'S'
		else cout << "D" << endl;//两边部分不完全相同但有同样长度即'D'
		}
	}
}