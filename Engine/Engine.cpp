#include "Header.h"
#include "Engine.h"
#include "Debugger.h"

Engine::Engine()
{
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

	m_image = ResourceManager::Get().GetResource<Image2D>("mainCharacter.png");

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
	D2D1Core::Get().Begin();

	static object2D obj(0, 0, 100, 100);

	obj.x += 0.01f;

	D2D1Core::Get().DrawP(obj, m_image->GetImage());

	D2D1Core::Get().Commit();

	D3D11Core::Get().Present();
}

void Engine::Start()
{
	while (!shutdown)
	{
		Update();
		Draw();
	}
}