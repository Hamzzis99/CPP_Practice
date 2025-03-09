#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8 //컴포넌트는 게임 오브젝트들을 넣는다?
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	LIGHT,
	// ...
	MONO_BEHAVIOUR, // 꼭 마지막에 등장해야한다 이유는?
	END,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1 // Monobehaivor을 뺀?
};

class GameObject;
class Transform;

class Component :public Object
{
public:
	Component(COMPONENT_TYPE type); // 컴포넌트 타입
	virtual ~Component(); // 컴포넌트는 부모클래스니 버추얼을 쓴다.

public:
	// 일단 순서대로.
	virtual void Awake() {} // 시작 하기전에 초기화를 하는 점?
	virtual void Start() {}
	virtual void Update() {} // 모든 물체가 전부 업데이트를 한 뒤에
	virtual void LateUpdate() {} // 시점분리?? 
	virtual void FinalUpdate() {} // 엔진에서만 활용하는 마지막 단계.

public:
	COMPONENT_TYPE GetType() { return _type; } // 내가 어떤 타입인지
	bool IsValid() { return _gameObject.expired() == false; } // 주인님이 소멸이 됐는지?

	//헬퍼 함수
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject; // 게임 오브젝트에게만 컴포넌트의 접근권한을 열어준 것.
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; } // 게임 오브젝트만 실행되게

protected:
	COMPONENT_TYPE _type;
	weak_ptr<GameObject> _gameObject; // weak_ptr인 이유 순환구조이기 때문에.
};

