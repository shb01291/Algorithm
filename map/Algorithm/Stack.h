#pragma once

#include<iostream>
#include"Node.h"
#include<vector>
#include<list>
using namespace std;

template<typename T, typename Container=vector<T>>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}


	void pop()
	{
		_container.pop_back();
	}
	T& top()
	{
		return _container.back();
	}
	bool empty()
	{return _container.empty();
	}
private:
	//vector<T> _container;
	//list<T> _container;
	Container _container;
};