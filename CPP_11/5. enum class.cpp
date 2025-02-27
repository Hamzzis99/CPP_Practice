#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// enum class

// unscoped enum (범위 없는)
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
	// 1) 이름공간 관리 (scoped)
	// 2) 암묵적인 변환 금지
	double value = PT_Knight; // 일반적인 enum은 실수로 변환이 된다?

	int choice;
	cin >> choice;

	//double value2 = Player; // 막힌다! 명시적으로 사용시 가능
	double value = static_cast<double>(ObjectType::Player);

	if (choice == static_cast<int>(ObjectType::Monster))
	{

	}

	unsigned int bitFlag;
	bitFlag = (1 << static_cast<int>(ObjectType::Player));

	//결론 enum class는 enum과 같지만 형변환은 명시적으로 사용하여야 한다!

	return 0;
}