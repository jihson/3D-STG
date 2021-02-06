#include "StandardEngineFramework.h"
#include "Renderer.h"
#include "GameObject.h"

using namespace HyEngine;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Render(IRenderable * renderable)
{
	renderable->Render();
}

void Renderer::RenderList(std::vector<IRenderable*> renderables)
{
	for (auto& renderable : renderables)
	{
		renderable->Render();
	}
}


void Renderer::RenderBegin()
{
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);
	DEVICE->BeginScene();

}

void Renderer::RenderEnd()
{
	DEVICE->EndScene();
	DEVICE->Present(nullptr, nullptr, g_hWnd, nullptr);
}

void Renderer::SetOpaqueContext()
{
}

void Renderer::SetAlphaContext()
{
}

void Renderer::BeginRenderEvent(std::wstring message)
{
}

void Renderer::EndRenderEvent(std::wstring message)
{
}
