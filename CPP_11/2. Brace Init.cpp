#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

class Knight
{
public:
	Knight()
	{

	}

	Knight(int a, int b)
	{
		cout << "Knight (int, int)" << endl;
	}

	//Knight(initializer_list<int> li) // 최상위 포식자 (이거 우선적으로 나옴)
	//{
	//	cout << "Knight(initializer_list)" << endl;
	//}
};

// 오늘의 주제 : 중괄호 초기화 { }

int main()
{
	int a = 0;
	int b(0);
	int c{ 0 };

	Knight k1;
	Knight k2 = k1; //복사 생성자
	//k2 = k1; // 대입 연산자 위랑 다름

	Knight k3{ k2 };

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2(10, 1);
	int arr[] = { 1, 2, 3, 4 };

	// 중괄호 초기화
	// 1) vector 등 container과 잘 어울린다.
	vector<int> v3{ 1,2,3,4, 5, 6, 7, 8, 9, 10 };

	// 2) 축소 변환 방지
	int x = 0;
	//double y{ x }; // 중괄호 초기화는 깐깐하게 하므라 축소변환을 이루지 않는다.

	// 3) Bonus
	Knight k4{}; // 중괄호를 사용할시 기본 생성자로 된다.

	Knight k5{ 1, 2 };

	// 전통적인 사용 이유
	// 괄호 초기화 ()를 기본으로 간다.
	// - 전통적인 C++ (거부감이 없음
	// - vector등 특이한 케이스에 대해서만 {} 사용

	// 사용하는 경우
	// 중괄호 초기화 {}를 기본으로 간다.
	// - 초기화 문법의 일치화
	// - 축소 변환 방지.

	return 0;
}