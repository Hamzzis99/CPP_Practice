#pragma once

class GameObject;

// Scene ������Ʈ�� ������ �ִ� ��.
class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

private:
	void PushLightData(); //Push, GPU������ ���� �ñ��.

public:
	void Render();
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	// ���Ϳ� const ���۷����� ��ȯ�ϴ� ��.
	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

private:
	vector<shared_ptr<GameObject>> _gameObjects;
};

