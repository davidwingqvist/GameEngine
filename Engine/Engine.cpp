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
		//ERROR
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
}

void Engine::Draw()
{
	m_pipelineManager.ClearScreen();

	D2D1Core::Get().Begin();

	m_drawManager.Draw();

	D2D1Core::Get().Commit();

	D3D11Core::Get().Present();
}

void Engine::EngineStart()
{
	while (!shutdown)
	{
		Update();
		Draw();
	}
}