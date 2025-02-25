#include <iostream>

// 오늘의 주제 : 캐스팅 (타입 변환)

// 1) static_cast
// 2) dynamic_cast
// 3) const_cast
// 4) reinterpret_cast

class Player
{
public:
	virtual ~Player() {}
};

class Knight : public Player
{

public:
};

class Archer : public Player
{

public:
};


int main()
{
	// static_cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다.
	//1) int <-> float
	//2) Player* -> Knight* (다운캐스팅) << 단, 안정성 보장 못함

	int hp = 100;
	int maxHp = 200;
	float ratio = static_cast<float>(hp) / maxHp;

	// 부모 -> 자식, 자식 -> 부모
	Player* p = new Archer();
	Knight* k1 = static_cast<Knight*>(p);

	// dynamic_cast : 상속 관계에서의 안전 형변환
	// RTTI (RunTime Type Information)
	// 다형성을 활용하는 방식
	// - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상 테이블 (vftable) 주소가 기입된다.
	// -  만약 잘못된 타입으로 캐스팅을 했으면, nullptr 반환 **********************
	// 이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인을 유용하다.
	Knight* k2 = dynamic_cast<Knight*>(p); 

	//const_cast
	return 0;
}