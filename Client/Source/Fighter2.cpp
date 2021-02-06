#include "stdafx.h"
#include "Fighter2.h"
#include "ObjLoader.h"
#include "VertexTypes.h"
#include "TestComponent2.h"
#include "Scene.h"
#include "Camera.h"
#include "Transform.h"

using namespace HyEngine;

Fighter2::Fighter2(Scene* scene)
	: GameObject(ERenderType::RenderOpaque, scene, Tags::Player)
{
	AddComponent(TestComponent2::Create(this));
}

void Fighter2::Initialize()
{
	HyEngine::IO::Loader loader;
	loader.LoadFile("../Resources/knife_LOD2.obj");
	m_pTransform = new HyEngine::Transform();

	DEVICE->CreateVertexBuffer
	(
		loader.LoadedVertices.size() * sizeof(TextureVertex),
		D3DUSAGE_DYNAMIC,
		TextureVertex::FVF,
		D3DPOOL_DEFAULT,
		&vertexBuffer,
		0
	);

	TextureVertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		vertices[i].x = loader.LoadedVertices[i].Position.X;
		vertices[i].y = loader.LoadedVertices[i].Position.Y;
		vertices[i].z = loader.LoadedVertices[i].Position.Z;

		vertices[i].nx = loader.LoadedVertices[i].Normal.X;
		vertices[i].ny = loader.LoadedVertices[i].Normal.Y;
		vertices[i].nz = loader.LoadedVertices[i].Normal.Z;

		vertices[i].u = loader.LoadedVertices[i].TextureCoordinate.X;
		vertices[i].v = loader.LoadedVertices[i].TextureCoordinate.Y;
	}

	vertexBuffer->Unlock();

	DEVICE->CreateIndexBuffer
	(
		loader.LoadedIndices.size() * sizeof(unsigned int),
		D3DUSAGE_DYNAMIC,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&indexBuffer,
		nullptr
	);

	unsigned int * indices = nullptr;
	indexBuffer->Lock(0, 0, (void**)&indices, 0);

	for (int i = 0; i < loader.LoadedIndices.size(); i++)
	{
		indices[i] = loader.LoadedIndices[i];
	}
	indexBuffer->Unlock();

	vertexNum = loader.LoadedVertices.size();
	primCount = loader.LoadedIndices.size() / 3;

	D3DMATERIAL9 material;
	material.Ambient = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255);
	material.Diffuse = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255);
	material.Specular = (D3DXCOLOR)D3DCOLOR_XRGB(255, 255, 255);
	material.Emissive = (D3DXCOLOR)D3DCOLOR_XRGB(0, 0, 0);
	material.Power = 5.0f;

	DEVICE->SetMaterial(&material);

	// setup a directional light


	D3DXCreateTextureFromFile(
		DEVICE,
		L"../Resources/Knife_hangar.png",
		&texture);
	D3DXCreateTextureFromFile(
		DEVICE,
		L"../Resources/Lightmap-0_comp_light.png",
		&lightMap);

	// Set Texture Filter States.
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	DEVICE->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}
//
//
void Fighter2::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
 
 	DEVICE->SetTexture(0, texture);
 
 	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(TextureVertex));
 
 	DEVICE->SetFVF(TextureVertex::FVF);
 
 	DEVICE->SetIndices(indexBuffer);

 	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNum, 0, primCount);

}
