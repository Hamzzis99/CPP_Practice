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
};

class RabbitPet : public Pet
{

};


class Knight
{
public:
	Knight()
	{
		_pet = new Pet();
	}

	Knight(const Knight& knight)
	{
		_hp = knight._hp; //이건 얕은복사 방식
		_pet = new Pet(*(knight._pet)); // 깊은 복사를 하기 위한 선언 새로운 객체를 만들어 
	}

	Knight& operator=(const Knight& knight) 
	{
		_hp = knight._hp; //이건 얕은복사 방식
		_pet = new Pet(*(knight._pet)); // 다 다른 pet들의 새로운 객체를 생성해주는 것. (깊은복사)
		return *this; //깊은 복사의 마무리 this 포인터
	}

	~Knight()
	{
		delete _pet;
	}

public:
	int _hp = 100;
	Pet* _pet;
};

int main()
{

	Knight knight; // 기본 생성자
	knight._hp = 200;

	Knight knight2 = knight; // 복사 생성자
	//Knight knight3(knight);

	Knight knight3; // 기본 생성자
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

	return 0;
}