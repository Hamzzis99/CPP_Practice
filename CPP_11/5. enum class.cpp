#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// enum class

// unscoped enum (���� ����)
enum PlayerType
{
	PT_None,
	PT_Knight,
	PT_Archer,
	PT_Mage,
};

enum MonsterType
{
	MT_None,
};

enum class ObjectType
{
	Player,
	Monster,
	Projectile 
};

int main()
{
	// enum class (scoped enum)
	// 1) �̸����� ���� (scoped)
	// 2) �Ϲ����� ��ȯ ����
	double value = PT_Knight; // �Ϲ����� enum�� �Ǽ��� ��ȯ�� �ȴ�?

	int choice;
	cin >> choice;

	//double value2 = Player; // ������! ��������� ���� ����
	double value = static_cast<double>(ObjectType::Player);

	if (choice == static_cast<int>(ObjectType::Monster))
	{

	}

	unsigned int bitFlag;
	bitFlag = (1 << static_cast<int>(ObjectType::Player));

	//��� enum class�� enum�� ������ ����ȯ�� ��������� ����Ͽ��� �Ѵ�!

	return 0;
}