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

	UpdateGameObject();
	UpdateUI();
	UpdateLight();
	UpdateSkybox();

	Update();

	LateUpdateGameObject();


	for (auto& removeFunction : m_removeFunctions)
	{
		removeFunction();
	}
	m_removeFunctions.clear();
}


void Scene::RenderScene(Renderer * renderer)
{
	RenderGameObject(renderer);
	RenderUI(renderer);
	RenderLight(renderer);
	RenderSkybox(renderer);
}

void HyEngine::Scene::RenderGameObject(Renderer* renderer) const
{
	renderer->SetOpaqueContext();
	for (auto& opaqueObj : m_opaqueObjects)
	{
		if (opaqueObj->GetActive())
			opaqueObj->Render();
	}

	renderer->SetAlphaContext();
	for (auto& alphaObj : m_alphaObjects)
	{
		if (alphaObj->GetActive())
			alphaObj->Render();
	}
}

void HyEngine::Scene::RenderUI(Renderer* renderer) const
{
	for (auto& ui : m_uiObejcts)
	{
		ui->Render();
	}
}

void HyEngine::Scene::RenderLight(Renderer* renderer) const
{
	for (auto& l : m_lights)
		l->Render();
}

void HyEngine::Scene::RenderSkybox(Renderer* renderer) const
{
	m_pSkybox->Render();
}

void HyEngine::Scene::UpdateGameObject()
{

	for (auto& obj : m_opaqueObjects)
		obj->Update();
	for (auto& obj : m_alphaObjects)
		obj->Update();
	for (auto& obj : m_invisibleObjects)
		obj->Update();
}

void HyEngine::Scene::UpdateUI()
{
	for (auto& ui : m_uiObejcts)
		ui->Update();
}

void HyEngine::Scene::UpdateLight()
{
	for (auto& l : m_lights)
		l->Update();
}

void HyEngine::Scene::UpdateSkybox()
{
	if (m_pSkybox)
		m_pSkybox->Update();
}

void HyEngine::Scene::LateUpdateGameObject()
{
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
}

void Scene::AddOpaqueObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderOpaque);
	if (m_reserveObjFunctions.size() != 0)
	{
		for (int i = 0; i < m_reserveObjFunctions.size(); i++)
		{
			if (obj->CompareName(m_reserveObjFunctions[i].first))
			{
				m_reserveObjFunctions[i].second(obj);
				m_reserveObjFunctions.erase(m_reserveObjFunctions.begin() + i);
			}
		}
	}
	
	m_opaqueObjects.push_back(obj);
}

void Scene::AddAlphaObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::RenderAlpha);
	if (m_reserveObjFunctions.size() != 0)
	{
		for (int i = 0; i < m_reserveObjFunctions.size(); i++)
		{
			if (obj->CompareName(m_reserveObjFunctions[i].first))
			{
				m_reserveObjFunctions[i].second(obj);
				m_reserveObjFunctions.erase(m_reserveObjFunctions.begin() + i);
			}
		}
	}
	m_alphaObjects.push_back(obj);
}

void Scene::AddInvisibleObject(GameObject * obj)
{
	assert(obj->GetRenderType() == ERenderType::None);
	if (m_reserveObjFunctions.size() != 0)
	{
		for (int i = 0; i < m_reserveObjFunctions.size(); i++)
		{
			if (obj->CompareName(m_reserveObjFunctions[i].first))
			{
				m_reserveObjFunctions[i].second(obj);
				m_reserveObjFunctions.erase(m_reserveObjFunctions.begin() + i);
			}
		}
	}
	m_invisibleObjects.push_back(obj);
}

void HyEngine::Scene::AddUserInterface(IUserInterface * ui)
{
	m_uiObejcts.push_back(ui);
}

void HyEngine::Scene::AddLight(ILight * light)
{
	m_lights.push_back(light);
}

void HyEngine::Scene::SetSkybox(ISkybox * skybox)
{
	m_pSkybox = skybox;
}

GameObject * HyEngine::Scene::GetGameObject(std::wstring name)
{
	for (auto& obj : m_opaqueObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	for (auto& obj : m_alphaObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	for (auto& obj : m_invisibleObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

GameObject * HyEngine::Scene::GetOpaqueObject(std::wstring name)
{
	for (auto& obj : m_opaqueObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

GameObject * HyEngine::Scene::GetAlphaObject(std::wstring name)
{
	for (auto& obj : m_alphaObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

GameObject * HyEngine::Scene::GetInvisibleObject(std::wstring name)
{
	for (auto& obj : m_invisibleObjects)
	{
		if (obj->CompareName(name))
			return obj;
	}
	return nullptr;
}

void HyEngine::Scene::ReserveObejct(std::wstring name, std::function<void(GameObject*)> reserveFunc)
{
	GameObject* obj = GetGameObject(name);
	if (obj != nullptr)
	{
		reserveFunc(obj);
		return;
	}
	m_reserveObjFunctions.emplace_back(std::make_pair(name, reserveFunc));
}

