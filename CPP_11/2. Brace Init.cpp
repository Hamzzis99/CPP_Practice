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

	//Knight(initializer_list<int> li) // �ֻ��� ������ (�̰� �켱������ ����)
	//{
	//	cout << "Knight(initializer_list)" << endl;
	//}
};

// ������ ���� : �߰�ȣ �ʱ�ȭ { }

int main()
{
	int a = 0;
	int b(0);
	int c{ 0 };

	Knight k1;
	Knight k2 = k1; //���� ������
	//k2 = k1; // ���� ������ ���� �ٸ�

	Knight k3{ k2 };

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int> v2(10, 1);
	int arr[] = { 1, 2, 3, 4 };

	// �߰�ȣ �ʱ�ȭ
	// 1) vector �� container�� �� ��︰��.
	vector<int> v3{ 1,2,3,4, 5, 6, 7, 8, 9, 10 };

	// 2) ��� ��ȯ ����
	int x = 0;
	//double y{ x }; // �߰�ȣ �ʱ�ȭ�� ����ϰ� �ϹǶ� ��Һ�ȯ�� �̷��� �ʴ´�.

	// 3) Bonus
	Knight k4{}; // �߰�ȣ�� ����ҽ� �⺻ �����ڷ� �ȴ�.

	Knight k5{ 1, 2 };

	// �������� ��� ����
	// ��ȣ �ʱ�ȭ ()�� �⺻���� ����.
	// - �������� C++ (�źΰ��� ����
	// - vector�� Ư���� ���̽��� ���ؼ��� {} ���

	// ����ϴ� ���
	// �߰�ȣ �ʱ�ȭ {}�� �⺻���� ����.
	// - �ʱ�ȭ ������ ��ġȭ
	// - ��� ��ȯ ����.

	return 0;
}