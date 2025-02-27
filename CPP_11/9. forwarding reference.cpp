#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// 오늘의 주제 : 전달 참조(forwarding reference)

class Knight
{
public:
	Knight() { cout << "기본 생성자" << endl; }
	Knight(const Knight&) { cout << "복사 생성자" << endl; }
	Knight(Knight&&) noexcept{ cout << "이동 생성자" << endl; } // noexcept 이동대입 할 때 그냥 넣어라. 

};

void Test_RValueRef(Knight&& k) // 오른값 참조
{

}

void Test_Copy(Knight k)
{

}

template<typename T>
void Test_ForwardingRef(T&& param) // 오른값 참조가 아니라 전달 참조이다. 왼값 오른값 둘 다 참조 가능. param은 왼값이지만 오른값으로 바꿔치기 가능한 문법. (개어렵네 XXX)
{
	// 오른값 참조라면 이동
	Test_Copy(std::forward<T>(param)); // 전달 참조는 무조건 forward를 사용하라!!! 그니까 왼값 오른값 둘 다 사용하게 되면?
}


int main()
{
	// 보편 참조(universal reference)
	// 전달 참조(forwarding reference) C++17 
	// 둘이 같은 말이다.

	// &&	&를 두 번 쓰면 -> 오른값 참조.

	Knight k1;

	Test_RValueRef(std::move(k1)); // rvalue_cast

	//Test_ForwardingRef(k1);
	//Test_ForwardingRef(std::move(k1));

	// 공통점 : 형식 연역 (type deduction)이 일어날 때 왼값 참조 오른값 참조 둘 다 된다!
	auto&& k2 = k1;
	auto&& k3 = std::move(k1);

	//----------------------------------------------------------------------------------
	Knight& k4 = k1; // 왼값 참조
	Knight&& k5 = std::move(k1); // 오른값 참조


	// 오른값 : 왼값이 아니다 = 단일식에서 벗어나면 사용X
	// 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
	//Test_RValueRef(std::move(k5));
	Test_ForwardingRef(std::move(k1)); // 오른값 참조
	Test_ForwardingRef(k1); // 왼값 참조

	return 0;
}
