#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>//greater�� �ٲٸ� ū ������
class PriorityQueue
{
public:
	void push(const T& data)
	{
		_heap.push_back(data);
		//��
		int now = static_cast<int>(_heap.size()) - 1;

		while (now > 0)
		{
			int next = (now - 1) / 2;//parent
			//if (_heap[now] < _heap[next])
				//break;
			if (_predicate(_heap[now], _heap[next]))
				break;
			//������ ��ü
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();
		int now = 0;
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;
			
			//������ ������ ���
			if (left >= _heap.size())
				break;

			int next = now;//�̵��ؾ� �ϴ� index

			//���ʰ� ��
			//if (_heap[next] < _heap[left])
				//next = left;
			if (_predicate(_heap[next], _heap[left]))
				next = left;
			//�� �� ���ڸ� �����ʰ� ��
			//if (right < _heap.size() && _heap[next] <= _heap[right])
				//next = right;
			if(right < (int)_heap.size() && _predicate(_heap[next],_heap[right]))
				next=right;

			//���� ������ �Ѵ� ���� ������ ������ ����
			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;


		}
	}

	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:
	Container _heap = {};
	Predicate _predicate = {};

};