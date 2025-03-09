#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8 //���� Ÿ��.
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor // ������ �����ִ� �Ӽ��� ���� ��.
{
	Vec4	diffuse;
	Vec4	ambient;
	Vec4	specular;
};

struct LightInfo // ���̴��� �Ѱ��� ������ ������ �ִ� ��.
{
	LightColor	color;		// ���� ����.
	Vec4		position;	// ������ �ڽ��� ��ġ DIRECTIONAL_LIGHT�� �ǹ� ����.
	Vec4		direction;	// ���� ��� ����. POINT_LIGHT���� ������ ����.
	int32		lightType;	// � �� Ÿ������ �־��ִ� ��.
	float		range;		//���� �ִ� ����
	float		angle;		// ���� ��� ����
	int32		padding;	// �ƹ��� �ǹ̰� ���� ��? ���̴����� �� �ڼ��� �˾ƺ� ��.
};

// �Ź����� ��ü�� �ϳ��� �׸��� ���� �ƴ� �����Ӵ� �� �ѹ��� ���� ������ �������ִ� ��.
struct LightParams 
{
	uint32		lightCount;
	Vec3		padding; // ����̶�. �޸𸮿� �ö󰡴� ���ļ��� ����. (�����޸𸮿���?) (�������� C++ �� ����ݾ�.... ��Ծ���..)
						// �� ����� ������� ������ ������ �����ڸ��� ���� �����Ͱ� ���׹��� �ȴ�.
	LightInfo	lights[50]; // ������ü�� ������Ű�� �� �� ȿ�����̴�. �ֳĸ� ���� ���� ������.
};

class Light : public Component
{
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;

public:
	const LightInfo& GetLightInfo() { return _lightInfo; } //���� ������ ���� �� ����Ʈ

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

