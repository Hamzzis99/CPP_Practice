//Game.cpp
#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	// �ﰢ��
	////�ﰢ���� ������.
	//vector<Vertex> vec(3);
	//// ������ �κ�
	//vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	//vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	////�Ķ��� �κ�
	//vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	//vec[1].color = Vec4(0.f, 1.0f, 0.f, 1.f);
	////�ʷϻ� �κ�
	//vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	//vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	

	//�簢��
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


	//mesh->Init(vec); //�ﰢ���� �ΰ��� �־ mesh�� �ϳ���!
	
	//�簢�� �ε��� ���� + ���� ���� ���� (�ߺ��Ǵ� ���� ������ ��)
	vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);

	//�ε��� ���� 
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

	shader->Init(L"..\\Resources\\Shader\\default.hlsli"); // ���̴� �ҷ�����

	GEngine->GetCmdQueue()->WaitSync();

}

void Game::Update()
{
	GEngine->RenderBegin();

	//���� �ҷ�����
	shader->Update();
	{
		Transform t; //offset 1��
		t.offset = Vec4(0.0f, 0.f, 0.f, 0.f); //VS_OUT VS_Main�� ��ǥ��. �� ������ ��ǥ
		mesh->SetTransform(t);

		mesh->Render();
	}

	GEngine->RenderEnd();
}
