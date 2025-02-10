#include <iostream>

// 오늘의 주제 : 타입 변환

// malloc -> void*을 반환하고, 이를 우리가 (타입변환)을 통해 사용했었음


class Knight
{
public:
	int _hp = 10;
};

class Dog
{
public:
	Dog()
	{

	}
	// 타입 변환 생성자
	Dog(const Knight& knight) // Knight를 받아서 Dog 로 변환하는 것
	{
		_age = knight._hp;
	}

	// 타입변환 연산자 (Dog 라는 것을 Knight로 변환)
	operator Knight()
	{
		return (Knight)(*this);
	}

public:
	int _age = 1;
	int _cuteness = 2;
};

class BullDog : public Dog
{
public: 
	bool _french;
};

int main()
{
	//----------------------- 타입 변환 유형 (비트열 재구성 여부) ------------------------------------

	// [1] 값 타입 변환
	//  특징) 의미를 유지하기 위해서, 원본 객체와 다른 비트열 재구성
	{
		int a = 123456789;
		float b = (float)a;
	}
	 
	// [2] 참조 타입 변환
	// 특징 ) 비트열을 재구성하지 않고, '관점' 만 바꾸는 것
	{
		int a = 123456789; // 2의 보수
		float b = (float&)a;
		std::cout << b << std::endl;
	}

	// ----------------------안전도 분류 ---------------------------------
	
	// [1] 안전한 변환
	// 특징) 의미가 항상 100% 완전히 일치하는 경우
	// 같은 타입이면서 크기만 더 큰 바구니로 이동
	// 작은 바구니 -> 큰 바구니로 이동 OK (업캐스팅)
	// ex ) char -> short, short -> int, int -> __int64
	{
		int a = 123456789;
		__int64 b = a;

		std::cout << b << std::endl;
	}


	// [2] 불완전한 변환
	// 특징) 의미가 항상 100% 일치한다고 보장하지 못하는 경우
	// 타입이 다르거나
	// 같은 타입이지만 큰 바구니 -> 작은 바구니 이동 (다운캐스팅)
	{
		int a = 123456789;
		float b = a;
		short c = a;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
	}

	// ------------------------------ 프로그래머 의도에 따라 분류 -------------------------------
	
	// [1] 암시적 변환
	// 특징) 이미 알려진 타입 변환 규칙에 따라서 컴파일러 '자동'으로 타입 변환
	{
		int a = 123456789;
		float b = a; // 암시적으로
		std::cout << b << std::endl;
	}


	// [2] 명시적 변환
	{
		int a = 123456789;
		int* b = (int*)a; // 명시적
		std::cout << b << std::endl;
	}

	// ------------------------------ 아무런 연관 관계가 없는 클래스 사이의 변환 --------------------

	// [1] 연관없는 클래스 사이의 '값 타입' 변환
	// 특징) 일반적으로 안 됨 (예외: 타입 변환 생성자, 타입 변환 연산자)
	{
		Knight knight;
		Dog dog = (Dog)knight;

		Knight knight2 = dog;
	}
	// [2] 연관없는 클래스 사이의 참조 타입 변환 
	// 특징 ) 참조타입은 명시적으로 하면 OK해준다.
	{
		Knight knight;

		// 어셈블리 언어 관점 : 포인터 = 참조

		// [주소] -> [Dog]
		Dog& dog = (Dog&)knight; // Knight 4바이트 Dog는 8바이트 메모리 오버?
		dog._cuteness = 12;
	}

	// ------------------------------- 상속 관계가 없는 클래스끼리..? -----------------------------------
	// 특징) 자식 -> 부모 OK / 부모 -> 자식 NO
	// [1] 상속 관계 클래스의 값 타입 변환
	{
		//Dog dog; 
		//BullDog bulldog = (Bulldog)dog;

		BullDog bulldog;
		Dog dog = bulldog;
	}

	// [2] 상속 관계 클래스의 참조 타입 변환
	// 특징) 자식 -> 부모 OK / 부모 -> 자식 (암시적NO) (명시적 OK)
	{
		// 명시적으로 하면 통과 시켜준다.
		//Dog dog;
		//BullDog& bulldog = (BullDog&)dog;
	

		// [age cuteness french ]
		BullDog bulldog;
		Dog& dog = bulldog;
	}

	// 결론)
	// [값 타입 변환] : 진짜 비트열도 바꾸고 논리적으로 말이 되게 바꾸는 변환
	// - 논리적으로 말이 된다? (ex. BullDog -> Dog) OK
	// - 논리적으로 말이 안 된다 (ex. Dog -> BullDog, Dog-> Knight) 안 됨
	// [참조 타입 변환] : 비트열은 냅두고 우리의 '관점'만 바꾸면 변환
	// - 땡깡 부리면(명시적 요구) 해주긴 하는데, 말 안 해도 '그냥' (암시적)으로 해주는지는 안전성 여부를 연관 있음
	// -- 안전하다? (ex. BullDog -> Dog&) '그냥' (암시적으로) OK
	// -- 위험하다? (ex. Dog -> BullDog&)
	// --- 메모리 침범 위험이 있는 경우는 '그냥' (암시적으로) 해주진 않음 (위험하니까)
	// --- 명시적으로 정말 정말 하겠다고 최종서명을 하면 OK

	return 0;
}