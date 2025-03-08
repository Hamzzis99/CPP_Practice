#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"

Matrix Camera::S_MatView;
Matrix Camera::S_MatProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate() // 실제적으로 행렬을 계산해주는 부분들
{
	// 월드행렬을 가져와 역행렬을 한 것. 뷰 행렬 자체가 월드행렬을 역행렬 했던 것.
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert(); 

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);
	

	//XMMatrixPerspectiveFovLH 왼손좌표계를 직접 만든 것.
	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far); // 투영 변환 행렬 화면의 view를 알아야 구할 수 있는 것.
	else
		// OrthographicLH 이면 scale을 이용하여 물체의 크기를 정하는 것.,
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);

	S_MatView = _matView; 
	S_MatProjection = _matProjection;
}

// Mesh Rende 부분
void Camera::Render()
{
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();

	// TODO : Layer 구분
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		//GetMeshRenderer 없으면 쌩깜.
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;
		// GetMeshRenderer 있으면 출력.
		gameObject->GetMeshRenderer()->Render();
	}
}