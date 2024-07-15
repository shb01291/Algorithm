#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

using NodeRef = shared_ptr<struct Node2>;

struct Node2
{
	Node2(){}
	Node2(const string& data) : data(data){}
	string data;
	vector<NodeRef> children;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node2>("R1 ���߽�");
	{
		NodeRef node = make_shared<Node2>("��������");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("���丮");
			node->children.push_back(leaf);
		}
	}

	{
		NodeRef node = make_shared<Node2>("���α׷�����");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("Ŭ��");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("����");
			node->children.push_back(leaf);
		}	
	}
	{
		NodeRef node = make_shared<Node2>("��Ʈ��");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("���");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("ĳ����");
			node->children.push_back(leaf);
		}
	}


	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "-";
	cout << root->data << endl;

	for (NodeRef& child : root->children)
		PrintTree(child, depth+1);
}

int GetHeight(NodeRef root)
{
	int height = 1;
	for (NodeRef& child : root->children)
	{
		height = max(height, GetHeight(child) + 1);//���� �ٸ� �� �ִ�. ���� ���� ū ���� �����ؾ�
	}
	return height;
}