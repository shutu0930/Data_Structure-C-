// �ַ���ƥ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "����һ���ַ�����������ɣ��м���ð�š�����������"<< endl;
	char c;
	while ((c = cin.get()) != '\n' && c != ':')		
	{
		left_queue.append(c);//����ַ������븳ֵ
	}
	if (c == '\n') 
	{
		cout << "N" << endl;//����'\n'˵��û��ð�ż�'N'
	}
	else
	{
		while ((c = cin.get()) != '\n' && c != ':')
		{
			right_queue.append(c);//�ұ��ַ������븳ֵ
		}
		
		if (left_queue.size() > right_queue.size()) //�����߲��ֱ��ұ߲��ֳ���'L'
		{
			cout << "L" << endl;
		}
		else if (left_queue.size() < right_queue.size()) //����ұ߲��ֱ���߲��ֳ���'R'
		{
			cout << "R" << endl;
		}
		else
		{
			char l =0, r =0;
			while (!left_queue.empty()) 
			{
				left_queue.serve_and_retrieve(l);//�ж����߲����Ƿ���ȫ��ͬ
				right_queue.serve_and_retrieve(r);
				if (l != r) break;
			}
		if (l == r) cout << "S" << endl;//��ȫ��ͬ��'S'
		else cout << "D" << endl;//���߲��ֲ���ȫ��ͬ����ͬ�����ȼ�'D'
		}
	}
}