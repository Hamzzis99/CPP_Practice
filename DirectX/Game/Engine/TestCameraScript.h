#pragma once
#include "MonoBehaviour.h"
// 키보드를 누르면 카메라를 이동하게.

class TestCameraScript : public MonoBehaviour
{
public:
	TestCameraScript();
	virtual ~TestCameraScript();

	virtual void LateUpdate() override;

private:
	float		_speed = 100.f;
};

