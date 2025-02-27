#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// ������ ���� : nullptr

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

// NullPtr ����
const
class NullPtr
{
public:
	// �� � Ÿ���� �����Ϳ͵� ġȯ ����.
	template<typename T>
	operator T* () const
	{
		return 0;
	}
	
	// �� � Ÿ���� ��� �����Ϳ͵� ġȯ ����.
	template<typename C, typename T>
	operator T C::* () const
	{
		return 0;
	}

private:
	void operator&() const; // �ּҰ� &�� ���´�.
};

const NullPtr _Nullptr;

int main()
{
	int* ptr = nullptr; // 0, NULL �ʱ�ȭ�� �Ȱ���

	// 1) ������ ������ ���� nullptr�� ����Ѵ�.
	Test(0);
	Test(NULL);
	Test(_Nullptr);

	// 2) ������.
	Knight* knight = FindKnight();
	if (knight == _Nullptr) // nullptr�� ��������μ� �������� ���� �����ش�.
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