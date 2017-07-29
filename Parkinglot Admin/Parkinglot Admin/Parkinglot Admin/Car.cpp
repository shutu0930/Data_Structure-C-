#include "StdAfx.h"
#include "Car.h"
#include "Queue.cpp"
#include "Stack.cpp"

Car::Car(void)
{
	license=0;
	in_out=0;
	time=-1;
}
Car::Car(int lic)
{
	license=lic;
	in_out=0;
	time=-1;
}
Car::Car(Car &temp)
{
	license=temp.license;
	in_out=temp.in_out;
	time=temp.time;
}
Car::~Car(void)
{
}
void Car::arrive(int arrivetime,Stack<Car> &parlot,Queue<Car> &shocut)
//到达时输出停车位置
{
	time=arrivetime;
	in_out=true;//假设到达停车场
	if(parlot.push(*this)!=Overflow)//停车场车位未满
	{
		cout<<"车牌"<<license<<"到达『停车场』,车位为"<<parlot.sum()<<endl;
	}
	else
	{
		in_out=false;//到达便道
		shocut.append(*this);
		cout<<"车牌"<<license<<"到达『便道』,车位为"<<shocut.sum()<<endl;
	}
}
void Car::leave(int leavetime,Stack<Car> &parlot,Queue<Car> &shocut)
//离开时输出停留时间以及所交费用
{
	int staytime=leavetime-time;
	if(in_out==false)//若是在便道上停车
	{
		shocut.serve();
		cout<<"车牌"<<license<<"离开『便道』，停留"<<staytime<<"无需缴纳费用"<<endl;
	}
	else//在停车场停车
	{
		in_out=false;
		parlot.pop();
		cout<<"车牌"<<license<<"离开『停车场』，停留"<<staytime<<"请缴纳费用"<<staytime*FEE<<"元，谢谢！"<<endl;
	}
}
