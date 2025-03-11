#pragma once
#include "object.h"

// materials <- 쉐이더들을 어떤식으로 그려줄지 정해준 것 (프리셋이라고 보면 되나?)

class Shader;
class Texture;

enum
{
	MATERIAL_INT_COUNT = 5,
	MATERIAL_FLOAT_COUNT = 5,
	MATERIAL_TEXTURE_COUNT = 5,
};

struct MaterialParams
{
	void SetInt(uint8 index, int32 value) { intParams[index] = value; }
	void SetFloat(uint8 index, float value) { floatParams[index] = value; }
	void SetTexon(uint8 index, int32 value) { texOnParams[index] = value; }
	// array 고정된 배열이라고 보면 됨. 버그를 잡기 좋음.
	// vector은 늘릴 수 있지만 array는 고정.
	// 쉐이더 추가 코드?
	array<int32, MATERIAL_INT_COUNT> intParams;
	array<float, MATERIAL_FLOAT_COUNT> floatParams; 
	array<float, MATERIAL_TEXTURE_COUNT> texOnParams;
};

class Material : public Object
{
public:
	Material();
	virtual ~Material();

	shared_ptr<Shader> GetShader() { return _shader; }

	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
	void SetInt(uint8 index, int32 value) { _params.SetInt(index, value); }
	void SetFloat(uint8 index, float value) { _params.SetFloat(index, value); }
	void SetTexture(uint8 index, shared_ptr<Texture> texture) 
	{ 
		_textures[index] = texture; 
		_params.SetTexon(index, (texture == nullptr ? 0 : 1)); // texture가 null 이면 0 false면 오른쪽 인 1의 값
	}

	void PushData();

private:
	shared_ptr<Shader>	_shader;
	MaterialParams		_params;
	array<shared_ptr<Texture>, MATERIAL_TEXTURE_COUNT> _textures;
};


