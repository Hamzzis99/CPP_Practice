#include <iostream>

// malloc
// - 할당할 메모리 크기를 건내준다
// - 메모리 할당 후 시작 주소를 가리키는 포인터를 반환해준다 (메모리 부족 NULL)

// free
// - malloc (혹은 기타 calloc, realloc 등의 사촌)을 통해 할당된 영역을 해제
// - 힙 관리자가 할당/미할당 여부를 구분해서 관리

//new / delete
// - C++에 추가됨
// - malloc/free 함수! new/delete는 연산자(operator)

// new[] / delete[]
// - new가 malloc에 비해 좋긴 한데~ 배열과 같이 N개 데이터를 같이 할당하려면?

// malloc/free vs new/delete
// -- 사용 편의성 -> new/delete가 더 좋음
// - 타입에 상관없이 특정한 크기의 메모리 영역을 할당받고 싶다? -> malloc/free

// 그런데 둘의 가장 가장 근본적인 중요한 차이는 따로 있음!
// new/delete는 (생성타입이 클래스일 경우) 생성자와 소멸자를 호출해준다!!!

class Monster
{
public:
	Monster()
	{
		std::cout << "Monster()" << std::endl;
	}
	~Monster()
	{
		std::cout << "Monster Delete" << std::endl;
	}
public:
	int _hp;
	int _x;
	int _y;
};

//Monster monster [500 * 10000];




int main()
{
	// 유저 영역 [메모장] [LOL] [곰플레이어] //서로의 존재를 아예 모르는 것 처럼?
	// ----------------------------
	// 커널 영역 (Windows 등의 핵심 코드)

	// 유저 영역) 운영체제에서 제공하는 API 호출
	// 커널 영역 메모리 할당해서 건내줌
	// 유저 영역) ㄳㄳ 잘 쓸게요~

	// [ 

	//void * 이게 무엇일까?
	// *가 있으니까 포인터는 포인터 (주소를 담는 바구니) => OK
	// 타고 가면 void 아무것도 없다 ? => NO
	// 타고 가면 void 뭐가 있는지 모르겠으니까 너가 적당히 변환해서 사용해라 => OK
	void* pointer = malloc(sizeof(Monster));

	Monster* m1 = (Monster*)pointer;
	m1->_hp = 100;
	m1->_x = 1;
	m1->_y = 2;

	free(pointer);

	Monster* m2 = new Monster;
	m2->_hp = 200;
	m2->_x = 2;
	m2->_y = 3;
	delete m2;

	Monster* m3 = new Monster[5]; // 여러마리를 동시에 만들어줘
	m3->_hp = 200;
	m3->_x = 2;
	m3->_y = 3;
	//delete[] m3;

	Monster* m4 = (m3 + 1);
	m4->_hp = 200;
	m4->_x = 2;
	m4->_y = 3;
	delete[] m3;
	return 0;
}