#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT, // PREFAB
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};

class Object
{
public:
	Object(OBJECT_TYPE type); // 최상위 클래스니 Object 타입을 붙임.
	virtual ~Object();

	OBJECT_TYPE GetType() { return _objectType; } // 내가 어떤 오브젝트 타입인지.

	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }

	// TODO : Instantiate // Object 클론의 복사본을 생성해주는 역할. (나중에 만들 것.)

protected: 
	// resource는 파일을 불러오는 것이다 보니 가상함수를 이용한 것. friend를 사용하기 때문에 protected를 사용함
	friend class Resources;
	virtual void Load(const wstring& path) { }
	virtual void Save(const wstring& path) { }

protected:
	OBJECT_TYPE _objectType = OBJECT_TYPE::NONE; // 어떤 오브젝트 타입인지.
	wstring _name;
};

