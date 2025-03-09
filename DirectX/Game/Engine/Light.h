#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8 //빛의 타입.
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor // 빛마다 갖고있는 속성을 담은 것.
{
	Vec4	diffuse;
	Vec4	ambient;
	Vec4	specular;
};

struct LightInfo // 쉐이더로 넘겨줄 정보를 가지고 있는 것.
{
	LightColor	color;		// 빛의 색상.
	Vec4		position;	// 빛마다 자신의 위치 DIRECTIONAL_LIGHT은 의미 없음.
	Vec4		direction;	// 빛이 쏘는 방향. POINT_LIGHT에선 쓰이지 않음.
	int32		lightType;	// 어떤 빛 타입인지 넣어주는 것.
	float		range;		//빛의 최대 범위
	float		angle;		// 빛이 쏘는 각도
	int32		padding;	// 아무런 의미가 없는 것? 쉐이더에서 더 자세히 알아볼 것.
};

// 매번마다 물체를 하나씩 그리는 것이 아닌 프레임당 딱 한번만 빛의 정보를 세팅해주는 것.
struct LightParams 
{
	uint32		lightCount;
	Vec3		padding; // 페딩이란. 메모리에 올라가는 정렬순서 느낌. (여유메모리였나?) (윤교수님 C++ 때 배웠잖아.... 까먹었어..)
						// 즉 페딩을 사용하지 않으면 데이터 여유자리가 없어 데이터가 뒤죽박죽 된다.
	LightInfo	lights[50]; // 상위객체가 관리시키는 게 더 효율적이다. 왜냐면 색이 많기 때문에.
};

class Light : public Component
{
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;

public:
	const LightInfo& GetLightInfo() { return _lightInfo; } //정보 추출을 위한 겟 라이트

	void SetLightDirection(const Vec3& direction) { _lightInfo.direction = direction; }

	void SetDiffuse(const Vec3& diffuse) { _lightInfo.color.diffuse = diffuse; }
	void SetAmbient(const Vec3& ambient) { _lightInfo.color.ambient = ambient; }
	void SetSpecular(const Vec3& specular) { _lightInfo.color.specular = specular; }

	void SetLightType(LIGHT_TYPE type) { _lightInfo.lightType = static_cast<int32>(type); }
	void SetLightRange(float range) { _lightInfo.range = range; }
	void SetLightAngle(float angle) { _lightInfo.angle = angle; }

private:
	LightInfo _lightInfo = {};
};

