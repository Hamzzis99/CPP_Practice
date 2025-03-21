﻿#include <iostream>

// malloc
// - 할당할 메모리 크기를 건내준다
// - 메모리 할당 후 시작 주소를 가리키는 포인터를 반환해준다 (메모리 부족 NULL)

// free
// - malloc (혹은 기타 calloc, realloc 등의 사촌)을 통해 할당된 영역을 해제
// - 힙 관리자가 할당/미할당 여부를 구분해서 관리

class Monster
{
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

	// Heap Overflow
	// - 유효한 힙 범위를 초과해서 사용하는 문제


	//만약에 free 하지 않으면 메모리 누수
	free(pointer);
	pointer = nullptr; // 실수를 하지 못하게.
	m1 = nullptr; // 실수하지 못하게 2

	// Double Free
	// - 이건 대부분 그냥 크래시만 나고 끝난다.
	// free(pointer);
	// free(pointer);

	// Use-After-Free
	// free를 했음에도 불구하고 데이터를 사용하면 큰일난다.
	// - 프로그래머 입장 : OMG 망했다! <- 이거 어떻게 찾냐
	// - 해커 입장 : 심봤다! (해킹가능)
	m1->_hp = 100;
	m1->_x = 1;
	m1->_y = 2;

	return 0;
}