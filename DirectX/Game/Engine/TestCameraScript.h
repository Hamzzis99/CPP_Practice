#pragma once
#include "MonoBehaviour.h"
// Ű���带 ������ ī�޶� �̵��ϰ�.

class TestCameraScript : public MonoBehaviour
{
public:
	TestCameraScript();
	virtual ~TestCameraScript();

	virtual void LateUpdate() override;

private:
	float		_speed = 100.f;
};

