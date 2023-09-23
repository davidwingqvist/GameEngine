#pragma once
#include "D3D11Context.h"
#include "Direct2DContext.h"
#include "PipelineManager.h"
#include "Debugger.h"
#include "ResourceManager.h"
#include "DrawManager.h"

class Engine
{
private:

	Window m_window;
	PipelineManager m_pipelineManager;
	bool shutdown = false;
	DrawManager m_drawManager;


public:

	recs::recs_registry m_3dObjects;

	Engine();
	~Engine();
	void Update();
	void Draw();
	void EngineStart();
	
};

