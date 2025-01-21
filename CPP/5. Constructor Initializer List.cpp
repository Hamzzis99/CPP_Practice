#include <iostream>

// 오늘의 주제 : 초기화 리스트

// 멤버 변수 초기화 ? 다양한 문법이 존재

// 초기화 왜 해야할까? 귀찮다~

// 초기화 방법
// - 생성자 내에서
// - 초기화 리스트
// - C++11 문법

// 초기화 리스트
// - 일단 상속 관계에서 원하는 부모 생성자 호출할 때 필요하다.
// - 생성자 내에서 초기화 vs 초기화 리스트
// -- 일반 변수는 별 차이 없음
// -- 멤버 타입이 클래스인 경우 차이가 난다.
// -- 정의함과 동시에 초기화가 필요한 경우 (참조 타입, const 타입)

class Inventory
{
public:
	Inventory() { std::cout << "Inventory()" << std::endl; }
	Inventory(int size) { std::cout << "Inventory(int size)" << std::endl; _size = size; }
	~Inventory() { std::cout << "~Inventory" << std::endl; }
public:
	int _size = 10;
};

class Player
{


public:
	Player(){}
	Player(int id) {}
};


// Is - A (Knight Is - a Player? 기사는 플레이어다) OK -> 상속관계

// Has-A (Knight Has-A Inventory? 기사는 인벤토리를 포함하고 있다 갖고있다 OK -> 포함관계

class Knight :public Player
{
public:
	//초기화 리스트
	Knight() : Player(1), _hp(100), _inventory(20), _hpRef(_hp), _hpConst(100) // _hp(100)으로도 초기화를 할 수 있었다...??? C++ 11문법. 모던C++아님 일단 초기화리스트를 이용해서 이렇게 사용해라.

		/*
			선처리 영역

			_inventory = Inventory()
		*/
	{
		_hp = 100;

	}
public:
	int _hp; // 윤교수님의 답변 : 쓰이지 않은 어딘가의 값, 강사의 답변 : (쓰레기 값)
	Inventory _inventory; // 포함관계 (내부에서 새로 만들어주는 게 아니라 한방에 처리할 수 있도록 해야한다.)

	int& _hpRef;
	const int _hpConst;
};

int main()
{
	Knight k;

	std::cout << k._hp << std::endl;

	return 0;
}