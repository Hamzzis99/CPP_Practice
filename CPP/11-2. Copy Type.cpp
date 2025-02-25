#include <iostream>

// 오늘의 주제 : 얕은 복사 vs 깊은 복사
class Pet
{
public:
	Pet()
	{
		std::cout << "Pet()" << std::endl;
	}
	~Pet()
	{
		std::cout << "Pet()" << std::endl;
	}
	Pet(const Pet& pet)
	{
		std::cout << "Pet(const Pet&)" << std::endl;
	}

	Pet& operator=(const Pet& pet)
	{
		std::cout << "operator = (const Pet&)" << std::endl;
		return *this;
	}
};

class RabbitPet : public Pet
{

};

class Player
{
public:
	Player()
	{
	std::cout << "Player()" << std::endl;
	}
	
	// 복사 생성자
	Player(const Player& player)
	{
	std::cout << "Player(const Player&)" << std::endl;
	_level = player._level;
	}

	Player& operator=(const Player& player)
	{
		std::cout << "operator = (const Player&)" << std::endl;
		_level = player._level;
		return *this;
	}
public:
	int _level = 0;
};


class Knight : public Player
{
public:
	Knight()
	{

	}

	Knight(const Knight& knight) : Player(knight), _pet(knight._pet) // : 이후가 복사 생성자 명시적 선언
	{
		std::cout << "Knight(const Knight&)" << std::endl;

		_hp = knight._hp; //이건 얕은복사 방식
	}

	Knight& operator=(const Knight& knight) //깊은 복사를 할 경우 오퍼레이터에도 변수 선언.
	{
		std::cout << "operator(const Knight&)" << std::endl;

		Player::operator=(knight);

		_pet = knight._pet;

		_hp = knight._hp; 
		return *this; //깊은 복사의 마무리 this 포인터
	}

	~Knight()
	{

	}

public:
	int _hp = 100;
	Pet _pet;
};

int main()
{

	Knight knight; // 기본 생성자
	knight._hp = 200;
	knight._level = 99;

	//std::cout << " -------------- 복사 생성자 ----------------" << std::endl;
	//Knight knight2 = knight; // 복사 생성자
	//Knight knight3(knight);

	Knight knight3; // 기본 생성자
	std::cout << " -------------- 복사 대입 연산자 ----------------" << std::endl;
	knight3 = knight; // 복사 대입 연산자

	// [복사 생성자] + [복사 대입 연산자]
	// 둘 다 안 만들어주면 컴파일러 '암시적으로' 만들어준다

	// 중간 결론) 컴파일러가 알아서 잘 만들어준다?
	// 수고하세요~ 다음 주제 넘어갈까요? << NO

	// [얕은 복사 Shallow Copy]
	// 멤버 데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값을 그대로 복사)
	// 포인터는 주소값 바구니 -> 주소값을 똑같이 복사 -> 동일한 객체를 가리키는 상태가 됨.
	// Stack : Knight [ hp 0x1000	] 
	//									-> Heap 0x1000 Pet[	]
	// Stack : Knight [ hp 0x1000	] 

	// [깊은 복사 Deep Copy]
	// 멤버 데이터가 참조(주소) 값이라면, 데이터를 새로 만들어준다. (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
	// 포인터는 주소값 바구니 -> 새로운 객체를 생성 -> 상이한 객체 가리키는 상태가 됨.
	// Stack : Knight [ hp 0x1000	] -> Heap 0x1000 Pet[	]
	// Stack : Knight [ hp 0x2000	]								
	// Stack : Knight [ hp 0x3000	] 

	// 실험)
	// - 암시적 복사 생성자 Steps
	// 1) 부모 클래스 복사 생성자 호출
	// 2) 멤버 클래스의 복사 생성자 호출
	// 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 Shallow Copy)
	
	// - 명시적 복사 생성자 Steps
	// 1) 부모 클래스의 기본 생성자 호출
	// 2) 멤버 클래스의 기본 생성자 호출
	// 즉 명시적은 프로그래머의 책임으로 복사 생성 하기 때문에..
	
	// - 암시적 복사 대입 연산자 Steps
	// 1) 부모 클래스 복사 생성자 호출
	// 2) 멤버 클래스의 복사 생성자 호출
	// 3) 멤버가 기본 타입일 경우 메모리 복사 (얕은 복사 Shallow Copy)
	// 
	// - 명시적 복사 대입 연산자 Steps
	// 1) 알아서 해주는 거 없음

	// 왜 이렇게 혼란스러울까?
	// 객체를 '복사' 한다는 것은 두 객체의 값들을 일치시키려는 것
	// 따라서 기본적으로 얕은 복사 (Shallow Copy) 방식으로 동작

	// 명시적 복사가 들어가는 순간 그의 책임은 프로그래머한테 위임하겠다로 의미한다.
	// 즉 깊은 복사를 공부해야겠다.


	return 0;
}