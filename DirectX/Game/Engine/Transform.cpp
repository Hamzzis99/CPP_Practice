#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM) //�ڱ� �ڽ��� ������ �θ�Կ��� �˷��ִ� ��.
{

}

Transform::~Transform()
{

}

void Transform::FinalUpdate()
{
	//������
	Matrix matScale = Matrix::CreateScale(_localScale);
	//�����̼�
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	//Ʈ�������̼�
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	//SRT ���� �͵��� Local���� ��´�.
	//��ü�� ��ǥ�� ȸ�� ���¿� �����Ϸκ��� ���� �޾� ���带 ������ش�. matworld�� �ӽ� ������ǥ?
	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	shared_ptr<Transform> parent = GetParent().lock(); // ���� �θ���� �ִ�
	if (parent != nullptr)
	{
		_matWorld *= parent->GetLocalToWorldMatrix(); // �θ���� ���� ��Ʈ������ ���Ѵ�.
	}
}

void Transform::PushData() // 
{
	//WVP�� ����� ���ؾ��Ѵ�. ������ World�� �ϼ��Ʊ⿡ View�� Projection�� ������ ���̴�.

	//������İ� ������� �����Ͽ� ī�޶� ��ǥ�踦 ���� ��.
	Matrix matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection; // Projection
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWVP, sizeof(matWVP)); 
}


