#include <iostream>

// 오늘의 주제 : 은닉성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성 (안전하게 하기 위한 은닉이라 보는 것이 좋다.)
// - 다형성

// 은닉성(Data Hiding) = 캡슐화(Encapsulation)
// 몰라도 되는 것은 깔끔하게 숨기겠다!
// 숨기는 이유?
// - 1) 정말 위험하고 건드리면 안 되는 경우
// - 2) 다른 경로로 접근하길 원하는 경우.


// 자동차
// - 핸들
// - 페달
// - 엔진
// - 문
// - 각종 전기선

// 일반 구매자 입장에서 사용하는 것?
// - 핸들/페달/ 문
// 몰라도 됨 (오히려 건드리면 큰일남)
// - 엔진, 각종 전기선 

// public (공개적?) protected (보호받는?) private (개인의)
// - public  누구에게나 공개 실컷 사용하세요:
// - protected : 나의 자식에게만 상속?
// - private : 나만 사용할 것 << class Car 내부에서만!

// 상속 접근 지정자 : 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
// 부모님한테 물려받은 유산을 꼭 나의 자손들에게도 똑같이 물려줘야 하진 않음
// - public: 공개적 상속? 부모님의 유산 설계 그대로~ (public -> public, protected -> protected)
// - protected : 보호받은 상속? 내 자손들한테만 물려줄거야 (public -> protected, protected -> protected)
// - private : 개인적인 상속? 나까지만 잘 쓰고 자손들한테는 아예 안 물려줄거야 (public -> private, protcted -> private)
// 보통은 public 상속을 사용하지 protected와 private는 잘 쓰이지 않음.

class Car
{
public: // (멤버) 접근 지정자
	void MoveHandle() {}
	void pushPedal() {}
	void OpenDoor() {}

	void TurnKey()
	{
		// ...
		RunEngine();
	}

protected: // 자식에게는 상속을 해줌.
	void DisassembleCar() {} // 차를 분해한다
	void RunEngine() {} // 엔진을 구동시킨다
	void ConnectCircuit() {} // 전기선 연결

public:
	// 핸들
	// 폐달
	// 엔진
	// 문
	// 각종 전기선
};

class SuperCar : private Car // 상속 접근 지정자 // 상속 접근자는 public만 대다수 쓰자!!
{
public:
	void PushRemoteController()
	{
		RunEngine();
	}
};

//class TestSuperCar : SuperCar
//{
//public:
//	void Test()
//	{
//		DisassembleCar(); // 어라 왜 상속이 안 되지? 이는 위에있는 private Car 때문이다. 
//	}
//};


// '캡슐화'
// 연관된 데이터와 함수를 논리적으로 묶어놓은 것

class Berserker
{
public:

	int GetHp() { return _hp; }

	// 사양 : 체력이 50 이하로 떨어지면 버서커 모드 발동 (강해짐)
	void SetHp(int hp)
	{
		_hp = hp;
		if (_hp <= 50)
			SetBerserkerMode();
	}

private:
	void SetBerserkerMode() // 외부에 노출되면 안 되니 private에다가 보관하는거임.
	{
		std::cout << "매우 강해짐!" << std::endl;
	}

private:
	int _hp = 100;
};

int main()
{
	Berserker b;

	b.SetHp(20);


	return 0;
}
