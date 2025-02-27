#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// ������(rvalue) ������ std::move
class Pet
{

};

class Knight
{
public:
	void PrintInfo() const{} // �ܽ�Ʈ����

	Knight()
	{
		cout << "Knight()" << endl;
	}

	// ���� ������
	Knight(const Knight& knight)
	{
		cout << "const Knight()" << endl;
	}

	// �̵� ������
	Knight(Knight&& knight)
	{

	}

	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	// ���� ���� ������
	void operator=(const Knight& knight)
	{
		cout << "operator=(const Knight&)" << endl;

		// ���� ����
		_hp = knight._hp;
		
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	// �̵� ���� ������ (�������� ����´�.) �߶󳻱� ����
	void operator=(Knight&& knight) noexcept
	{
		cout << "operator(Knight&&)" << endl; 

		// ���� ����
		_hp = knight._hp;
		_pet = knight._pet;

		knight._pet = nullptr; // nullptr ���� ���� Ȥ�� k2�� �Ҹ��� �ǰ� ������ �ϴϱ� ������ nullptr�� ������ ��!
	}

public:
	int _hp = 100;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) { } // Ŭ������ �������� ������ �⺻ �����ڰ� �������. Ŭ������ ����� ������ ��ҿ� ����� ���� �ִ�.
void TestKnight_LValueRef(Knight& knight) {} // ������ ���� �������ִ� �Լ� �ϰ� �ڴ�� ���� ��Ƶ� ��
void TestKnight_ConstLValueRef(const Knight& knight) { knight.PrintInfo(); } // �ܽ�Ʈ ���۷����� ������ �б� �����ΰ� ����? �ʴ� ������ �����ϸ� �� �ȴ�.

void TestKnight_RValueRef(Knight&& knight) { knight._hp = 20; } //�б� ���� ������� ����. �ϰ� �ڴ�� ����. �̵� ����� �����ϴ�. (�̵�����̶� ����?)

int main()
{
	// �ް�(lvalue) vs ������(rvalue)
	// - lvalue : ���Ͻ��� �Ѿ ��� ���ӵǴ� ��ü
	// - rvalue : lavalue�� �ƴ� ������ (�ӽ� ��, ������, ����, i++ ��)

	int a = 3;

	Knight k1;

	TestKnight_Copy(k1);
	TestKnight_LValueRef(k1);
	TestKnight_ConstLValueRef(Knight());

	TestKnight_RValueRef(Knight()); // k1�� �� ������ Knight�� �����ϴ�? �������̱� ������?

	TestKnight_RValueRef(static_cast<Knight&&>(k1)); // k1�� �� ������ Knight�� �����ϴ�? �������̱� ������?

	// ���縦 ���� �ʰ� �̵��� �ϴ� ��!
	Knight k2; 
	k2._pet = new Pet();
	k2._hp = 1000;

	// ������ ������ �ȴ�. << �� Hint�� �ִ� �ʿ� ������!
	Knight k3; 

	k3 = static_cast<Knight&&>(k2); // k3�� k2�� ������ �� ���ƸԴ´�. �̵��Ѵ� (�߶󳻱� ����!)

	k3 = std::move(k2); // ���� �ִ� k3 = static_cast<Knight&&>(k2); �̰ſ� ����.
	// std::move�� ���� �̸� �ĺ� �� �ϳ��� rvalue_cast

	std::unique_ptr<Knight> uptr = std::make_unique<Knight>(); // �� ���� �ϳ��� �����ؾ��ϴ� ������ (����Ʈ ������) ���簡 �� �Ǵ� ��.
	//std::unique_ptr<Knight> uptr2 = uptr; // �̰� �� ������ ���� �ѱ�� ���� �Ʒ��� ����.
	std::unique_ptr<Knight> uptr2 = std::move(uptr);
	return 0;
}