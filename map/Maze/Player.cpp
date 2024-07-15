#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <map>
#include <queue>
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;
	_path.clear();
	_path.push_back(pos);

	//������ �����ϱ� ������ ��� ����
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos{-1, 0}, //up
		Pos{0, -1},//left
		Pos{1, 0},//down
		Pos{0, 1}//right
	};
	while (pos != dest)
	{
		//1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			_dir = newDir; //������ �������� 90�� ȸ��

			pos += front[_dir]; //������ �Ѻ� ����

			_path.push_back(pos); //��ǥ ����

			//������ �������� 90�� ȸ�� �� ������ �� �� ����
		}
		//2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			//������ �Ѻ� ����
			pos += front[_dir];
				_path.push_back(pos);
		}
		else
		{
			//���� �������� 90�� ȸ��
			_dir = (_dir + 1) % DIR_COUNT;

		}
	}
}

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }
	int32 f; // f = g+h
	int32 g;
	Pos pos;
};

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}
		
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType==TileType::EMPTY;
}

void Player::AStar()
{
	// ���� �ű��
	// F = G + H
	// F=���� ���� (���� ���� ����, ��ο� ���� �޶���)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���
	// H = ���������� �󸶳� ������� ( ���� ���� ����, ���� ��)
	Pos start = _pos;
	Pos dest = _board->GetExitPos();

	enum
	{
		DIR_COUNT = 4
	};

	Pos front[] =
	{
		Pos{-1, 0}, //Up
		Pos{0, -1}, //Left
		Pos{1, 0}, //Down
		Pos{0, 1}, //Right
		Pos{-1, -1}, //Up_left
		Pos{1, -1}, //Down_left
		Pos{1, 1}, //down_right
		Pos{-1, 1} //Up_right

	};

	int32 cost[] =
	{
		10, //Up
		10, //LEFT
		10, //Down
		10,//right
		14, //�밢
		14,
		14,
		14
	};
	const int32 size = _board->GetSize();

	//closedList
	//closed[y][x] -> (y, x)�� �湮�� �ߴ���
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	//best[y][x] -> ���ݱ��� (y, x)�� ���� ���� ���� ��� ( ���� ���� ����)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	//�θ� ���� �뵵
	map<Pos, Pos> parent;

	//openlist �߰��� ������ �湮�� ���� ���� ����
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	//1) ����(�߰�) �ý��� ����
	//2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> ���� ó�� �ʼ�

	//�ʱⰪ
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		//���� ���� �ĺ� ã��
		PQNode node = pq.top();
		pq.pop();
		// ������ ��ǥ�� ���� ��η� ã�Ƽ�, �� ���� ��η� ���� �̹� �湮 ������ ��� ��ŵ
		//closed list�� ����ϴ� ���
		if (closed[node.pos.y][node.pos.x])
			continue;
		//best���� ����� ���
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		//�湮
		// 
		closed[node.pos.y][node.pos.x] = true;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			//�� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;
			//[����]�̹� �湮�� ���̸� ��ŵ
			if (closed[nextPos.y][nextPos.x])
				continue;

			//��� ���
			int32 g = node.g + cost[dir]; //���� ��ǥ + ���� ��ǥ�� �̵��ϴµ� ��� ���
			int32 h=110 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			//�ٸ� ��ο��� �� �������� ã������ ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			//���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;

		}
		//�������� ���������� ����
		if (node.pos == dest)
			break;
	}
	Pos pos = dest;
	_path.clear();
	_pathIndex = 0;

	while (true)
	{
		_path.push_back(pos);

		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}
	std::reverse(_path.begin(), _path.end());
}
