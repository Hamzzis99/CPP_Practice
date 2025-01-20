#include <iostream>

// 오늘의 주제 : 은닉성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성 (안전하게 하기 위한 은닉이라 보는 것이 좋다.)
// - 다형성

// 다형성 (Polymorphism = Poly + morph) = 겉은 똑같은데, 기능이 다르게 동작한다.
// - 오버로딩(Overloading) = 함수 중복 정의 = 함수 이름의 재사용
// - 오버라이딩(Overriding) = 재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의

// 바인딩(Binding) = 묶는다.
// - 정적 바인딩(Static Binding) : 컴파일 시점에 결정
// - 동적 바인딩(Dynamic Binding) : 실행 시점에 결정 (면접 단골 질문..?) (오버로딩 오버라이딩인가?

// 일반 함수는 정적 바인딩을 사용
// 동적 바인딩을 원한다면? -> 가상 함수 (virtual function)

class Player
{
public:
	void Move() { std::cout << "Move Player!" << std::endl; }

	//함수 이름이 같아도 받는 인자가 다르면 실행 가능 오버로딩이라 부름
	//void Move(int a) { std::cout << "Move Player" << std::endl; } 
	virtual void VMove() { std::cout << "Move Player!" << std::endl; }

public:
	int _hp;
};

class Knight : public Player
{
public:
	void Move() { std::cout << "Move Knight!" << std::endl; }

	//가상 함수는 재정의를 하더라도 가상 함수다!
	virtual void VMove() { std::cout << "Move Knight!" << std::endl; }

public:
	int _stamina;
};

class Mage : public Player
{

public:
	int _mp;
};

void MovePlayer(Player* player)
{
	player->VMove();
}


int main()
{
	Player p;
	//MovePlayer(&p); // 플레이어는 플레이어다? Yes
	//MoveKnight(&p); // 플레이어는 기사다? NO

	Knight k;
	//MoveKnight(&k); // 기사는 기사다? Yes
	MovePlayer(&k); // 기사는 플레이어다? Yes
	

	return 0;
}
