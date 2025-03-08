#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE, // ���� ����
	ORTHOGRAPHIC, // ���� ����
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	void Render();

private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::PERSPECTIVE; // ī�޶� Ÿ���� projection

	float _near = 1.f; // near
	float _far = 1000.f; // far
	float _fov = XM_PI / 4.f; // 45���� �⺻ ����
	float _scale = 1.f; // ������������ ����ϰ� �� ��.


	//ī�޶󿡼� ����� �͵�.�츮�� ������� �ߴ� view, projection
	Matrix _matView = {}; 
	Matrix _matProjection = {}; 

public:
	// ������ �ȴٸ� PushData�� �����Ͽ� ����ϰ� �Ǵ� ��.
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

