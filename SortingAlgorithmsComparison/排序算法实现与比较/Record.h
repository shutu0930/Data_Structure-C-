#pragma once
#include"Key.h"
class Record{
	Key key;
public:
	Record(double x);
	Record();
	operator Key() const; // cast to Key
};
Record::Record()
{
	key = 0;
}
Record::Record(double x)
{
	key = x;
}
Record::operator Key() const
{
	return key;
}

