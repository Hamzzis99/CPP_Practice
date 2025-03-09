#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8 //������Ʈ�� ���� ������Ʈ���� �ִ´�?
{
	TRANSFORM,
	MESH_RENDERER,
	CAMERA,
	LIGHT,
	// ...
	MONO_BEHAVIOUR, // �� �������� �����ؾ��Ѵ� ������?
	END,
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1 // Monobehaivor�� ��?
};

class GameObject;
class Transform;

class Component :public Object
{
public:
	Component(COMPONENT_TYPE type); // ������Ʈ Ÿ��
	virtual ~Component(); // ������Ʈ�� �θ�Ŭ������ ���߾��� ����.

public:
	// �ϴ� �������.
	virtual void Awake() {} // ���� �ϱ����� �ʱ�ȭ�� �ϴ� ��?
	virtual void Start() {}
	virtual void Update() {} // ��� ��ü�� ���� ������Ʈ�� �� �ڿ�
	virtual void LateUpdate() {} // �����и�?? 
	virtual void FinalUpdate() {} // ���������� Ȱ���ϴ� ������ �ܰ�.

public:
	COMPONENT_TYPE GetType() { return _type; } // ���� � Ÿ������
	bool IsValid() { return _gameObject.expired() == false; } // ���δ��� �Ҹ��� �ƴ���?

	//���� �Լ�
	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();

private:
	friend class GameObject; // ���� ������Ʈ���Ը� ������Ʈ�� ���ٱ����� ������ ��.
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; } // ���� ������Ʈ�� ����ǰ�

protected:
	COMPONENT_TYPE _type;
	weak_ptr<GameObject> _gameObject; // weak_ptr�� ���� ��ȯ�����̱� ������.
};

