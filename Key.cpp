#include "Key.h"
#include<iostream>
using namespace std;

int Key::comparisons = 0;

int Key::the_key() const{
    return this->key;
}

bool operator== (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() == y.the_key();
}

bool operator> (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() > y.the_key();
}

bool operator< (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() < y.the_key();
}

bool operator>= (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() >= y.the_key();
}

bool operator<= (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() <= y.the_key();
}

bool operator!= (const Key &x, const Key &y){
    Key::comparisons++;
    return x.the_key() != y.the_key();
}