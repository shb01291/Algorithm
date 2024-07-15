#pragma once

#include <iostream>
#include <vector>
#include "Vector.h"


template<typename T>
class Node
{
public:
    Node() : _prev(nullptr), _next(nullptr), _data(T())
    {

    }

    Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
    {

    }
public:
    Node* _prev;
    Node* _next;
    T _data;

};
