#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"
#include "Node.h"
#include "Iterator.h"


using namespace std;


template<typename T>
class List
{
public:
    List() : _size(0)
    {
        _head = new Node<T>();
        _tail = new Node<T>();
        _head->_next = _tail;
        _tail->_prev = _head;

    }
    ~List()
    {
        while (_size > 0)
            pop_back();

        delete _head;
        delete _tail;
    }
    void push_back(const T& value)
    {
        AddNode(_tail, value);
    }
    void pop_back()
    {
        RemoveNode(_tail->_prev);

    }
private:

    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* prevNode = before->_prev;

        prevNode->_next = newNode;
        newNode->_prev = prevNode;

        newNode->_next = before;
        before->_prev = newNode;

        _size++;

        return newNode;
    }

    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;
        delete node;
        _size--;

        return nextNode;
    }

    int size() { return _size; }

public:
    using iterator = Iterator<T>;

    iterator begin() { return iterator(_head->_next); }
    iterator end() { return iterator(_tail); }
    iterator insert(iterator it, const T& value)
    {
        Node<T>* node = AddNode(it._node, value);
        return (node);
    }

    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    }


private:
    Node<T>* _head;
    Node<T>* _tail;
    int _size;
};