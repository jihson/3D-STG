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
			Scene���� UI, Light, Skybox�� �׸���.
			Engine���� Debug�� �׸���.
			GameObject���� ���� ������Ʈ�� �׸���.
		*/
	private :

		// Scene�� ��ӹ��� SceneŬ��������
		// UI, Light, Skybox�� Add ���ֱ⸸ �ϸ�
		// �˾Ƽ� �����Ѵ�.
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
		 �ش� ������Ʈ�� � ������ ���� �� �� �� 
		 ��ü������ �˻��մϴ�.
		 ��ü�� �˻��ϴ� ��ŭ �ӵ��� ������ �� ������
		 �����ϸ� GetOpaqueObject, GetAlphgaObject �� �ٸ� �Լ���
		 ����ؾ��մϴ�.
		*/
		class GameObject* GetGameObject(std::wstring name);
		class GameObject* GetOpaqueObject(std::wstring name);
		class GameObject* GetAlphaObject(std::wstring name);
		class GameObject* GetInvisibleObject(std::wstring name);

		
		/*
		������Ʈ�� �����մϴ�.
		������Ʈ�� �������� ���� ������ �ȵưų� 
		��Ȯ�� ���� ������ �� �� ����մϴ�.

		ȣ�� ������ �̹� �ش� ������Ʈ�� �����Ǿ��ٸ� 
		�ݹ��� ���� �����ϰ� 
		���� ���������ʾҴٸ� ���Ŀ� ������ ��� 
		�ݹ��� ���� �����մϴ�.

		�ǵ��� ����� �����ؾ��մϴ�.
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
			���� ������ ��� �Լ�.
			Update���ư��� ���� ������ �� ���� ������
			�ӽ÷� m_removeFunctions�� ���
			��� Update, LateUpdate�� ����ģ �� ��� �����Լ��� ȣ�����ش�.
		*/
		std::vector<std::function<void()>> m_removeFunctions;
		

		std::vector<std::pair< std::wstring, std::function<void(class GameObject*)>>> m_reserveObjFunctions;
	};

}