#include <iostream>
using namespace std;

// 오늘의 주제 : 클래스 템플릿

// typename T을 붙이면 '조커카드' (어떤 타입도 다 넣을 수 있음)
// 그런데 무조건 typename을 붙여야 하는 것은 아니다.
// template<> 안에 들어가는건 [골라줘야 하는 목록] 이라고 볼 수 있음.
template<typename T, int SIZE> // 정수는 정수인데 어떤 정수를 고르는지...?
class RandomBox
{
public:
	T GetRandomData()
	{
		int idx = rand() % 10;
		return _data[idx];
	}
public:
	T _data[SIZE]; // 10 -> SIZE로 변경
};

// 템플릿 특수화
template<int SIZE> // 정수는 정수인데 어떤 정수를 고르는지...?
class RandomBox<double, SIZE> // 특수한 템플릿....^^;;
{
public:
	double GetRandomData()
	{
		cout << "RandomBox Double" << endl;
		int idx = rand() % 10;
		return _data[idx];
	}
public:
	double _data[SIZE]; // 10 -> SIZE로 변경
};


void Hello(int number)
{

}

int main()
{
	Hello(10);
	Hello(20);
	
	srand(static_cast<unsigned int>(time(nullptr)));
	// 템플릿 : 함수나 클래스를 찍어내는 틀
	// 1) 함수 템플릿
	// 2) 클래스 템플릿

	RandomBox<int, 10> rb1; // 뒤에 있는 10이라는 타입이 일치해야 아래에 있는 것을 맞출 수 있음.

	for (int i = 0; i < 10; i++)
	{
		rb1._data[i] = i;
	}

	int value1 = rb1.GetRandomData();
	cout << value1 << endl;

	RandomBox<double, 20> rb2;
	for (int i = 0; i < 20; i++)
	{
		rb2._data[i] = i + 0.5f;
	}

	double value2 = rb2.GetRandomData();
	cout << value2 << endl;
	
	//rb1 = rb2; // 두 타입이 일치하지 않기 때문에 대입 못함. 


	return 0;
}