#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// delete (������ �Լ�)

class Knight
{
public:

private:
	// ���ǵ��� ���� �����(private) �Լ�
	void operator=(const Knight& k) = delete; // ������� ���� �Լ��� delete�Ѵ�. �ּ����� ���� �ʳ�?

	//void operator=(const Knight& k) // ���� ����
	//{

	//}

	//firend�� ���� �� ��ü�� ���������� ������ �ȴ�..?
	// ��� ���� �մ� â vs ���� ����
	//friend class Admin; // Admin���״� private�� �����ְڴ�!

private:
	int _hp = 100;
};

class Admin
{
public:
	void CopyKnight(const Knight& k)
	{
		Knight k1;
		// ���� ����
		//k1 = k; // �ٸ� Ŭ�������� ����ϱ� ������ ������ ���°ǰ�?
	}
};

int main()
{
	Knight k1;

	Knight k2;
	
	// ���� ������
	//k1 = k2;

	//Admin admin;
	//admin.CopyKnight(k1);

	return 0;
}