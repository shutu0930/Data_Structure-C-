#pragma once
#include "Queue.h"
#include "Stack.h"
#include<iostream>
using namespace std;
const int FEE=20;

class Car
{
public:
	int license;
	int time;
	bool in_out;//in=1;out=0;
	Car(void);
	Car(int lic);
	Car(Car &temp);
	~Car(void);
	void arrive(int arrivetime,Stack<Car> &parlot,Queue<Car> &shocut);
	void leave(int leavetime,Stack<Car> &parlot,Queue<Car> &shocut);
};
