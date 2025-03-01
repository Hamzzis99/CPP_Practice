#pragma once
#include "Component.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject> //����ϴ� ���� :
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();

	//�����ֱ� ������ �Լ���?
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	shared_ptr<Transform> GetTransform();

	void AddComponent(shared_ptr<Component> component);

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; // �Ϲ����� ������Ʈ
	vector<shared_ptr<MonoBehaviour>> _scripts; //Ŀ����ȭ�� ��ǰ?
};

