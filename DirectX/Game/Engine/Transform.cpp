#include "pch.h"
#include "Transform.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM) //�ڱ� �ڽ��� ������ �θ�Կ��� �˷��ִ� ��.
{

}

Transform::~Transform()
{

}

// CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&_transform, sizeof(_transform));