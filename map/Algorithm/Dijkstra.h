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

	list<VertexCost> discoverd; //�߰� ���
	vector<int> best(6, INT32_MAX);//�� �������� ���ݱ��� �߰��� �ּҰŸ�
	vector<int> parent(6, -1);

	discoverd.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;

	while (discoverd.empty()==false)
	{
		//���� ���� �ĺ��� ã�´�.
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

		//�湮 �� �� ª�� ��θ� ã�Ҵٸ� ��ŵ

		if (best[here] < cost)
			continue;
		//�湮


		for (int there = 0; there < 6; there++)
		{
			//������� �ʾҴٸ� ��ŵ
			if (adjacent[here][there] == -1)
				continue;

			// ���ſ� ã�� ��ΰ� �� ���ٸ� ��ŵ
			int nextCost = best[here] + adjacent[here][there];//���������� ���� �Ÿ�
			if (nextCost >= best[there])
				continue;

			discoverd.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
			
		}
	}
}

