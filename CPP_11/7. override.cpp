#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// 오늘의 주제 : override, final
// 자손들에게 재정의를 할 수 없게 만드는 것은 final이다.


class Creature
{
public:
	virtual void Attack()
	{
		cout << "Creature!" << endl;
	}
};

class Player : public Creature
{
public:
	virtual void Attack() override
	{
		cout << "Player!" << endl;
	}
};

class Knight : public Player
{
	// 재정의 (override)
public:
	virtual void Attack() override // override 컴파일러가 올바른 재정의를 체크하도록 돕는 역할
	{
		cout << "Knight!" << endl;
	}

private:
	int _stamina = 100;
};


int main()
{
	Player* p = new Knight();

	p->Attack();

	return 0;
}
