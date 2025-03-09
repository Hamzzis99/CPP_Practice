#pragma once
#include "Component.h"
#include "Object.h"

//���漱��
class Transform;
class MeshRenderer;
class MonoBehaviour;
class Camera;

class GameObject : public Object, public enable_shared_from_this<GameObject> //����ϴ� ���� :
{
public:
	GameObject();
	virtual ~GameObject();


	//�����ֱ� ������ �Լ���?
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	// ������Ʈ�� ��� �þ�� ������� ���� ���α׷����� ����� ����.
	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type); 

	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<Camera> GetCamera();

	void AddComponent(shared_ptr<Component> component);

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; // �Ϲ����� ������Ʈ
	vector<shared_ptr<MonoBehaviour>> _scripts; //Ŀ����ȭ�� ��ǰ?
};

