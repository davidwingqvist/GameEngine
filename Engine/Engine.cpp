#include "Header.h"
#include "Engine.h"
#include "Debugger.h"

Engine::Engine()
{
	srand(NULL);
	Debugger::Get();

	Window::Desc config;
	config.title = L"Game";
	if (!m_window.Initialize(config))
	{
		Debugger::Get().Print("Couldnt create Window!\n", Debugger::COLOR_RED);
		return;
	}

	D3D11Core::Get().Initialize(&m_window);
	D2D1Core::Get().Initialize();

	this->m_pipelineManager.Initialize();
}

Engine::~Engine()
{
}

void Engine::Update()
{
	MSG msg = { nullptr };

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			shutdown = true;
		}
	}

	if (m_currentScene)
		m_currentScene->Update();
}

void Engine::Draw()
{
	m_pipelineManager.ClearScreen();

	D2D1Core::Get().Begin();

	m_drawManager.Draw();

	D2D1Core::Get().Commit();

	D3D11Core::Get().Present();
}

void Engine::Start()
{
	while (!shutdown)
	{
		auto start = std::chrono::high_resolution_clock::now();
		Update();
		Draw();
		auto end = std::chrono::high_resolution_clock::now();

		Time::Get().SetDeltaTime(std::chrono::duration<float, std::milli>(end - start).count());
	}
}

void Engine::AddScene(const std::string& sceneName, const Scene& scene)
{
	m_scenes.emplace(sceneName, scene);
}
