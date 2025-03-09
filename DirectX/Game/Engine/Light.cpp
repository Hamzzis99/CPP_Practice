#include "pch.h"
#include "Light.h"
#include "Transform.h"

Light::Light() : Component(COMPONENT_TYPE::LIGHT)
{
}

Light::~Light()
{
}

void Light::FinalUpdate()
{
	// LightPosition�� ������ Ʈ�������� �ִ� ���������ǿ� ä���ִ� �ڵ�. (������? ���� ���ϴ� ��?)
	_lightInfo.position = GetTransform()->GetWorldPosition(); 
}