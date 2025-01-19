#include <iostream>


//오늘의 주제 : 상속성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성
// - 다형성

struct Statinfo
{
	int hp;
	int attack;
	int defence;
};

// 메모리
// 아파트 구조 방식. Player -> 다음층 Knight
// 
// [	Knight	]
// [ [ Player]  ]
// 


// 상속(Inheritance) ? 부모 -> 자식에게 유산을 물려주는 것

// 생성자(N) / 소멸자(1)

// 생성자는 탄생을 기념해서 호출되는 함수?
// - Knight를 생성하면 -> Player의 생성자? Knight의 생성자?
// -> 솔로몬의 선택 ! 그냥 둘 다 호출하자 !

// GameObject를 최상위로 둔다 (보통 게임을 만들 때)
// - Creature
// -- Player, Monster, Npc, Pet
// 
// - Projectile 
// -- Arrow, Fireball
// - Env (채집물)

// Item
// - Weapon
// -- Sword, Bow
// - Armor
// -- Helment, Boots, Armor
// - Consumable
// - Potion, Scroll

class GameObject
{
public:
	int _objectid;
};

class Player : public GameObject
{
public:
	Player()
	{
		_hp = 0;
		_attack = 0;
		_defence = 0;
		std::cout << "Player() 기본 생성자 호출" << std::endl;
	}

	Player(int hp)
	{
		_hp = hp;
		_attack = 0;
		_defence = 0;
		std::cout << "Player(int hp) 기본 생성자 호출" << std::endl;
	}

	~Player()
	{
		std::cout << "~Player() 소멸자 호출" << std::endl;
	}


	void Move() { std::cout << "Player Move 호출" << std::endl; }
	void Attack() { std::cout << "Player Attack 호출" << std::endl; }
	void Die() { std::cout << "Player Die 호출" << std::endl; }

public:
	int _hp;
	int _attack;
	int _defence;
};

// class는 일종의 설계도
class Knight : public Player
{
public:
	Knight()
		/*
			선(먼저)처리 영역
			- 여기서 Player() 생성자를 호출
		*/
	{
		_stamina = 100;
		std::cout << "Knight() 기본 생성자 호출" << std::endl;
	}


	Knight(int stamina) : Player(100)
		/*
			선(먼저)처리 영역
			- 여기서 Player(int hp) 생성자를 호출
		*/
	{
		_stamina = stamina;
		std::cout << "Knight(int hp) 기본 생성자 호출" << std::endl;
	}


	~Knight()
	{
		std::cout << "~Knight() 소멸자 호출" << std::endl;
	}
	/*
		후(나중에)처리 영역
		- 여기서 Player() 소멸자를 호출
	*/


	// 재정의 : 부모님의 유산을 거부하고 새로운 이름으로 만든 것.
	void Move()
	{
		std::cout << "Knight Move 호출" << std::endl;
	}

public:
	int _stamina;
};

// class는 일종의 설계도
class Mage : public Player
{
public:

public:
	int _mp;
};

int main()
{
	Knight k(100);

	k._hp = 100;
	k._attack = 10;
	k._defence = 5;
	k._stamina = 50;

	//k.Move();
	//k.Player::Move(); // 이런 문장은 쓰지 않는다..

	//k.Attack();
	//k.Die();

	return 0;
}