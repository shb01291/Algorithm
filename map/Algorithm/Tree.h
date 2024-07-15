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
	NodeRef root = make_shared<Node2>("R1 개발실");
	{
		NodeRef node = make_shared<Node2>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("스토리");
			node->children.push_back(leaf);
		}
	}

	{
		NodeRef node = make_shared<Node2>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("엔진");
			node->children.push_back(leaf);
		}	
	}
	{
		NodeRef node = make_shared<Node2>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node2>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node2>("캐릭터");
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
		height = max(height, GetHeight(child) + 1);//각각 다를 수 있다. 따라서 가장 큰 값을 추출해야
	}
	return height;
}