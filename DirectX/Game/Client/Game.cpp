//Game.cpp
#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	// 삼각형
	////삼각형을 만들자.
	//vector<Vertex> vec(3);
	//// 빨간색 부분
	//vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	//vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	////파란색 부분
	//vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	//vec[1].color = Vec4(0.f, 1.0f, 0.f, 1.f);
	////초록색 부분
	//vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	//vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	

	//사각형
	//vector<Vertex> vec(6);
	//vec[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	//vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	//vec[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	//vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	//vec[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	//vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);

	//vec[3].pos = Vec3(0.5f, -0.5f, 0.5f);
	//vec[3].color = Vec4(0.f, 0.f, 1.f, 1.f);
	//vec[4].pos = Vec3(-0.5f, -0.5f, 0.5f);
	//vec[4].color = Vec4(0.f, 1.f, 0.f, 1.f);
	//vec[5].pos = Vec3(-0.5f, 0.5f, 0.5f);
	//vec[5].color = Vec4(1.f, 0.f, 0.f, 1.f);


	//mesh->Init(vec); //삼각형이 두개가 있어도 mesh는 하나다!
	
	//사각형 인덱스 버퍼 + 정점 버퍼 버전 (중복되는 점을 제거한 것)
	vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);

	//인덱스 버퍼 
	vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);
		indexVec.push_back(2);
	}
	{
		indexVec.push_back(0);
		indexVec.push_back(2);
		indexVec.push_back(3);
	}

	mesh->Init(vec, indexVec);

	shader->Init(L"..\\Resources\\Shader\\default.hlsli"); // 쉐이더 불러오기

	GEngine->GetCmdQueue()->WaitSync();

}

void Game::Update()
{
	GEngine->RenderBegin();

	//도형 불러오기
	shader->Update();
	{
		Transform t; //offset 1번
		t.offset = Vec4(0.0f, 0.f, 0.f, 0.f); //VS_OUT VS_Main의 좌표다. 즉 도형의 좌표
		mesh->SetTransform(t);

		mesh->Render();
	}

	GEngine->RenderEnd();
}
