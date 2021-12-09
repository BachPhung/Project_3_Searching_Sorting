#pragma once
#include <iostream>
using namespace std;

class Key {
	int key;
public:
	static int comparisons;
	static int assignments;
	Key(int x = 0);
	int the_key() const;
	Key& operator = (const Key& original);
};



bool operator ==(const Key& x, const Key& y);
bool operator >(const Key& x, const Key& y);
bool operator <(const Key& x, const Key& y);
bool operator >=(const Key& x, const Key& y);
bool operator <=(const Key& x, const Key& y);
bool operator !=(const Key& x, const Key& y);
