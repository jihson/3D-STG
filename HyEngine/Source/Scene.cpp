#include "StandardEngineFramework.h"
#include "Scene.h"
#include "Renderer.h"
#include "GameObject.h"

using namespace HyEngine;

Scene::Scene()
{

}
Scene::~Scene()
{
	for (auto& obj : m_opaqueObjects)
		SAFE_DELETE(obj);
	m_opaqueObjects.clear();
	for (auto& obj : m_alphaObjects)
		SAFE_DELETE(obj);
	m_alphaObjects.clear();
}

//void Scene::LoadScene(SerializedScene & scene, const Settings::Window & windowSettings)
//{
//	Load(scene);
//}
void Scene::LoadScene()
{
	Load();
}

void Scene::UnloadScene()
{
	Unload();
}

void Scene::UpdateScene()
{
	/*
		TODO 
		해당 로직은 특성 상 반복이 빈번한데
		이렇게 해도 괜찮은지 검토해야함.
	*/

	for (auto& obj : m_opaqueObjects)
		obj->Update();
	for (auto& obj : m_alphaObjects)
		obj->Update();
	for (auto& obj : m_invisibleObjects)
		obj->Update();
	
	Update();


	for (auto& obj : m_opaqueObjects)
	{
		obj->LateUpdate();
		if (obj->m_bWantsDestroy)
		{
			m_removeFunctions.push_back([&]()->void
			{
				m_opaqueObjects.remove(obj);
				SAFE_DELETE(obj);
			});
		}
	}
	for (auto& obj : m_alphaObjects)
	{
		obj->LateUpdate();
		if (obj->m_bWantsDestroy)
		{
			m_removeFunctions.push_back([&]()->void
			{
				m_alphaObjects.remove(obj);
				SAFE_DELETE(obj);
			});
		}
	}
	for (auto& obj : m_invisibleObjects)
	{
		obj->LateUpdate();
		if (obj->m_bWantsDestroy)
		{
			m_removeFunctions.push_back([&]()->void
			{
				m_invisibleObjects.remove(obj);
				SAFE_DELETE(obj);
			});
		}
	}

	for (auto& removeFunction : m_removeFunctions)
	{
		removeFunction();
	}
	m_removeFunctions.clear();
}


void Scene::RenderScene(Renderer * renderer)
{
	renderer->SetOpaqueContext();
	for (auto& opaqueObj : m_opaqueObjects)
	{
		if (opaqueObj->GetActive())
			renderer->Render(opaqueObj);
	}
	
	renderer->SetAlphaContext();
	for (auto& alphaObj : m_alphaObjects)
	{
		if (alphaObj->GetActive())
			renderer->Render(alphaObj);
	}

	RenderUI();
	RenderLight();
	RenderSkybox();
}

void Scene::AddOpaqueObject(GameObject * obj)
{
	m_opaqueObjects.push_back(obj);
}

void Scene::AddAlphaObject(GameObject * obj)
{
	m_alphaObjects.push_back(obj);
}

void Scene::AddInvisibleObject(GameObject * obj)
{
	m_invisibleObjects.push_back(obj);
}

