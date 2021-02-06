#include "StandardEngineFramework.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"

using namespace HyEngine;

Settings::Engine Engine::sEngineSettigns ;

IMPLEMENT_SINGLETON(Engine)

// todo keyboard, mouse, timer
Engine::Engine()
	: 
	m_bLoading(false),
	m_bIsPaused(false)
{
	DirectXDevice::Create();
	UIDGen::Create();

	m_pRenderer = new Renderer();
	m_pMouse = new IO::Mouse();
	m_pKeyboard = new IO::Keyboard();
	m_pTimer = new Timer();
	m_pCamera = new Camera();
}
Engine::~Engine()
{
	delete m_pTimer;
	delete m_pKeyboard;
	delete m_pMouse;
	delete m_pRenderer;
	delete m_pCamera;
	DirectXDevice::Destroy();
	UIDGen::Destroy();
}

bool Engine::Initialize(HWND hWnd, EngineConfig engineConfig)
{
	DirectXDevice::Get()->Init(hWnd);

	m_pTimer->start();

	this->engineConfig = engineConfig;
	m_scenes = engineConfig.scenes;

	// set default camera option
	m_pCamera->SetProjectionMatrix
	(
		D3DX_PI * 0.5f , // 90 - degree
		WinMaxWidth / WinMaxHeight,
		1.0f, 
		1000.0f
	);



	return false;
}

void Engine::Exit()
{
	m_pActiveScene->UnloadScene();
	for (auto& scene : m_scenes)
	{
		delete scene;
	}
	
}

bool Engine::Load()
{
	m_bLoading = true;

	LoadShaders();
	LoadScenes();

	m_bLoading = false;
	return false;
}

void Engine::SimulateFrame()
{
	m_pKeyboard->Update();
	m_pMouse->Update();
	m_pActiveScene->UpdateScene();
}

void Engine::RenderFrame()
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_pCamera->GetProjectionMatrix());
	DEVICE->SetTransform(D3DTS_VIEW, &m_pCamera->GetViewMatrix());
	m_pRenderer->RenderBegin();
	RenderDebug();
	m_pActiveScene->RenderScene(m_pRenderer);
	m_pRenderer->RenderEnd();
}

Camera * Engine::GetCamera() const 
{
	return m_pCamera;
}
Scene * Engine::GetActiveScene()
{
	return m_pActiveScene;
}


bool Engine::LoadShaders()
{
	// TODO 
	return true;
}

void Engine::LoadScenes()
{
	m_currentLevel = engineConfig.defaultSceneIndex;
	m_pActiveScene = engineConfig.scenes[m_currentLevel];
	m_pActiveScene->LoadScene();
}


void Engine::RenderDebug()
{

}
