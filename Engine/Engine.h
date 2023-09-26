#pragma once
#include "D3D11Context.h"
#include "Direct2DContext.h"
#include "PipelineManager.h"
#include "Debugger.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Time.h"

class Engine
{
private:

	Window m_window;
	PipelineManager m_pipelineManager;
	bool shutdown = false;

	std::unordered_map<std::string, Scene> m_scenes;
	Scene* m_currentScene = nullptr;


	void Update();
	void Draw();

public:

	Engine();
	~Engine();

	/*
	
		Run this function to start the whole engine operation.
	
	*/
	void Start();

	void AddScene(const std::string& sceneName);
	void SetScene(const std::string& sceneName);
	Scene* GetScene(const std::string& sceneName);

	void SetSplashScreen();

	void Shutdown();
	
};

