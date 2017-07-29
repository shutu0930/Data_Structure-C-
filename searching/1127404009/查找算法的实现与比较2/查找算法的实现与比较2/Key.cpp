#include "Key.h"
int Key::comparisions=0;
int Key::the_key()const
{
	return key;
}
Key::Key (int x)
{
	key = x;
}

Key::~Key(void)
{
}
bool operator == (const Key&x,const Key &y)
{
	Key::comparisions++;
	return x.the_key()==y.the_key();

}

bool operator !=(const Key &x, const Key &y)
{
	Key::comparisions++;
	return x.the_key() != y.the_key();
}
bool operator >=(const Key &x, const Key &y)
{
	Key::comparisions++;
	return x.the_key() >= y.the_key();
}
bool operator <=(const Key &x, const Key &y)
{
	Key::comparisions++;
	return x.the_key() <= y.the_key();
}
bool operator >(const Key &x, const Key &y)
{
	Key::comparisions++;
	return x.the_key() > y.the_key();
}
bool operator <(const Key &x, const Key &y)
{
	Key::comparisions++;
	return x.the_key() < y.the_key();
}
