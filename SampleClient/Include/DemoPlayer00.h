#pragma once
#include "GameObject.h"
#include "DemoComponent00.h"

using namespace HyEngine;

class DemoPlayer00 final : public GameObject
{
private:
	explicit DemoPlayer00(class Scene* scene);

	virtual ~DemoPlayer00() = default;


public:
	static DemoPlayer00* Create(Scene* scene)
	{
		DemoPlayer00* fighter = new DemoPlayer00(scene);
		fighter->Initialize();

		//ObjectManager::Get()->InsertObject(fighter);
		return fighter;
	}

	virtual void Initialize() override;

	// Inherited via GameObject
	virtual void Render() override;

private:
	IDirect3DVertexBuffer9 * vertexBuffer = nullptr;

	IDirect3DIndexBuffer9* indexBuffer = nullptr;
	//class objl::Loader loader;
	UINT vertexNum;
	UINT primCount;

	IDirect3DTexture9 * texture = nullptr;
	IDirect3DTexture9* lightMap = nullptr;

};
