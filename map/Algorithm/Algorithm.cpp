#include <iostream>
#include <vector>
#include "Node.h"
#include "Vector.h"
#include "Iterator.h"
#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "DFS.h"
#include "BFS.h"
#include "Tree.h"
#include <stack>
#include <queue>
#include "PriorityQueue.h"
#include "BinarySearchTree.h"
using namespace std;



int main()
{
    /*
    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    while (s.empty() == false)
    {
        int data = s.top();//최상위 원소
        s.pop();//최상위 원소 삭제
    }
    

    Stack<int, list<int>> s2; //기본은 vector 리스트로 하고 싶을시 container

    ArrayQueue<int> q;

    for (int i = 0; i < 100; i++)
        q.push(i);

    while (q.empty() == false)
    {
        int value = q.front();
        q.pop();
        cout << value << endl;
    }

    */
    /*
    PriorityQueue<int, vector<int>, greater<int>> pq;

    pq.push(100);
    pq.push(300);
    pq.push(200);
    pq.push(500);
    pq.push(400);

    while (pq.empty() == false)
    {
        int value = pq.top();
        pq.pop();

        cout << value << endl;

    }
    */
    BinarySearchTree bst;

    bst.Insert(20);
    bst.Insert(10);
    bst.Insert(30);
    bst.Insert(25);
    bst.Insert(26);
    bst.Insert(40);
    bst.Insert(50);
    bst.Delete(20);
    bst.Print();

}