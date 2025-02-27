#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// 오늘의 주제 : nullptr

class Knight
{
public:
	void Test()
	{

	}
};

Knight* FindKnight()
{
	//TODO

	return nullptr;
}

void Test(int a)
{
	cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
	cout << "Test(*)" << endl;
}

// NullPtr 구현
const
class NullPtr
{
public:
	// 그 어떤 타입의 포인터와도 치환 가능.
	template<typename T>
	operator T* () const
	{
		return 0;
	}
	
	// 그 어떤 타입의 멤버 포인터와도 치환 가능.
	template<typename C, typename T>
	operator T C::* () const
	{
		return 0;
	}

private:
	void operator&() const; // 주소값 &을 막는다.
};

const NullPtr _Nullptr;

int main()
{
	int* ptr = nullptr; // 0, NULL 초기화와 똑같음

	// 1) 오동작 방지를 위해 nullptr을 사용한다.
	Test(0);
	Test(NULL);
	Test(_Nullptr);

	// 2) 가독성.
	Knight* knight = FindKnight();
	if (knight == _Nullptr) // nullptr을 사용함으로서 포인터인 것을 보여준다.
	{

	}

	void(Knight:: * memFunc)();
	memFunc = &Knight::Test;

	if (memFunc == _Nullptr)
	{

	}

	nullptr_t whoami = nullptr;

	return 0;
}