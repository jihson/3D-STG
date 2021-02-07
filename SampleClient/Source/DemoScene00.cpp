#include "stdafx.h"
#include "DemoScene00.h"
#include "DemoPlayer00.h"
#include "Renderer.h"
#include "DemoCamera00.h"
#include "DebugGround.h"
#include "GameObjectQuad.h"

void DemoScene00::Update()
{
}

void DemoScene00::Load()
{
#pragma region Create Example
	/*
	// �Ʒ� ������ active false�� �����ϴ� ��
	auto obj = Fighter::Create(this);
	obj->SetActive(false);
	m_gameObjectsOnScene.push_back(obj);
	*/



	// �Ʒ� ������ active true�� �����ϴ� ��
	GameObject*  player = DemoPlayer00::Create(this);
	// �̰� �ݵ�� �������
	AddOpaqueObject(player);


	DemoCamera00* sampleCamera = static_cast<DemoCamera00*>(ENGINE->GetCamera());
	sampleCamera->SetTarget(player->m_pTransform);

	AddOpaqueObject(DebugGround::Create(this));

	AddOpaqueObject(GameObjectQuad::Create(this));

#pragma endregion
}

void DemoScene00::Unload()
{
}

void DemoScene00::RenderUI() const
{

}

void DemoScene00::RenderLight() const
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

void DemoScene00::RenderSkybox() const
{
}
