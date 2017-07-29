#pragma once

class Key {
	int key;
	public:
	static int comparisons;
	static int assignments;
	static void initialize();
	static int counter();
	Key ( int x = 0 );
	int the_key() const;
	Key &operator =(const Key &y);
};
bool operator ==(const Key &y,const Key &x);
bool operator !=(const Key &y,const Key &x);
bool operator >=(const Key &y,const Key &x);
bool operator <=(const Key &y,const Key &x);
bool operator >(const Key &y,const Key &x);
bool operator <(const Key &y,const Key &x);
