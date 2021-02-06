#pragma once



namespace HyEngine
{

	class GameObject;

	class ENGINE_DLL Scene
	{
	protected:
		virtual void Update() = 0;

		// LOAD / UNLOAD
		virtual void Load() = 0;
		virtual void Unload() = 0;

		/*
			Scene에서 UI, Light, Skybox를 그린다.
			Engine에서 Debug를 그린다.
			GameObject에서 각종 오브젝트를 그린다.
		*/
		virtual void RenderUI() const = 0;
		virtual void RenderLight() const = 0;
		virtual void RenderSkybox() const = 0;

	public:
		explicit Scene();
		virtual ~Scene();

		/*
			CORE INTERFACE
		*/
		void LoadScene();
		void UnloadScene();
		void UpdateScene();
		void RenderScene(class Renderer * renderer);

		/*
			Object Setter
		*/
		void AddOpaqueObject(class GameObject* obj);
		void AddAlphaObject(class GameObject* obj);
		void AddInvisibleObject(class GameObject* obj);

	private:
		// TODO : 

		int m_selectedCamera;



		// Visible Objects
		std::list<GameObject* > m_opaqueObjects;
		std::list<GameObject* > m_alphaObjects;
		// Invisible Objects
		std::list<GameObject* > m_invisibleObjects;

		/*
			삭제 로직을 담는 함수.
			Update돌아가는 도중 삭제할 수 없기 때문에
			임시로 m_removeFunctions에 담아
			모든 Update, LateUpdate를 끝마친 후 모든 제거함수를 호출해준다.
		*/
		std::vector<std::function<void()>> m_removeFunctions;
	};

}