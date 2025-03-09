#pragma once

#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Resources
{
	DECLARE_SINGLE(Resources); // 싱글톤 지정 (싱글톤에 대해선 공부 필요)

public:
	// 이미 메모리에 있던 것을 추가하거나 읽는 기능들.
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
	array<KeyObjMap, OBJECT_TYPE_COUNT> _resources; // 맵으로 이루어진 배열.
};

template<typename T>
inline shared_ptr<T> Resources::Load(const wstring& key, const wstring& path) // 파일 로드부분
{
	OBJECT_TYPE objectType = GetObjectType<T>(); // 어떤 오브젝트인지 추출을 해준 다음에
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)]; // 원본 데이터를 건드려서 몇번쨰인지 배열을 선택해주는 것.

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end()) // 키를 찾으면 뱉어내는 것.
		return static_pointer_cast<T>(findIt->second);

	// 키가 없다면 쉐이더를 만들어주는 역할들.
	shared_ptr<T> object = make_shared<T>(); 
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool Resources::Add(const wstring& key, shared_ptr<T> object) // 직접 만들어 준 것을 등록해주는 것 (임시 함수 웬만해서 Load 사용할 것.)
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
shared_ptr<T> Resources::Get(const wstring& key) // 로드가 되었을 때 키를 찾아주는 것.
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

//어떤 클래스가 왔을 때 컴파일을 하는 것?
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