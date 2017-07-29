#pragma once

class Time
{
	int Hour;
	int Minute;
public:
	Time();
	Time(int h,int m);
	Time operator -(const Time temp);
	~Time(void);
};
