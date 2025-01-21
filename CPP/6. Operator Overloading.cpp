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


// 복사 대입 연산자
// - 대입 연산자가 나온 김에 [복사 대입 연산자]에 대해 알아보자.
// 용어가 좀 헷갈린다. [복사 생성자] [대입 연산자] [복사 대입 연산자] @_@
// - 복사 대입 연산자 = 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받은 것.

// 기타
// - 모든 연산자를 다 오버로딩 할 수 있는 것은 아니다. (:: . .* 이런 건 안 됨)
// - 모든 연산자가 다 2개 항이 있는 것 아님. ++ -- 가 대표적 (단항 연산자)
// - 증갑 연산자 ++ --
// -- 전위형 (++a) operator++()
// -- 후위형 (a++) operator++(int)

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

	Position& operator=(int arg) // operator은 void 반환형이 아닌 자기 자신 참조형으로 만들어야함.
	{
		_x = arg;
		_y = arg;

		//Position* this = 내자신의주소;
		return *this; // 내 자신의 주소를 가리킨 후 가져오고 싶다? this 포인터를 return 반환하면 됨
	}

	//[복사 생성자] [복사 대입 연산자] 등 특별 대우를 받는 이유는,
	// 말 그대로 객체가 '복사' 되길 원하는 특징 때문
	// TODO ) 동적할당 시간에 더 자세히 알아볼 것
	Position& operator=(const Position& arg) // operator은 void 반환형이 아닌 자기 자신 참조형으로 만들어야함.
	{
		_x = arg._x;
		_y = arg._y;

		return *this; // 내 자신의 주소를 가리킨 후 가져오고 싶다? this 포인터를 return 반환하면 됨
	}

	Position& operator++()
	{
		_x++;
		_y++;
		return *this;
	}

	Position operator++(int)
	{
		Position ret = *this;
		_x++;
		_y++;
		return ret;
	}

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
	int c = (a++);

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
	pos3 = (pos5 = 5);

	//pos.operator+(pos2);

	pos3++;

	++(++pos3);
	// (const Pos&)줘~		(Pos) 복사값 줄게~
	// 타입이 일치하지 않더라고! const를 붙이면 Pos의 복사값을 받을 수 있다! 이게 중요한거다!!!!!! (외워!!! 당장!!!! 별 백만개!)
	pos5 = pos3++; //임시 객체를 참조하지 못하는 상황이 일어나면 const를 붙여줘라?
	

	++(++pos3);
	//pos3 = posoperator+(pos2);


	return 0;
}