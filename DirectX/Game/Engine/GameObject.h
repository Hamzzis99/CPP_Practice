#pragma once
#include "Component.h"
#include "Object.h"

//전방선언
class Transform;
class MeshRenderer;
class MonoBehaviour;
class Camera;

class GameObject : public Object, public enable_shared_from_this<GameObject> //상속하는 이유 :
{
public:
	GameObject();
	virtual ~GameObject();


	//생명주기 관리의 함수들?
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	// 컴포넌트가 계속 늘어나니 묶어놓아 공용 프로그램으로 만드는 역할.
	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type); 

	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<Camera> GetCamera();

	void AddComponent(shared_ptr<Component> component);

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; // 일반적인 컴포넌트
	vector<shared_ptr<MonoBehaviour>> _scripts; //커스텀화된 부품?
};

