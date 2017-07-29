class Key
{
	int key;
public:
	static int comparisons;
	Key(int x=0);
	int the_key()const;
};

bool operator ==(const Key &x,const Key &y);
bool operator >(const Key &x,const Key &y);
bool operator <(const Key &x,const Key &y);
bool operator >=(const Key &x,const Key &y);
bool operator <=(const Key &x,const Key &y);
bool operator !=(const Key &x,const Key &y);

//-------------------------------------------------------------------
int Key::comparisons=0;
//-----------------------------------------------------------------------
Key::Key(int x)
{
	key=x;
}
//-----------------------------------------------------------------------
int Key::the_key()const
{
	return key;
}

bool operator ==(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() == y.the_key();
}

bool operator !=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() != y.the_key();
}
bool operator >=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() >= y.the_key();
}

bool operator <=(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() <= y.the_key();
}

bool operator >(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() > y.the_key();
}

bool operator <(const Key &x, const Key &y)
{
	Key::comparisons++;
	return x.the_key() < y.the_key();
}