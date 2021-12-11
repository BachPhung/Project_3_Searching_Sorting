#include "Key.h"
#include<iostream>
using namespace std;

int Key::comparisons = 0;
int Key::assignments = 0;

Key::Key(int x) {
    this->key = x;
}

int Key::the_key() const {
    return this->key;
}

Key& Key::operator=(const Key& original) {
    Key::assignments++;
    key = original.key;
    return *this;
}

bool operator== (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() == y.the_key();
}

bool operator> (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() > y.the_key();
}

bool operator< (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() < y.the_key();
}

bool operator>= (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() >= y.the_key();
}

bool operator<= (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() <= y.the_key();
}


bool operator!= (const Key& x, const Key& y) {
    Key::comparisons++;
    return x.the_key() != y.the_key();
}

ostream& operator << (ostream& os, const Key& k){
    os << k.the_key();
    return os;
}