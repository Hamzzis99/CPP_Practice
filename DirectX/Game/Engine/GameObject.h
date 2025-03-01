#pragma once
#include "Component.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject> //상속하는 이유 :
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();

	//생명주기 관리의 함수들?
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	shared_ptr<Transform> GetTransform();

	void AddComponent(shared_ptr<Component> component);

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; // 일반적인 컴포넌트
	vector<shared_ptr<MonoBehaviour>> _scripts; //커스텀화된 부품?
};

