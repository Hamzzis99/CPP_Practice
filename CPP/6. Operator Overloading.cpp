#include <iostream>

// 오늘의 주제 : 연산자 오버로딩(Operator Overloading)

// 연산자 vs 함수
// - 연산자는 피연산자의 개수 / 타입이 고정되어 있음

// 연산자 오버로딩?
// [연산자 함수]를 정의해야 함.
// 함수도 멤버함수 vs 전역함수가 존재하는것처럼, 연산자 함수도 두가지 방식으로 만들 수 있음


// - 멤버 연산자 함수 version
// -- a op b 형태에서 왼쪽 기준으로 실행 됨 (a가 클래스여야 가능. a를 '기준 피연산자'라고 함)
// -- 한계) a가 클래스가 아니면 사용 못함.

//- 전역 연산자 함수 version
// - a op b 형태라면 a, b 모두를 연산자 함수의 피연산자로 만들어준다.


// (멤버 vs 전역) 그럼 무엇이 더 좋은가? 그런 거 없음. 심지어 둘 중 하나만 지원하는 경우도 있기 때문.
// - 대표적으로 대입 연산자 ( a = b)는 전역 연산자 version으로는 못 만든다. 

//operator은 결국 왼쪽에는 클래스. 오른쪽에는 멤버변수가 와야한다..?

class Position
{
public: 
	Position operator+(const Position& arg) // operator =  pos와 pos2의 결과물을 뱉어주게 하는 것..?
	{
		Position pos;
		pos._x = _x + arg._x;
		pos._y = _y + arg._y;
		return pos;
	}

	Position operator+(int arg) // operator =  pos와 pos2의 결과물을 뱉어주게 하는 것..?
	{
		Position pos;
		pos._x = _x + arg;
		pos._y = _y + arg;
		return pos;
	}


	bool operator == (const Position& arg) // == operator 
	{
		return _x == arg._x && _y == arg._y;
	}

	//void operator=(int arg)
	//{
	//	_x = arg;
	//	_y = arg;
	//}

public:
	int _x;
	int _y;
};

Position operator+(int a, const Position& b)
{
	Position ret;

	ret._x = b._x + a;
	ret._y = b._y + a;

	return ret;
}

//void operator=(const Position* a, int b) <- 전역으로 이건 안 됨.
//{
//	a._x = b;
//	a._y = b;
//}

int main()
{
	int a = 1;
	int b = 2;

	int c = a + 3.01f;

	Position pos;
	pos._x = 0;
	pos._y = 0;


	Position pos2;
	pos2._x = 1;
	pos2._y = 1;

	Position pos3 = pos + pos2; // pos.operator+(pos2); 와 같은 의미!

	Position pos4 = 1 + pos3; // Position operator+(int arg) 
	
	bool isSame = (pos3 == pos4); // 클래스끼리 비교하려면 operator를 구현하고 사용하는 것이다!!!

	Position pos5;
	pos5 = 5;
	//pos.operator+(pos2);


	return 0;
}