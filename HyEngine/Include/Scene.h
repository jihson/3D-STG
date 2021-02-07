#pragma once
#include "IUserInterface.h"
#include "ISkybox.h"
#include "ILight.h"


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
	private :

		// Scene을 상속받은 Scene클래스에선
		// UI, Light, Skybox를 Add 해주기만 하면
		// 알아서 동작한다.
		void RenderGameObject(class Renderer* renderer) const;
		void RenderUI(class Renderer* renderer) const;
		void RenderLight(class Renderer* renderer) const ;
		void RenderSkybox(class Renderer* renderer) const ;

		void UpdateGameObject();
		void UpdateUI();
		void UpdateLight();
		void UpdateSkybox();

		void LateUpdateGameObject();

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
		void AddUserInterface(class IUserInterface* ui);
		void AddLight(class ILight* light);
		void SetSkybox(class ISkybox* skybox);
		/*
		 해당 오브젝트가 어떤 종류에 속할 지 모를 떄 
		 전체적으로 검색합니다.
		 전체를 검사하는 만큼 속도가 느려질 수 있으니
		 가능하면 GetOpaqueObject, GetAlphgaObject 등 다른 함수를
		 사용해야합니다.
		*/
		class GameObject* GetGameObject(std::wstring name);
		class GameObject* GetOpaqueObject(std::wstring name);
		class GameObject* GetAlphaObject(std::wstring name);
		class GameObject* GetInvisibleObject(std::wstring name);

		
		/*
		오브젝트를 예약합니다.
		오브젝트를 원하지만 아직 생성이 안됐거나 
		정확한 생성 시점을 모를 때 사용합니다.

		호출 시점에 이미 해당 오브젝트가 생성되었다면 
		콜백을 통해 전달하고 
		아직 생성되지않았다면 이후에 생성될 경우 
		콜백을 통해 전달합니다.

		되도록 사용을 자제해야합니다.
		*/
		void ReserveObejct(std::wstring name,  std::function<void(GameObject*)>);
	private:
		// TODO : 

		int m_selectedCamera;



		// Visible Objects
		std::list<GameObject* > m_opaqueObjects;
		std::list<GameObject* > m_alphaObjects;
		// Invisible Objects
		std::list<GameObject* > m_invisibleObjects;

		// UI Objects
		std::list<IUserInterface*> m_uiObejcts;

		// lights
		std::list<ILight* > m_lights;

		ISkybox* m_pSkybox;


		/*
			삭제 로직을 담는 함수.
			Update돌아가는 도중 삭제할 수 없기 때문에
			임시로 m_removeFunctions에 담아
			모든 Update, LateUpdate를 끝마친 후 모든 제거함수를 호출해준다.
		*/
		std::vector<std::function<void()>> m_removeFunctions;
		

		std::vector<std::pair< std::wstring, std::function<void(class GameObject*)>>> m_reserveObjFunctions;
	};

}