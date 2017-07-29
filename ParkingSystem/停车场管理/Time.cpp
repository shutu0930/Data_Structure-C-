#include "Time.h"
using namespace std;

Time::Time()
{
 _hour=0;
 _minute=0;
}

Time::Time(int hour, int minute)
{
 _hour=hour;
 _minute=minute;
}


Time::Time(const Time &time)
{
 _hour=time._hour;
 _minute=time._minute;
}


bool Time::SetTime(int hour, int minute)
{
 _hour=hour;
 _minute=minute;
 return true;
}


bool Time::Check_Time()const
{
 if (_hour<0||_hour>=24||_minute<0||_minute>=60)
  return false;
 return true;
}


bool Time::ReSet_timeArr()
{
 if (Check_Time())
  return true;
 if (_minute<0)
 {
  _hour--;
  _minute+=60;
 }
 else if (_minute>=60)
 {
  _hour++;
  _minute-=60;
 }
 if (_hour<0)
 {
  _hour+=24;
 }
 else if (_hour>=24)
 {
  _hour-=24;
 }
 return true;
}


bool Time::operator ==(const Time &time)const
{
 return ((this->_hour==time._hour)&&(this->_minute==time._minute));
}

bool Time::operator !=(const Time &time)const
{
 return !(*this==time);
}

bool Time::operator >(const Time &time)const
{
 if (_hour>time._hour)
 {
  return true;
 }
 else if (_hour==time._hour&&_minute>time._minute)
 {
  return true;
 }
 else
  return false;
}

bool Time::operator >=(const Time &time)const
{
 if (_hour>time._hour)
 {
  return true;
 }
 else if (_hour==time._minute&&_minute>=time._minute)
 {
  return true;
 }
 else
  return false;
}

bool Time::operator <(const Time &time)const
{
 if (_hour<time._hour)
 {
  return true;
 }
 else if (_hour==time._hour&&_minute<time._minute)
 {
  return true;
 }
 else
  return false;
}


bool Time::operator <=(const Time &time)const
{
 if (_hour<time._hour)
 {
  return true;
 }
 else if (_hour==time._hour&&_minute<=time._minute)
 {
  return true;
 }
 else
  return false;
}


const Time Time::operator +(int minute)
{
 Time temp(*this);
 temp._minute+=minute;
 temp.ReSet_timeArr();
 return temp;
}

const Time Time::operator +(const Time &time)
{
 Time temp;
 temp._hour=_hour+time._hour;
 temp._minute=_minute+time._minute;
 temp.ReSet_timeArr();
 return temp;
}


const Time Time::operator +=(const Time &time)
{
 _hour+=time._hour;
 _minute+=time._minute;
 ReSet_timeArr();
 return *this;
}


const int Time::operator -(const Time& time)
{
 int minute;
 minute=(_hour-time._hour)*60+_minute-time._minute;
 return minute;
}


const Time Time::operator -(int minute)
{
 Time temp(*this);
 temp._minute-=minute;
 temp.ReSet_timeArr();
 return temp;
}


const Time Time::operator -=(const Time& time)
{
 _hour-=time._hour;
 _minute-=time._minute;
 ReSet_timeArr();
 return *this;
}


const Time Time::operator =(const Time& time)
{
 if (!time.Check_Time())
  return Time(-1,-1);
 _hour=time._hour;
 _minute=time._minute;
 return *this;
}


const Time Time::operator++(int a)
{
 Time temp=*this;
 _minute++;
 ReSet_timeArr();
 return temp;
}

const Time Time::operator--(int a)
{
 Time temp=*this;
 _minute--;
 ReSet_timeArr();
 return temp;
}

const Time operator++(Time& time)
{
 time++;
 return time;
}


const Time operator--(Time& time)
{
 time--;
 return time;
}


ostream& operator<<(ostream& out,const Time& time)
{
 if (!time.Check_Time())
 {
  out<<"Error Time!"<<endl;
  return out;
 }
 if (time._hour<10)
 {
  out<<"0"<<time._hour;
 }
 else
 {
  out<<time._hour;
 }
 out<<":";
 if (time._minute<10)
 {
  out<<"0"<<time._minute;
 }
 else
 {
  out<<time._minute;
 }
 return out;
}


istream& operator>>(istream& ins,Time& time)
{
 int hour,minute;
 ins>>hour;
 ins.ignore(1);
 ins>>minute;
 time.SetTime(hour,minute);
 return ins;
}