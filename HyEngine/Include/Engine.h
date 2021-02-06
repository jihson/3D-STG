#pragma once


struct EngineDesc
{
	std::vector<Scene*> scenes;
};

namespace HyEngine
{
	class ENGINE_DLL Engine
	{
		friend class Application;

		DECLARE_SINGLETON(Engine)
	private:
		Engine();
		~Engine();

	public:
		bool Initialize(HWND hWnd, EngineConfig engineConfig);
		void Exit();

		// Load the required resources
		bool Load();

		// The basic Logic works in this function.
		void SimulateFrame();
		// The basic Render works in this function.
		void RenderFrame();

		// Engine Pause
		inline void Pause() { m_bIsPaused = true; }
		inline void Unpause() { m_bIsPaused = false; }

		// Input
		inline IO::Mouse* GetMouse() const { return m_pMouse; }
		inline IO::Keyboard* GetKeyboard() const { return m_pKeyboard; }
		inline Timer* GetTimer() const { return m_pTimer; }
		class Camera* GetCamera() const;
	public:
		class Scene* GetActiveScene();
	private:


		// °ø¿ë ½¦ÀÌ´õ > ?
		bool LoadShaders();

		void LoadScenes();


		//void RenderUI();
		void RenderDebug();


		bool inline IsLoading() const { return m_bLoading; }


		// TOGGLES
		void inline TogglePause() { m_bIsPaused = !m_bIsPaused; }
	private:
		// static 
		static Settings::Engine sEngineSettigns;

		IO::Keyboard *m_pKeyboard;
		IO::Mouse *m_pMouse;
		Timer *m_pTimer;

		class Camera* m_pCamera;
	private:

		// engine state
		bool m_bIsPaused;

		int m_currentLevel;
		// THREADED LOADING
		bool m_bLoading;

	private:

		class Renderer * m_pRenderer;

		EngineConfig engineConfig;
		class Scene* m_pActiveScene;
		std::vector<Scene*> m_scenes;
	};

}