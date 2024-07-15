#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>
using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(BNode* node, int x, int y)
{
	if (node == nullptr)
		return;

	SetCursorPosition(x, y);
	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y+1);
	Print(node->right, x + (5 / (y + 1)), y+1);
}

void BinarySearchTree::Print_Inorder(BNode* node)
{
	//preorder traverse
	//inorder
	//postorder

	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

BNode* BinarySearchTree::Search(BNode* node, int key)
{
	if (node == nullptr || key == node->key)
		return node;
	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

BNode* BinarySearchTree::Search2(BNode* node, int key)
{
	while (node&&key!=node->key)
	{
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

BNode* BinarySearchTree::Min(BNode* node)
{
	while (node->left)
		node = node->left;

	return node;
}

BNode* BinarySearchTree::Max(BNode* node)
{
	while (node->right)
		node = node->right;

	return node;
}

BNode* BinarySearchTree::Next(BNode* node)
{
	if(node->right)
	return Min(node->right);

	BNode* parent = node->parent;
	while (parent && node == parent->right) //자신을 왼쪽 자손으로 가지고 있다면 끝
	{
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void BinarySearchTree::Insert(int key)
{
	BNode* newNode = new BNode();
	newNode->key = key;
	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	BNode* node = _root;
	BNode* parent = nullptr;

	while (node)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;
	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

}

void BinarySearchTree::Delete(int key)
{
	BNode* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(BNode* node)
{
	if (node == nullptr)
		return;
	if (node->left == nullptr)
		Replace(node, node->right);
	else if(node->right==nullptr)
		Replace(node, node->left);
	else
	{
		//다음 데이터 찾기
		BNode* next = Next(node);
		node->key = next->key;
		Delete(next);
	}

}

//u 서브 트리를 v 서브트리로 교체
void BinarySearchTree::Replace(BNode* u, BNode* v)
{
	if (u->parent == nullptr)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if (v)
		v->parent = u->parent;

	delete u;
}
