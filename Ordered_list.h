#pragma once
#include"List.h"
#include<iostream>
using namespace std;

class Ordered_list :public List<Record> {
public:
	Ordered_list() {};
	Error_code insert(const Record& data);
	Error_code insert(int position, const Record& data);
	
};

