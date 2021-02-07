#include "stdafx.h"
#include "TestScene2.h"
#include "Fighter2.h"
#include "Renderer.h"
#include "SampleCamera.h"
#include "DebugGround.h"
#include "GameObjectQuad.h"

void TestScene2::Update()
{
}

void TestScene2::Load()
{
	#pragma region Create Example
		/*
		// 아래 예제는 active false로 시작하는 예
		auto obj = Fighter::Create(this);
		obj->SetActive(false);
		m_gameObjectsOnScene.push_back(obj);
		*/
	
	
	
		// 아래 예제는 active true로 시작하는 예
	GameObject*  player = Fighter2::Create(this);
	// 이거 반드시 해줘야함
	AddOpaqueObject(player);


	SampleCamera* sampleCamera = static_cast<SampleCamera*>(ENGINE->GetCamera());
	sampleCamera->SetTarget(player->m_pTransform);

	AddOpaqueObject(DebugGround::Create(this));

	AddOpaqueObject(GameObjectQuad::Create(this));


#pragma endregion
}

void TestScene2::Unload()
{
}

void TestScene2::RenderUI() const
{

}

void TestScene2::RenderLight() const
{
	D3DLIGHT9 dirLight;
	ZeroMemory(&dirLight, sizeof(dirLight));
	dirLight.Type = D3DLIGHT_DIRECTIONAL;
	dirLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	dirLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	dirLight.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	dirLight.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	DEVICE->SetLight(0, &dirLight);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

}

void TestScene2::RenderSkybox() const
{
}
