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
		cout << "Knight 생성" << endl;
	}

	~Knight()
	{
		cout << "~ Knight 소멸" << endl;
	}

	//void Attack() // shared_ptr전용
	//{
	//	_target->_hp -= _damage;
	//	cout << "HP : " << _target->_hp << endl;
	//}

	void Attack()
	{
		if (_target.expired() == false)
		{
			// 장점은 생명 주기에는 자유롭다.
			// 단점은 사용하기 위해선 이런식으로 명시적으로 체크해야함... 어렵다...
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
	weak_ptr<Knight> _target; // 날라갔는지 안 날라갔는지 확인 전용!
};

class RefCountBlock //참조 횟수를 세어주는 것.
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
		if (_ptr != nullptr) // 내가 진짜 관리할 애가 생겼다.
		{
			_block = new RefCountBlock(); // 1이었다가
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
			_block->_refCount--; //소멸 할 때는 --가 된다.
			cout << "RefCount : " << _block->_refCount << endl;
			//delete _ptr; // 여기서 할 필요가 없다.
		}

		if (_block->_refCount == 0)
		{
			delete _ptr;
			//delete _block; // weekptr을 사용하면 이거는 주석처리 된다!
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

	// 스마트 포인터 : 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
	// shared_ptr, weak_ptr, unique_ptr

	// shared_ptr 기능 내가 확실하게 없어졌다고 판단할 때 그 때 삭제시켜준다.
	//weak_ptr
	
	// k1[	1]
	// k2[	1]
	shared_ptr<Knight> k1 = make_shared<Knight>(); // make_shgred <- 메모리 블럭을 한번에 만들어주는 것 (new 보다 성능 빠름)

	// k1[	1]
	// k2[	1]
	shared_ptr<Knight> k2 = make_shared<Knight>(); 

	k1->_target = k2;
	k2->_target = k1;

	k1->Attack();

	//k1->_target = nullptr;
	//k2->_target = nullptr; // shared_ptr을 쓸 거면 순환 구조일시 꼭 꼭 꼭 끝날 때 nullptr을 적어줘라. (근데 이러면 스마트 포인터를 왜 쓰지?) (순환구조는 위에있는 내용)

	return 0;
}