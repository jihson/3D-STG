#include "StandardEngineFramework.h"
#include "GameObject.h"
#include "Component.h"

using namespace HyEngine;

GameObject::GameObject(ERenderType renderType, Scene* scene, const std::wstring& tag)
	: Object(),
	m_renderType(renderType),
	m_bActiveSelf(true),
	m_pScene(scene),
	m_tag(tag)
{
	m_pTransform = new Transform();

}


GameObject::~GameObject()
{
	delete m_pTransform;
	for (auto& com : m_components)
	{
		SAFE_DELETE(com)
	}
	m_components.clear();
}



void GameObject::Update()
{
	for (auto& com : m_components)
	{
		if (com->GetBehaviourType() & BehaviourType::Update)
		{
			com->Update();
		}
	}
}

void GameObject::LateUpdate()
{
	for (auto& com : m_components)
	{
		if (com->GetBehaviourType() & BehaviourType::LateUpdate)
			com->LateUpdate();

		if (com->m_bWantsDestroy)
		{
			m_removeFunctions.push_back([&]() ->void
			{
				m_components.remove(com);
				SAFE_DELETE(com);
			});
		}
	}
	for (auto& removeFunction : m_removeFunctions)
	{
		removeFunction();
	}
	m_removeFunctions.clear();


}

void GameObject::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
}

bool GameObject::CompareTag(std::wstring tag)
 {
	 return m_tag == tag;
 }
