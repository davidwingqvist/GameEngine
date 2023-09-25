#pragma once
#include "D3D11Context.h"
#include "Direct2DContext.h"
#include "PipelineManager.h"
#include "Debugger.h"
#include "ResourceManager.h"
#include "DrawManager.h"
#include "Scene.h"
#include "Time.h"

class Engine
{
private:

	Window m_window;
	PipelineManager m_pipelineManager;
	bool shutdown = false;
	DrawManager m_drawManager;

	std::unordered_map<std::string, Scene> m_scenes;
	Scene* m_currentScene = nullptr;


	void Update();
	void Draw();

public:

	recs::recs_registry m_3dObjects;

	Engine();
	~Engine();

	/*
	
		Run this function to start the whole engine operation.
	
	*/
	void Start();

	void AddScene(const std::string& sceneName, const Scene& scene);
	
};

