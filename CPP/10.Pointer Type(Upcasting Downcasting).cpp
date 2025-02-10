#include <iostream>

// 오늘의 주제 : 타입 변환 (포인터)
class Knight
{
public:
	int _hp;
};

class Item // 최상위 클래스에게는 virtual
{
public:
	Item()
	{
		std::cout << "Item()" << std::endl;
	}

	Item(int itemType) : _itemType(itemType)
	{
		std::cout << "Item(int itemType)" << std::endl;
	}

	Item(const Item& item)
	{
		std::cout << "Item(const Item&)" << std::endl;
	}


	virtual ~Item()
	{
		std::cout << "~Item()" << std::endl;
	}

	virtual void Test() //객체 자체에 내가 실행되어야 할 함수를 따로 만드는 것.
	{
		std::cout << "Test Item" << std::endl;

	}
public:
	int _itemType = 0;
	int _itemDbId = 0;

	char _dummy[4096] = {}; // 이런 저런 정보들로 인해 비대해진
};

enum ItemType
{
	IT_WEAPON = 1,
	IT_ARMOR = 2,
};

class Weapon : public Item
{
public:
	Weapon() : Item(IT_WEAPON)
	{
		std::cout << "Weapon()" << std::endl;
		_damage = rand() % 100;
	}
	virtual ~Weapon()
	{
		std::cout << "~Weapon()" << std::endl;
	}

	virtual void Test() {
		std::cout << "Test Weapon" << std::endl;
	}

public:
	int _damage = 0;
};

class Armor : public Item
{
public:
	Armor() : Item(IT_ARMOR)
	{
		std::cout << "Armor()" << std::endl;
	}
	virtual ~Armor()
	{
		std::cout << "~Armor()" << std::endl;
	}
public:
	int _defence = 0;
};

void TestItem(Item item)
{
	
}

void TestItemPtr(Item* item)
{
	item->Test();
}

int main()
{
	//연관성이 없는 클래스 사이의 포인터 변환 테스트
	{
		// Stack [주소] -> Heap [ _hp(4) ]
		Knight* knight = new Knight();


		// 암시적 NO 명시적 OK (명시적은 최종결정 서명이라고 생각하자)

		// Stack [ 주소 ] <- 이런 캐스팅 잘못하는 상황은 없어야만 한다.
		//Item* item = (Item*)knight;
		//item->_itemType = 2;
		//item->_itemDbId = 1;

		delete knight;
	}
	// 부모 -> 자식 변환 테스트
	{
		Item* item = new Item();

		// [ [ Item ]	]
		// [	_damage	]
		//Weapon* weapon = (Weapon*) item;
		//weapon->_damage = 10;

		delete item;
	}

	// 자식 -> 부모 변환 테스트
	{
		// [ [ Item ]	]
		// [	_damage	]
		Weapon* weapon = new Weapon();


		// 암시적으로도 된다.
		Item* item = weapon;

		TestItemPtr(item);

		delete weapon;
	}

	// 명시적으로 타입 변환할 때는 항상 항상 조심해야 한다!
	// 암시적으로 될 때는 안전하다?
	// -> 평생 명시적으로 타입 변환(캐스팅)은 안 하면 되는거 아닌가?

	Item* inventory[20] = {};

	srand((unsigned int)time(nullptr));
	for (int i = 0; i < 20; i++)
	{
		int randValue = rand() % 2; // 0 ~ 1
		switch (randValue)
		{
		case 0:
			inventory[i] = new Weapon();
			break;
		case 1:
			inventory[i] = new Armor();
			break;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;

		if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;
			std::cout << "Weapon Damage : " << weapon->_damage << std::endl;
		}
	}


	// *********************** 매우 매우 매우 중요 **********************************************
	//상속 관계가 있다면 부모 클래스 소멸자 함수에는 꼭 virtual을 붙여라!!!

	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;
		delete item;

	}
	
	// [결론]
	// - 포인터 vs 일반 타입 : 차이를 이해하자
	// 복사 방식으로 넘기면 생명체가 하나더 생겨서 기본생성 소멸이 있어야 하고
	// 포인터는 원격제어라고 생각하자. 

	// - 포인터 사이의 타입 변환 (캐스팅)을 할 때는 매우 매우 조심해야 한다!
	// 컴파일러가 자동으로 해주지 않는 명시적일 경우 더욱더 조심해야 한다.
	// - 부모- 자식 관계에서 부모 클래스의 소멸자에는 까먹지 말고 무조건 virtual을 붙이자!!! <- 이거 이유 면접에 대해서 나온다!
	


	return 0;
}