#pragma once
#include "D3D11Context.h"
#include "Direct2DContext.h"
#include "PipelineManager.h"
#include "Debugger.h"
#include "ResourceManager.h"


class Engine
{
private:

	Window m_window;
	PipelineManager m_pipelineManager;
	bool shutdown = false;
	std::shared_ptr<Image2D> m_image;


public:

	recs::recs_registry m_registry;

	Engine();
	~Engine();
	void Update();
	void Draw();
	void Start();
	
};

