#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "TestCameraScript.h"
#include "Resources.h"

void SceneManager::Update() // 업데이트 부분은 여기다가.
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();

}

//TEMP 임시로 정한 것.
void SceneManager::Render()
{
	if (_activeScene)
		_activeScene->Render();
}


void SceneManager::LoadScene(wstring sceneName)
{
	// TODO : 기존 Scene 정리
	// TODO : 파일에서 Scene 정보 로드

	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

shared_ptr<Scene> SceneManager::LoadTestScene() // 카메라의 역할을 해줄 코드를 만들 것.
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	//컴포넌트의 기본. 한 번 다시 복습할 필요가 있음. 매우 중요하다 함.
#pragma region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>()); // Near = 1, Far = 1000, FOV = 45도
	camera->AddComponent(make_shared<TestCameraScript>()); // 카메라 스크립트 넣는 부분.
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion

#pragma region Sphere
	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>(); //게임 오브젝트 하나를 만듦
		sphere->AddComponent(make_shared<Transform>()); 
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 150.f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh(); // vertex index 정보를 resource에 접근하는 것.
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\veigar.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region Green Directional Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		//light->GetTransform()->SetLocalPosition(Vec3(0.f, 150.f, 150.f));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(0.f, -1.f, 0.f)); // 직각 아래로 빵 쏴버리는거
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);

		//rgb색상
		light->GetLight()->SetDiffuse(Vec3(0.1f, 1.f, 0.1f));
		light->GetLight()->SetAmbient(Vec3(0.f, 0.1f, 0.f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));

		scene->AddGameObject(light);
	}

#pragma endregion

#pragma region Red Point Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(150.f, 150.f, 150.f)); //z축의 150만큼. 우측 위쪽에 조명을 쏨.
		light->AddComponent(make_shared<Light>());
		//light->GetLight()->SetLightDirection(Vec3(0.f, -1.f, 0.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);

		//RGB
		light->GetLight()->SetDiffuse(Vec3(1.f, 0.1f, 0.1f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.f, 0.f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetLightRange(10000.f); //이걸 조절하면서 작동하는지 확인
		//light->GetLight()->SetLightAngle(XM_PI / 4);
		scene->AddGameObject(light);
	}
#pragma endregion

#pragma region Blue Spot Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(-150.f, 0.f, 150.f)); //물체 기준 왼쪽으로.
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 0.f)); // 우측으로 조명 쏘기
		light->GetLight()->SetLightType(LIGHT_TYPE::SPOT_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(0.f, 0.1f, 1.f));
		//light->GetLight()->SetAmbient(Vec3(0.f, 0.f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetLightRange(10000.f);
		light->GetLight()->SetLightAngle(XM_PI / 4); // 각도는 4분에 파이만큼 설정 되어있음 (45도)
		scene->AddGameObject(light);
	}
#pragma endregion

	return scene; // 방금 만들어준 scene 반환.
}