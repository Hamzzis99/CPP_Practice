#pragma once
#include "Component.h"

class MonoBehaviour : public Component
{
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();

public:
	virtual void FinalUpdate() sealed {} // sealed 너는 활용하지 말아라? 실드? 공부 필요
};

