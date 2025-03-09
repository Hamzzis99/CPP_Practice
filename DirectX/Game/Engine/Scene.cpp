#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"

void Scene::Awake()
{
	//두번째 안에있는 vec를 쭉 스캔하겠다. 복사를 하는 게 아니기 때문에 콘스트를 붙인다.
	for (const shared_ptr<GameObject>& gameObject : _gameObjects) 
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->FinalUpdate();
	}
}

void Scene::Render() // Scene 자체가 모든 물체를 가지고 있기 때문에 gameobject에서 정보를 가져올 필요가 없음.
{
	//조명 관련 정보는 여기다가 담을 것.
	PushLightData();

	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render(); // 카메라를 찾게 되면 여기서 랜더한다...zz
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& gameObject : _gameObjects) //하나씩 전부 스캔을 해줘서
	{
		if (gameObject->GetLight() == nullptr)
			continue;

		// 가지고 있다면 LightInfo를 읽고
		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();
		//LightInfo를 복사해서 Count를 올리는 것. 즉 10개의 데이터라면 10개의 데이터를 채워주는 것.
		lightParams.lights[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;
	}

	//다 끝나게 되면 GLOBAL 컨스턴트 버퍼를 SetGlobalData 해주는 것.
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->SetGlobalData(&lightParams, sizeof(lightParams));
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
	{
		_gameObjects.erase(findIt);
	}
}