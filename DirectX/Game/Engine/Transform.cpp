#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM) //자기 자신이 누군지 부모님에게 알려주는 것.
{

}

Transform::~Transform()
{

}

void Transform::FinalUpdate()
{
	//스케일
	Matrix matScale = Matrix::CreateScale(_localScale);
	//로테이션
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	//트렌슬레이션
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	//SRT 구한 것들을 Local에다 담는다.
	//물체의 좌표와 회전 상태와 스케일로부터 값을 받아 월드를 계산해준다. matworld는 임시 월드좌표?
	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	shared_ptr<Transform> parent = GetParent().lock(); // 만약 부모님이 있다
	if (parent != nullptr)
	{
		_matWorld *= parent->GetLocalToWorldMatrix(); // 부모님의 월드 매트릭스를 곱한다.
	}
}

void Transform::PushData() // 
{
	//WVP를 만들어 곱해야한다. 하지만 World는 완성됐기에 View와 Projection을 구현한 것이다.

	//월드행렬과 뷰행렬을 곱셈하여 카메라 좌표계를 만든 것.
	Matrix matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection; // Projection
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWVP, sizeof(matWVP)); 
}


