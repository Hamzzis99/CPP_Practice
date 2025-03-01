#pragma once

// 프레임을 계산하기 위해 만든 것 2D겜프에서 배운 거.

class Timer
{
public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; } // 현재 프레임
	float GetDeltaTime() { return _deltaTime; } // 이전 프레임에서 현재 프레임까지 계산된 것.

private:
	uint64	_frequency = 0;
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f;

private:
	uint32	_frameCount = 0;
	float	_frameTime = 0.f;
	uint32	_fps = 0;
};

