#include <iostream>

using namespace std;

class Knight
{
public:
	int GetHp(int, int)
	{
		cout << "GetHP()" << endl;
		return _hp;
	}

public:
	int _hp = 100;
};

// 오늘의 주제 : 함수 포인터

// typedef의 진실
// typedef 왼쪽 오른쪽 -> 오른쪽 (커스텀 타입 정의)

// 정확히는 왼쪽/오른쪽 기준이 아니라,
// [선언 문법]에서 typedef을 앞에다 붙이는 쪽.

typedef int INTEGER;
typedef int* POINTER;
typedef int FUNC(int, int);
typedef int (*PFUNC)(int, int);
typedef int ARRAY[20]; // 함수 포인터
typedef int (Knight::*PMEMFUNC)(int, int); // 멤버 함수 포인터


int Test(int a, int b)
{
	cout << "Test" << endl;
	return a + b;
}

int t(int a, int b)
{
	cout << "t" << endl;
	return a + b;
}

int main()
{
	 // 함수 포인터
	// 1 ) 포인터		*
	// 2) 변수의 이름	fn
	// 3) 타입			함수(인자로 int 2개를 받고, int 1개를 반환)
	
	//int (*fn)(int, int);


	PFUNC fn;

	fn = Test; // & 생략 가능 (C언어 호환성 때문)

	fn(1, 2);
	(*fn)(1, 2);

	// 위 문법으로는 [전역 함수 / 정적 함수 (static)] 만 담을 수 있다 (호출 규약이 동일한 애들)
	//fn = &Knight::GetHp;

	Test(1, 2);

	Knight k1;
	k1.GetHp(1, 1);



	PMEMFUNC mfn;
	mfn = &Knight::GetHp; // Knight 안에 있는 애들만 건드린다.
	(k1.*mfn)(1, 1);

	Knight* k2 = new Knight();
	(k2->*mfn)(1, 1);
	delete k2;

	return 0;

}