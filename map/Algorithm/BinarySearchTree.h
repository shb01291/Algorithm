#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct BNode
{
	BNode* parent=nullptr;
	BNode* left=nullptr;
	BNode* right=nullptr;
	int key = {};

};

class BinarySearchTree
{
public:
	void Print() { Print(_root, 10, 0); };
	void Print(BNode* node, int x, int y);
	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(BNode* node);

	BNode* Search(BNode* node, int key);
	BNode* Search2(BNode* node, int key);

	BNode* Min(BNode* node);
	BNode* Max(BNode* node);
	BNode* Next(BNode* node);

	void Insert(int key);
	void Delete(int key);
	void Delete(BNode* node);
	void Replace(BNode* u, BNode* v);
private:
	BNode* _root = nullptr;

};