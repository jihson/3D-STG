#pragma once
#include "Object.h"
#include "IRenderable.h"

namespace HyEngine
{
	class Component;
	class ENGINE_DLL GameObject : public Object, public IRenderable
	{
	protected:
		GameObject(ERenderType renderType, class Scene* scene, const std::wstring& tag);

	public:
		virtual ~GameObject();

	protected:
		virtual void Initialize() = 0;


	public:
		virtual void Render() = 0;
		void Update();
		void LateUpdate();

		bool CompareTag(std::wstring tag);

		inline ERenderType GetRenderType()const { return m_renderType; }

		inline Component* AddComponent(Component* component)
		{
			m_components.emplace_back(component);
			return component;
		}

		template <typename Type>
		Component* GetComponent()
		{
			for (auto& component : m_components)
			{
				Type* comp = dynamic_cast<Type*>(component);
				if (comp != nullptr)
					return comp;
			}
			return nullptr;
		}

		template <typename Type>
		std::vector<class Component* > GetComponents()
		{
			std::vector<component*> comVec;
			for (auto& component : m_components)
			{
				Type* comp = dynamic_cast<Type*> (component);
				if (comp != nullptr)
					comVec.push_back(comp);
			}
			return comVec;
		}

		inline void SetActive(bool active) { m_bActiveSelf = active; }
		inline bool GetActive() const { return m_bActiveSelf; }

		// Gets the component of the specified type, if it exists.
		template <typename T>
		bool TryGetComponent(_Out_ Component** result)
		{
			for (auto& component : m_components)
			{
				T * comp = dynamic_cast<T*>(component);
				if (comp != nullptr)
				{
					result = comp;
					return true;
				}
			}
			return false;


		}


		inline void SetScene(class Scene* scene)
		{
			if (m_pScene == nullptr)
				m_pScene = scene;
			else
				assert(false);
		}

		// ----------------------------------------------------------
		// STATIC METHODS
		// ---------------------------------------------------------------


	public:
		class Transform* m_pTransform;
	private:
		// --------------------------------------
		// PROPERTIES
		// --------------------------------------
		bool m_bActiveSelf;
		//TODO : Layer m_layer;
		// TODO : Scene m_scene;
		const std::wstring m_tag;

		UINT m_layer;
		//Scene that the GameObject is part of.
		class Scene* m_pScene = nullptr;

		ERenderType m_renderType;

		std::list<class Component* > m_components;

		std::vector<std::function<void()>> m_removeFunctions;
	};
}