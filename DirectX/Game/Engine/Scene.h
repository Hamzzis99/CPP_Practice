#pragma once

class GameObject;

// Scene 오브젝트만 가지고 있는 것.
class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

private:
	void PushLightData(); //Push, GPU쪽으로 일을 맡긴다.

public:
	void Render();
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	// 벡터에 const 레퍼런스를 반환하는 것.
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

private:
	vector<shared_ptr<GameObject>> _gameObjects;
};

