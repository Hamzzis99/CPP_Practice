#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)  // Scene만 로드하고.
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
	


void Game::Update() //엔진에서 업데이트를 해준다.
{
	GEngine->Update();
}
