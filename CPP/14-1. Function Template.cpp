#include <iostream>
using namespace std;

// 오늘의 주제 : 템플릿 기초

class Knight
{
public:
	// ...

public:
	int _hp = 100;
};

template<typename T> // typename 대신 class라고 지어도 됨.
void Print(T a) // 자료형을 쓰는 게 아니라 T라는 것을 쓴다?
{
	cout << a << endl;
}

// 템플릿 특수화
template<>
void Print(Knight a)
{
	cout << "Knight !!!!!!!!!!!!!!!" << endl;
	cout << a._hp << endl;
}

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << " " << b << endl;
}

template<typename T>
T Add(T a, T b) // 아직 타입이 뭔지 모르니 조커카드로?
{
	return a + b;
}

// 연산자 오버로딩 (전역함수 버전)
ostream& operator <<(ostream& os, const Knight& k)
{
	os << k._hp;
	return os;
}


int main()
{
	// 템플릿 : 함수나 클래스를 찍어내는 틀
	// 1) 함수 템플릿
	// 2) 클래스 템플릿


	Print<int>(50); // 명시적으로 하는 법은 꺽새 <int>를 달면 된다.
	Print(50.0f);
	Print(50.0);
	Print("Hello World");

	Print("Hello ", 100);

	int result1 = Add(1, 2);
	float result2 = Add<float>(1.11f, 2.22f);

	Knight k1;
	Print(k1); 

	return 0;
}