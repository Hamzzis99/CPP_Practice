#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// 오른값(rvalue) 참조와 std::move
class Pet
{

};

class Knight
{
public:
	void PrintInfo() const{} // 콘스트전용

	Knight()
	{
		cout << "Knight()" << endl;
	}

	// 복사 생성자
	Knight(const Knight& knight)
	{
		cout << "const Knight()" << endl;
	}

	// 이동 생성자
	Knight(Knight&& knight)
	{

	}

	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	// 복사 대입 연산자
	void operator=(const Knight& knight)
	{
		cout << "operator=(const Knight&)" << endl;

		// 깊은 복사
		_hp = knight._hp;
		
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	// 이동 대입 연산자 (소유권을 뺏어온다.) 잘라내기 개념
	void operator=(Knight&& knight) noexcept
	{
		cout << "operator(Knight&&)" << endl; 

		// 얕은 복사
		_hp = knight._hp;
		_pet = knight._pet;

		knight._pet = nullptr; // nullptr 넣은 이유 혹시 k2가 소멸이 되게 만들어야 하니까 강제로 nullptr을 대입한 것!
	}

public:
	int _hp = 100;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) { } // 클래스는 구현하지 않으면 기본 생성자가 만들어짐. 클론으로 어딘가의 임의의 장소에 복사된 값이 있다.
void TestKnight_LValueRef(Knight& knight) {} // 원본의 값을 수정해주는 함수 니가 멋대로 갖고 놀아도 돼
void TestKnight_ConstLValueRef(const Knight& knight) { knight.PrintInfo(); } // 콘스트 레퍼런스는 오로지 읽기 전용인거 알제? 너는 원본을 수정하면 안 된다.

void TestKnight_RValueRef(Knight&& knight) { knight._hp = 20; } //읽기 쓰기 마음대로 가능. 니가 멋대로 가능. 이동 대상이 가능하다. (이동대상이란 뭘까?)

int main()
{
	// 왼값(lvalue) vs 오른값(rvalue)
	// - lvalue : 단일식을 넘어서 계속 지속되는 개체
	// - rvalue : lavalue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

	int a = 3;

	Knight k1;

	TestKnight_Copy(k1);
	TestKnight_LValueRef(k1);
	TestKnight_ConstLValueRef(Knight());

	TestKnight_RValueRef(Knight()); // k1은 안 되지만 Knight는 가능하다? 오른값이기 때문에?

	TestKnight_RValueRef(static_cast<Knight&&>(k1)); // k1은 안 되지만 Knight는 가능하다? 오른값이기 때문에?

	// 복사를 하지 않고 이동을 하는 것!
	Knight k2; 
	k2._pet = new Pet();
	k2._hp = 1000;

	// 원본은 날려도 된다. << 는 Hint를 주는 쪽에 가깝다!
	Knight k3; 

	k3 = static_cast<Knight&&>(k2); // k3는 k2의 정보를 다 빨아먹는다. 이동한다 (잘라내기 개념!)

	k3 = std::move(k2); // 위에 있는 k3 = static_cast<Knight&&>(k2); 이거와 같다.
	// std::move의 본래 이름 후보 중 하나가 rvalue_cast

	std::unique_ptr<Knight> uptr = std::make_unique<Knight>(); // 딱 세상에 하나만 존재해야하는 포인터 (스마트 포인터) 복사가 안 되는 것.
	//std::unique_ptr<Knight> uptr2 = uptr; // 이건 안 되지만 권한 넘기는 것은 아래에 있음.
	std::unique_ptr<Knight> uptr2 = std::move(uptr);
	return 0;
}