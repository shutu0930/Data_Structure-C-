#include "StdAfx.h"
#include "Time.h"

Time::Time(void)
{
	Hour=0;
	Minute=0;
}
Time::Time(int h, int m)
{
	Hour=h;
	Minute=m;
}
Time::operator -(const Time temp);
{	int h,m,s;
	if(h=(Hour-temp.Hour)>=0)
	{
		if(m=(Minute>=temp.Minute)>=0)
		{
			Time res(h,m)
		}
		else
		{
			Time res(h-1,m+60)
		}
	}
	else
	{
		if(m=(Minute>=temp.Minute)>=0)
		{
			Time res(h+1,-m+60)
		}
		else
		{
			Time res(h,m)
		}
	}
}
Time::~Time(void)
{
}
