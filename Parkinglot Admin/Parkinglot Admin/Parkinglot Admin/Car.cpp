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
//����ʱ���ͣ��λ��
{
	time=arrivetime;
	in_out=true;//���赽��ͣ����
	if(parlot.push(*this)!=Overflow)//ͣ������λδ��
	{
		cout<<"����"<<license<<"���ͣ������,��λΪ"<<parlot.sum()<<endl;
	}
	else
	{
		in_out=false;//������
		shocut.append(*this);
		cout<<"����"<<license<<"��������,��λΪ"<<shocut.sum()<<endl;
	}
}
void Car::leave(int leavetime,Stack<Car> &parlot,Queue<Car> &shocut)
//�뿪ʱ���ͣ��ʱ���Լ���������
{
	int staytime=leavetime-time;
	if(in_out==false)//�����ڱ����ͣ��
	{
		shocut.serve();
		cout<<"����"<<license<<"�뿪���������ͣ��"<<staytime<<"������ɷ���"<<endl;
	}
	else//��ͣ����ͣ��
	{
		in_out=false;
		parlot.pop();
		cout<<"����"<<license<<"�뿪��ͣ��������ͣ��"<<staytime<<"����ɷ���"<<staytime*FEE<<"Ԫ��лл��"<<endl;
	}
}
