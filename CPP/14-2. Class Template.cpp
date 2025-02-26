#include <iostream>
using namespace std;

// ������ ���� : Ŭ���� ���ø�

// typename T�� ���̸� '��Ŀī��' (� Ÿ�Ե� �� ���� �� ����)
// �׷��� ������ typename�� �ٿ��� �ϴ� ���� �ƴϴ�.
// template<> �ȿ� ���°� [������ �ϴ� ���] �̶�� �� �� ����.
template<typename T, int SIZE> // ������ �����ε� � ������ ������...?
class RandomBox
{
public:
	T GetRandomData()
	{
		int idx = rand() % 10;
		return _data[idx];
	}
public:
	T _data[SIZE]; // 10 -> SIZE�� ����
};

// ���ø� Ư��ȭ
template<int SIZE> // ������ �����ε� � ������ ������...?
class RandomBox<double, SIZE> // Ư���� ���ø�....^^;;
{
public:
	double GetRandomData()
	{
		cout << "RandomBox Double" << endl;
		int idx = rand() % 10;
		return _data[idx];
	}
public:
	double _data[SIZE]; // 10 -> SIZE�� ����
};


void Hello(int number)
{

}

int main()
{
	Hello(10);
	Hello(20);
	
	srand(static_cast<unsigned int>(time(nullptr)));
	// ���ø� : �Լ��� Ŭ������ ���� Ʋ
	// 1) �Լ� ���ø�
	// 2) Ŭ���� ���ø�

	RandomBox<int, 10> rb1; // �ڿ� �ִ� 10�̶�� Ÿ���� ��ġ�ؾ� �Ʒ��� �ִ� ���� ���� �� ����.

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
	
	//rb1 = rb2; // �� Ÿ���� ��ġ���� �ʱ� ������ ���� ����. 


	return 0;
}