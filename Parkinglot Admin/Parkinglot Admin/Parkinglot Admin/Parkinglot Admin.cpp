// Parkinglot Admin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Car.h"
#include "Queue.cpp"
#include "Stack.cpp"

#include<iostream>
using namespace std;

void introduction()
{
	cout<<"请输入指令 i：进入，o：离开，q：下班"<<endl;
}
void instruction()
{
	cout<<"******************************停车场管理系统******************************"<<endl
		<<"本停车场由【便道】和【停车场】组成，便道容量无穷大，停车场容量只有********"<<MAXSIZE<<endl
		<<"当停车场有车子开出去的时候，在他后面进去的车子每一辆都需要缴纳一次费用****"
		<<"本停车场【便道】不收费，【停车场】收费为每小时"<<FEE<<"元"<<endl
		<<"ps:时间手动输入，eg：1表示1点，2表示2点，谢谢合作，再见！*****************"<<endl;
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
		cout<<"生意兴隆，下班下班！"<<endl;
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
		newcar.arrive(time,spark,qpark);//有新车进入
	}
	if(command=='o')
	{
		Car temp;
		Stack<Car> temppark;
		int count=spark.sum();
		do{
		spark.top(temp);
		temp.leave(time,spark,qpark);//停车场最外面的车辆离开
		temppark.push(temp);
		count--;
		}//离开的车辆进入一个临时的停车场
		while(temp.license!=lic && count>0);//最后一辆出去的车子为应该出去的车子
		if(count==0 && temp.license!=lic)
		{
			while(temppark.top(temp)!=Underflow)
			{
				temp.arrive(time,spark,qpark);//车子重新回到停车场
				temppark.pop();
			}
			cout<<"查无此车"<<endl;
			return 0;
		}
		temppark.pop();//应该出去的车子出去了
		while(temppark.top(temp)!=Underflow)
		{
			temp.arrive(time,spark,qpark);//车子重新回到停车场
			temppark.pop();
		}
		if(qpark.retrieve(temp))
			temp.arrive(time,spark,qpark);//便道上最前面的一辆车进入停车场
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

