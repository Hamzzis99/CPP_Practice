//Game.cpp
#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	//삼각형을 만들자.
	vector<Vertex> vec(3);
	// 빨간색 부분
	vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	//파란색 부분
	vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.0f, 0.f, 1.f);
	//초록색 부분
	vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	mesh->Init(vec);

	shader->Init(L"..\\Resources\\Shader\\default.hlsli"); // 쉐이더 불러오기

	GEngine->GetCmdQueue()->WaitSync();

}

void Game::Update()
{
	GEngine->RenderBegin();

	shader->Update();
	{
		Transform t; //offset 1번
		t.offset = Vec4(0.75f, 0.f, 0.f, 0.f); //VS_OUT VS_Main의 좌표다. 
		mesh->SetTransform(t);

		mesh->Render();
	}

	{
		Transform t; //offset 2번
		t.offset = Vec4(0.f, 0.75f, 0.f, 0.f);
		mesh->SetTransform(t);

		mesh->Render();
	}

	
	mesh->Render();

	GEngine->RenderEnd();
}
