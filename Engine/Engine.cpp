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


	this->AddScene("Test");
	this->SetScene("Test");

	ResourceManager::Get().GetResource<Model3D>("Villager.fbx");
	
	this->SetSplashScreen("peeky.jpg");
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

	if (m_currentScene)
		m_currentScene->Draw();

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

void Engine::AddScene(const std::string& sceneName)
{
	Scene newScene;
	m_scenes.emplace(sceneName, newScene);
	Debugger::Get().Print("Added Scene: '" + sceneName + "'\n", Debugger::COLOR_GREEN);
}

void Engine::SetScene(const std::string& sceneName)
{
	if (m_scenes.find(sceneName) == m_scenes.end())
	{
		Debugger::Get().Print("No scene with the name: '" + sceneName + "' found.\n", Debugger::COLOR_RED);
		return;
	}

	Debugger::Get().Print("Scene set to: '" + sceneName + "'\n", Debugger::COLOR_GREEN);
	m_currentScene = &m_scenes[sceneName];
}

Scene* Engine::GetScene(const std::string& sceneName)
{
	return &m_scenes[sceneName];
}

void Engine::SetSplashScreen(const std::string& fileName)
{
	object2D splash(0,0, D3D11Core::Get().GetWindow()->GetWidth(), D3D11Core::Get().GetWindow()->GetHeight());

	Image2D* image = ResourceManager::Get().GetResource<Image2D>(fileName).get();

	m_pipelineManager.ClearScreen();
	D2D1Core::Get().Begin();
	D2D1Core::Get().DrawP(splash, image->GetImage());
	D2D1Core::Get().Commit();
	D3D11Core::Get().Present();
}

void Engine::Shutdown()
{
	Debugger::Get().Print("Engine has started shutdown sequence.\n", Debugger::COLOR_WHITE);
	shutdown = true;
}

