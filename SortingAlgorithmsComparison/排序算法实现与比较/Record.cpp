#include "Record.h"

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

