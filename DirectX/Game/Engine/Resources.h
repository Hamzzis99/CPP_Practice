#pragma once

#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Resources
{
	DECLARE_SINGLE(Resources); // �̱��� ���� (�̱��濡 ���ؼ� ���� �ʿ�)

public:
	// �̹� �޸𸮿� �ִ� ���� �߰��ϰų� �д� ��ɵ�.
	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> object);

	template<typename T>
	shared_ptr<T> Get(const wstring& Key);

	template<typename T>
	OBJECT_TYPE GetObjectType();

	shared_ptr<Mesh> LoadCubeMesh();
	shared_ptr<Mesh> LoadSphereMesh();

private:
	using KeyObjMap = std::map<wstring/*key*/, shared_ptr<Object>>;
	array<KeyObjMap, OBJECT_TYPE_COUNT> _resources; // ������ �̷���� �迭.
};

template<typename T>
inline shared_ptr<T> Resources::Load(const wstring& key, const wstring& path) // ���� �ε�κ�
{
	OBJECT_TYPE objectType = GetObjectType<T>(); // � ������Ʈ���� ������ ���� ������
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)]; // ���� �����͸� �ǵ���� ��������� �迭�� �������ִ� ��.

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end()) // Ű�� ã���� ���� ��.
		return static_pointer_cast<T>(findIt->second);

	// Ű�� ���ٸ� ���̴��� ������ִ� ���ҵ�.
	shared_ptr<T> object = make_shared<T>(); 
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool Resources::Add(const wstring& key, shared_ptr<T> object) // ���� ����� �� ���� ������ִ� �� (�ӽ� �Լ� �����ؼ� Load ����� ��.)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return false;

	keyObjMap[key] = object;

	return true;
}

template<typename T>
shared_ptr<T> Resources::Get(const wstring& key) // �ε尡 �Ǿ��� �� Ű�� ã���ִ� ��.
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

//� Ŭ������ ���� �� �������� �ϴ� ��?
template<typename T>
inline OBJECT_TYPE Resources::GetObjectType()
{
	if (std::is_same_v<T, GameObject>)
		return OBJECT_TYPE::GAMEOBJECT;
	else if (std::is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;
	else if (std::is_same_v<T, Mesh>)
		return OBJECT_TYPE::MESH;
	else if (std::is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;
	else if (std::is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;
	else if (std::is_convertible_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;
	else
		return OBJECT_TYPE::NONE;
}