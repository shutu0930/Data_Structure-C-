#pragma once
#include"Key.h"
class Record{
	Key key;
public:
	Record(double x);
	Record();
	operator Key() const; // cast to Key
};
