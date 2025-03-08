#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE, // 원근 투영
	ORTHOGRAPHIC, // 직교 투영
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	void Render();

private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::PERSPECTIVE; // 카메라 타입의 projection

	float _near = 1.f; // near
	float _far = 1000.f; // far
	float _fov = XM_PI / 4.f; // 45도의 기본 세팅
	float _scale = 1.f; // 직교투영에서 사용하게 될 것.


	//카메라에서 사용할 것들.우리가 구해줘야 했던 view, projection
	Matrix _matView = {}; 
	Matrix _matProjection = {}; 

public:
	// 세팅이 된다면 PushData가 인지하여 사용하게 되는 것.
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

