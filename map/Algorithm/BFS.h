#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Vertex2
{
	//item
};

vector<Vertex2> vertices2;
vector<vector<int>> adjacent2;
vector<bool> discovered(6, false); //발견 여부

void CreateGraphForBFS()
{
	vertices2.resize(6);
	adjacent2 = vector<vector<int>>(6);

	adjacent2[0].push_back(1);
	adjacent2[0].push_back(3);
	adjacent2[1].push_back(0);
	adjacent2[1].push_back(2);
	adjacent2[1].push_back(3);
	adjacent2[3].push_back(4);
	adjacent2[5].push_back(4);


}

void Bfs(int here)
{

	//누구에 의해 발견?
	vector<int> parent(6, -1);
	vector<int> distance(6, -1);

	parent[here] = here;
	distance[here] = 0;

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	while (q.empty()==false)
	{
		here = q.front(); 
		q.pop();

		cout << "Visited Here : " << here << endl;

		for (int there : adjacent2[here])
		{
			if (discovered[there])
				continue;
			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}
}

void BfsAll()
{
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false)
			Bfs(i);
	}
}

