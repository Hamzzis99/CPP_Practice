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
	// LightPosition의 정보를 트랜스폼에 있는 월드포지션에 채워주는 코드. (뭐래냐? 국어 못하니 나?)
	_lightInfo.position = GetTransform()->GetWorldPosition(); 
}