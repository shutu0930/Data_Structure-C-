// Parkinglot Admin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Car.h"
#include "Queue.cpp"
#include "Stack.cpp"

#include<iostream>
using namespace std;

void introduction()
{
	cout<<"������ָ�� i�����룬o���뿪��q���°�"<<endl;
}
void instruction()
{
	cout<<"******************************ͣ��������ϵͳ******************************"<<endl
		<<"��ͣ�����ɡ�������͡�ͣ��������ɣ�������������ͣ��������ֻ��********"<<MAXSIZE<<endl
		<<"��ͣ�����г��ӿ���ȥ��ʱ�����������ȥ�ĳ���ÿһ������Ҫ����һ�η���****"
		<<"��ͣ��������������շѣ���ͣ�������շ�ΪÿСʱ"<<FEE<<"Ԫ"<<endl
		<<"ps:ʱ���ֶ����룬eg��1��ʾ1�㣬2��ʾ2�㣬лл�������ټ���*****************"<<endl;
}
char get_command()
{
	char command;
	bool waiting=true;
	cout<<"Select commmand and press <ENTER>";
	while(waiting)
	{
		cin>>command;
		command=tolower(command);
		if(command=='i'||command=='o'|| command=='q')
			waiting=false;
		else
			introduction();
	}
	return command;
}
bool do_command(char command,Queue<Car> &qpark,Stack<Car> &spark)
{
	if(command=='q')
	{
		cout<<"������¡���°��°࣡"<<endl;
		return 0;
	}
	int time;
	cout<<"please input the time";
	cin>>time;
	int lic;
	cout<<"please input the car license";
	cin>>lic;
	if(command=='i')
	{
		Car newcar(lic);
		newcar.arrive(time,spark,qpark);//���³�����
	}
	if(command=='o')
	{
		Car temp;
		Stack<Car> temppark;
		int count=spark.sum();
		do{
		spark.top(temp);
		temp.leave(time,spark,qpark);//ͣ����������ĳ����뿪
		temppark.push(temp);
		count--;
		}//�뿪�ĳ�������һ����ʱ��ͣ����
		while(temp.license!=lic && count>0);//���һ����ȥ�ĳ���ΪӦ�ó�ȥ�ĳ���
		if(count==0 && temp.license!=lic)
		{
			while(temppark.top(temp)!=Underflow)
			{
				temp.arrive(time,spark,qpark);//�������»ص�ͣ����
				temppark.pop();
			}
			cout<<"���޴˳�"<<endl;
			return 0;
		}
		temppark.pop();//Ӧ�ó�ȥ�ĳ��ӳ�ȥ��
		while(temppark.top(temp)!=Underflow)
		{
			temp.arrive(time,spark,qpark);//�������»ص�ͣ����
			temppark.pop();
		}
		if(qpark.retrieve(temp))
			temp.arrive(time,spark,qpark);//�������ǰ���һ��������ͣ����
	}
	return 1;
}

int main()
{
	int sum=0;
	Stack<Car> parkinglot;
	Queue<Car> shortcut;
	instruction();
	introduction();
	while(do_command(get_command(),shortcut,parkinglot));
	return 0;
}

