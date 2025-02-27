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
		cout << "Knight ����" << endl;
	}

	~Knight()
	{
		cout << "~ Knight �Ҹ�" << endl;
	}

	//void Attack() // shared_ptr����
	//{
	//	_target->_hp -= _damage;
	//	cout << "HP : " << _target->_hp << endl;
	//}

	void Attack()
	{
		if (_target.expired() == false)
		{
			// ������ ���� �ֱ⿡�� �����Ӵ�.
			// ������ ����ϱ� ���ؼ� �̷������� ��������� üũ�ؾ���... ��ƴ�...
			shared_ptr<Knight> sptr = _target.lock();
			sptr->_hp -= _damage;
			cout << "HP : " << sptr->_hp << endl;
		}
}

public:
	int _hp = 100;
	int _damage = 10;
	//Knight* _target = nullptr;
	//shared_ptr<Knight>_target = nullptr;
	weak_ptr<Knight> _target; // ���󰬴��� �� ���󰬴��� Ȯ�� ����!
};

class RefCountBlock //���� Ƚ���� �����ִ� ��.
{
public:
	int _refCount = 1;
	int _weakCount = 1;
};



template<typename T>
class SharedPtr
{
public:
	SharedPtr() {}
	SharedPtr(T* ptr) : _ptr(ptr)
	{
		if (_ptr != nullptr) // ���� ��¥ ������ �ְ� �����.
		{
			_block = new RefCountBlock(); // 1�̾��ٰ�
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr), _block(sptr._block)
	{
		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	void operator=(const SharedPtr& sptr)
	{
		_ptr = sptr._ptr;
		_block = sptr._block;
		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	~SharedPtr()
	{
		if (_ptr != nullptr)
		{
			_block->_refCount--; //�Ҹ� �� ���� --�� �ȴ�.
			cout << "RefCount : " << _block->_refCount << endl;
			//delete _ptr; // ���⼭ �� �ʿ䰡 ����.
		}

		if (_block->_refCount == 0)
		{
			delete _ptr;
			//delete _block; // weekptr�� ����ϸ� �̰Ŵ� �ּ�ó�� �ȴ�!
			cout << "Delete Data" << endl;

		}
	}

public:
	T* _ptr = nullptr; //
	RefCountBlock* _block = nullptr;
};



int main()
{
	//Knight* k1 = new Knight();
	//Knight* k2 = new Knight();

	//k1->_target = k2;

	//delete k2;

	//k1->Attack();

	// ����Ʈ ������ : �����͸� �˸´� ��å�� ���� �����ϴ� ��ü (�����͸� �����ؼ� ���)
	// shared_ptr, weak_ptr, unique_ptr

	// shared_ptr ��� ���� Ȯ���ϰ� �������ٰ� �Ǵ��� �� �� �� ���������ش�.
	//weak_ptr
	
	// k1[	1]
	// k2[	1]
	shared_ptr<Knight> k1 = make_shared<Knight>(); // make_shgred <- �޸� ���� �ѹ��� ������ִ� �� (new ���� ���� ����)

	// k1[	1]
	// k2[	1]
	shared_ptr<Knight> k2 = make_shared<Knight>(); 

	k1->_target = k2;
	k2->_target = k1;

	k1->Attack();

	//k1->_target = nullptr;
	//k2->_target = nullptr; // shared_ptr�� �� �Ÿ� ��ȯ �����Ͻ� �� �� �� ���� �� nullptr�� �������. (�ٵ� �̷��� ����Ʈ �����͸� �� ����?) (��ȯ������ �����ִ� ����)

	return 0;
}