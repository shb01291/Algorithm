#pragma once

#include "Node.h"

template<typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr)
    {

    }
    Iterator(Node<T>* _node) :_node(Node)
    {

    }

    Iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    Iterator operator++(int)
    {

        Iterator<T> temp = *this;
        _node = _node->_next;
        return temp;
    }

    Iterator& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    Iterator operator--(int)
    {

        Iterator<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    T& operator*()
    {
        return _node->_data;

    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;

    }
    bool operator!=(const Iterator& other)
    {
        return _node != other._node;

    }
public:
    Node<T>* _node;


};