#pragma once

#include "IRenderable.h"

namespace HyEngine
{
	/*
	Renderer는 Render관련 모든 기능을 수행한다.
	*/
	class ENGINE_DLL Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render(IRenderable * renderable);
		void RenderList(std::vector<IRenderable* > renderables);

		void RenderBegin();
		void RenderEnd();


		// default setter 
		void SetOpaqueContext();

		void SetAlphaContext();


		void BeginRenderEvent(std::wstring message);
		void EndRenderEvent(std::wstring message);

	private :
		D3DXCOLOR clearColor = 0xff555566;

	};

}