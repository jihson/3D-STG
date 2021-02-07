#include "StandardEngineFramework.h"
#include "GameObjectQuad.h"
#include "Scene.h"
#include "VertexTypes.h"
#include "IndexTypes.h"

using namespace HyEngine;

HyEngine::GameObjectQuad::GameObjectQuad(Scene * scene, const std::wstring& tag)
	: GameObject(ERenderType::RenderOpaque, scene, tag)
{

}

void GameObjectQuad::Initialize()
{
	HRESULT hr;

	hr = DEVICE->CreateVertexBuffer
	(
		4 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		0
	);
	assert(SUCCEEDED(hr));

	ColorVertex* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[0].x = 0;
	vertices[0].y = 0;
	vertices[0].z = 0;
	vertices[0].color = D3DCOLOR_ARGB(255, 255, 255, 255);

	vertices[1].x = 1;
	vertices[1].y = 0;
	vertices[1].z = 0;
	vertices[1].color = D3DCOLOR_ARGB(255, 255, 255, 255);

	vertices[2].x = 1;
	vertices[2].y = 1;
	vertices[2].z = 0;
	vertices[2].color = D3DCOLOR_ARGB(255, 255, 255, 255);

	vertices[3].x = 0;
	vertices[3].y = 1;
	vertices[3].z = 0;
	vertices[3].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	

	m_pVertexBuffer->Unlock();

	hr = DEVICE->CreateIndexBuffer
	(
		2 * sizeof(Index16),
		D3DUSAGE_WRITEONLY,
		Index16::FMT,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		nullptr
	);
	assert(SUCCEEDED(hr));

	Index16 * indices;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0]._1 = 3;
	indices[0]._2 = 2;
	indices[0]._3 = 0;

	indices[1]._1 = 2;
	indices[1]._2 = 1;
	indices[1]._3 = 0;

	m_pIndexBuffer->Unlock();


}

void GameObjectQuad::Render()
{
	GameObject::Render();

	DEVICE->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ColorVertex));
	DEVICE->SetFVF(ColorVertex::FVF);
	DEVICE->SetIndices(m_pIndexBuffer);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
