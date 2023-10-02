#pragma once
#include "D3D11Context.h"
#include "Direct2DContext.h"
#include "Debugger.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Time.h"
#include "Renderer.h"

class Engine
{
private:

	Window m_window;
	Renderer m_renderer;
	bool shutdown = false;

	std::unordered_map<std::string, Scene> m_scenes;
	Scene* m_currentScene = nullptr;


	void Update();
	void Draw();

public:

	Engine();
	Engine(const std::string& splashScreen);
	~Engine();

	// Run this function to build the engine.
	void Build();

	/*
	
		Run this function to start the whole engine operation.
	
	*/
	void Start();

	void AddScene(const std::string& sceneName);
	void SetScene(const std::string& sceneName);
	Scene* GetScene(const std::string& sceneName);

	void SetSplashScreen(const std::string& fileName);

	void Shutdown();
	
};

