#pragma once
#include "Scene.h"

using namespace HyEngine;
class DemoScene00 : public Scene
{
	// Inherited via Scene
	virtual void Update() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void RenderUI() const override;

	// Inherited via Scene
	virtual void RenderLight() const override;
	virtual void RenderSkybox() const override;
};