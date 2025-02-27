#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// delete (삭제된 함수)

class Knight
{
public:

private:
	// 정의되지 않은 비공개(private) 함수
	void operator=(const Knight& k) = delete; // 사용하지 않을 함수를 delete한다. 주석쓰면 되지 않나?

	//void operator=(const Knight& k) // 복사 대입
	//{

	//}

	//firend를 쓰는 것 자체가 설계적으로 문제가 된다..?
	// 모든 것은 뚫는 창 vs 절대 방패
	//friend class Admin; // Admin한테는 private를 열어주겠다!

private:
	int _hp = 100;
};

class Admin
{
public:
	void CopyKnight(const Knight& k)
	{
		Knight k1;
		// 복사 연산
		//k1 = k; // 다른 클래스에서 사용하기 때문에 에러가 나는건가?
	}
};

int main()
{
	Knight k1;

	Knight k2;
	
	// 복사 연산자
	//k1 = k2;

	//Admin admin;
	//admin.CopyKnight(k1);

	return 0;
}