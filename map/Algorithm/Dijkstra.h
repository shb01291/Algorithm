#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;


struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraphForDijikstra()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;

}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discoverd; //발견 목록
	vector<int> best(6, INT32_MAX);//각 정점별로 지금까지 발견한 최소거리
	vector<int> parent(6, -1);

	discoverd.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;

	while (discoverd.empty()==false)
	{
		//제일 좋은 후보를 찾는다.
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;
		

		for (auto it = discoverd.begin(); it != discoverd.end(); it++)
		{

			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discoverd.erase(bestIt);

		//방문 시 더 짧은 경로를 찾았다면 스킵

		if (best[here] < cost)
			continue;
		//방문


		for (int there = 0; there < 6; there++)
		{
			//연결되지 않았다면 스킵
			if (adjacent[here][there] == -1)
				continue;

			// 과거에 찾은 경로가 더 좋다면 스킵
			int nextCost = best[here] + adjacent[here][there];//시작점으로 부터 거리
			if (nextCost >= best[there])
				continue;

			discoverd.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
			
		}
	}
}

