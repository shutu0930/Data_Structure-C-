#pragma once
#include <iostream>
using namespace std;

class Time
{
private:
	 int c_hour;
	 int c_minute;
public:
	 Time();
	 Time(int hour,int minute);
	 Time(const Time& time);
	 bool SetTime(int hour,int minute);
	 bool Check_Time()const;
	 bool ReSet_timeArr();
	 bool operator==(const Time& time)const;
	 bool operator>(const Time& time)const;
	 bool operator<(const Time& time)const;
	 bool operator>=(const Time& time)const;
	 bool operator<=(const Time& time)const;
	 bool operator!=(const Time& time)const;
	 const Time operator+(int minute);
	 const Time operator+(const Time& time);
	 const int  operator-(const Time& time);
	 const Time operator-(int minute);
	 const Time operator+=(const Time& time);
	 const Time operator-=(const Time& time);
	 const Time operator=(const Time& time);
	 const Time operator++(int a);
	 const Time operator--(int a);
	 friend const Time operator++(Time& time);
	 friend const Time operator--(Time& time);
	 friend ostream& operator<<(ostream& out,const Time& time);
	 friend istream& operator>>(istream& ins,Time& time);
};
