#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"

void Scene::Awake()
{
	//�ι�° �ȿ��ִ� vec�� �� ��ĵ�ϰڴ�. ���縦 �ϴ� �� �ƴϱ� ������ �ܽ�Ʈ�� ���δ�.
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

void Scene::Render() // Scene ��ü�� ��� ��ü�� ������ �ֱ� ������ gameobject���� ������ ������ �ʿ䰡 ����.
{
	//���� ���� ������ ����ٰ� ���� ��.
	PushLightData();

	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render(); // ī�޶� ã�� �Ǹ� ���⼭ �����Ѵ�...zz
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& gameObject : _gameObjects) //�ϳ��� ���� ��ĵ�� ���༭
	{
		if (gameObject->GetLight() == nullptr)
			continue;

		// ������ �ִٸ� LightInfo�� �а�
		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();
		//LightInfo�� �����ؼ� Count�� �ø��� ��. �� 10���� �����Ͷ�� 10���� �����͸� ä���ִ� ��.
		lightParams.lights[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;
	}

	//�� ������ �Ǹ� GLOBAL ������Ʈ ���۸� SetGlobalData ���ִ� ��.
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