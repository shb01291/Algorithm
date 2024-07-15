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

	//목적지 도착하기 전에는 계속 실행
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
		//1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			_dir = newDir; //오른쪽 방향으로 90도 회전

			pos += front[_dir]; //앞으로 한보 전진

			_path.push_back(pos); //좌표 저장

			//오른쪽 방향으로 90도 회전 후 앞으로 한 보 전진
		}
		//2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			//앞으로 한보 전진
			pos += front[_dir];
				_path.push_back(pos);
		}
		else
		{
			//왼쪽 방향으로 90도 회전
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
	// 점수 매기기
	// F = G + H
	// F=최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용
	// H = 목적지에서 얼마나 가까운지 ( 작을 수록 좋음, 고정 값)
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
		14, //대각
		14,
		14,
		14
	};
	const int32 size = _board->GetSize();

	//closedList
	//closed[y][x] -> (y, x)에 방문을 했는지
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	//best[y][x] -> 지금까지 (y, x)에 대한 가장 좋은 비용 ( 작을 수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	//부모 추적 용도
	map<Pos, Pos> parent;

	//openlist 발견은 했지만 방문은 하지 않은 상태
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	//1) 예약(발견) 시스템 구현
	//2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수

	//초기값
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		//제일 좋은 후보 찾기
		PQNode node = pq.top();
		pq.pop();
		// 동일한 좌표를 여러 경로로 찾아서, 더 빠른 경로로 인해 이미 방문 상태인 경우 스킵
		//closed list를 사용하는 경우
		if (closed[node.pos.y][node.pos.x])
			continue;
		//best만을 사용할 경우
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		//방문
		// 
		closed[node.pos.y][node.pos.x] = true;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			//갈 수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;
			//[선택]이미 방문한 곳이면 스킵
			if (closed[nextPos.y][nextPos.x])
				continue;

			//비용 계산
			int32 g = node.g + cost[dir]; //이전 좌표 + 현재 좌표로 이동하는데 드는 비용
			int32 h=110 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			//다른 경로에서 더 빠른길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			//예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;

		}
		//목적지에 도착했으면 종료
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
