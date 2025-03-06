#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)  // Scene�� �ε��ϰ�.
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
	


void Game::Update() //�������� ������Ʈ�� ���ش�.
{
	GEngine->Update();
}
