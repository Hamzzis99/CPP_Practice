#include <iostream>

// 오늘의 주제 : 은닉성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성 (안전하게 하기 위한 은닉이라 보는 것이 좋다.)
// - 다형성

// 다형성 (Polymorphism = Poly + morph) = 겉은 똑같은데, 기능이 다르게 동작한다.
// - 오버로딩(Overloading) = 함수 중복 정의 = 함수 이름의 재사용 (함수 이름을 똑같은 이름으로 사용한다..)
// - 오버라이딩(Overriding) = 재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의

// 바인딩(Binding) = 묶는다.
// - 정적 바인딩(Static Binding) : 컴파일 시점에 결정
// - 동적 바인딩(Dynamic Binding) : 실행 시점에 결정 (면접 단골 질문..?) (오버로딩 오버라이딩인가?

// 일반 함수는 정적 바인딩을 사용
// 동적 바인딩을 원한다면? -> 가상 함수 (virtual function)

//그런데 실제 객체가 어떤 타입인지 어떻게 알고 알아서 가상함수를 호출해준걸까?
// - 가상 함수 테이블 (vftable)

// .vftable [] 4바이트(32) 8바이트(64)
// [VMove] [VDie]

// 순수 가상 함수 : 구현은 없고 '인터페이스'만 전달하는 용도로 사용하고 싶을 경우
// 추상 클래스 : 순수 가상 함수가 1개 이상 포함되면 바로 추상 클래스로 간주
// - 직접적으로 객체를 만들 수 없게 됨.

class Player 
{
public:

	Player()
	{
		_hp = 100;
	}

	void Move() { std::cout << "Move Player!" << std::endl; }

	//함수 이름이 같아도 받는 인자가 다르면 실행 가능 오버로딩이라 부름
	//void Move(int a) { std::cout << "Move Player" << std::endl; } 
	virtual void VMove() { std::cout << "VMove Player!" << std::endl; }
	virtual void VDie() { std::cout << "VDie Player!" << std::endl; }

	// 순수 가상 함수 <- 사용하면 Player을 단독으로 객체를 사용할 수 없다...?
	virtual void VAttack() = 0;

public:
	int _hp;
};

class Knight : public Player
{
public:
	void Move() { std::cout << "Move Knight!" << std::endl; }

	//가상 함수는 재정의를 하더라도 가상 함수다!
	virtual void VMove() { std::cout << "Move Knight!" << std::endl; }
	virtual void VDie() { std::cout << "VDie Player!" << std::endl; }

	// 순수 가상 함수
	virtual void VAttack() { std::cout << "VAttack Knight" << std::endl; }

public:
	int _stamina;
};

class Mage : public Player
{

public:
	int _mp;
};

// [ [ Player ] ]
// [   Knight	]


void MovePlayer(Player* player) // 그냥 해당 주소로 뿅 하고 이동하는 게 virtual??
{
	player->VMove();
	player->VDie();
}


int main()
{
	//Player p; <- 혼자 독립적으로 만들 수는 없다.
	//MovePlayer(&p); // 플레이어는 플레이어다? Yes
	//MoveKnight(&p); // 플레이어는 기사다? NO

	Knight k;
	//MoveKnight(&k); // 기사는 기사다? Yes
	MovePlayer(&k); // 기사는 플레이어다? Yes
	

	return 0;
}
