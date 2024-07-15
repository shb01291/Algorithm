#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> visited(6, false);

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);
	

	/*
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);
	*/

	//���� ���
	adjacent = vector<vector<int>>
	{
		{0, 1, 0, 1, 0, 0},
		{1, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
	};
	
	
}
void Dfs(int here) //�湮�� ��� �����ؾ� ��ȯ �߻�x
{
	visited[here] = true;
	cout << "Visited: " << here<< endl;
	//���� ����Ʈ version
	//��� ���� ���� ��ȸ
	
	// 

	for (int i = 0; i < adjacent[here].size(); i++)
	{
		cout << "now im "<<here << endl;
		int there = adjacent[here][i];//�����Ұ�
		
		if (visited[there] == false)
			Dfs(there);
	}
}

void DfsAll()
{
	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
			Dfs(i);
	}
}

void Mdfs(int here)
{
	visited[here] = true;
	cout << "Visited: " << here << endl;

	for (int there=0; there < 6; there++)
	{
		if (adjacent[here][there] == 0)
			continue;
		//���� �湮���� ���� ���� ������, �湮�Ѵ�
		if (visited[there] == false)
			Mdfs(there);
	}
}