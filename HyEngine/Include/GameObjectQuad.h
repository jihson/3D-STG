#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL GameObjectQuad : public GameObject
	{
	protected:
		explicit GameObjectQuad(class Scene* scene, const std::wstring& tag);

		virtual ~GameObjectQuad() = default;

	public:
		static GameObjectQuad* Create(class Scene* scene)
		{
			GameObjectQuad* objQuad = new GameObjectQuad(scene, L"Quad");
			objQuad->Initialize();

			return objQuad;
		}

		// Inherited via GameObject
		virtual void Initialize() override;
		virtual void Render() override;

	private:
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;
		IDirect3DIndexBuffer9 * m_pIndexBuffer = nullptr;


	};

}
