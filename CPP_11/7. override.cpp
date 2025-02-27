#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// ������ ���� : override, final
// �ڼյ鿡�� �����Ǹ� �� �� ���� ����� ���� final�̴�.


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
	// ������ (override)
public:
	virtual void Attack() override // override �����Ϸ��� �ùٸ� �����Ǹ� üũ�ϵ��� ���� ����
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
