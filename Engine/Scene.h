#pragma once
#include "DrawManager.h"

class Scene
{
private:

	recs::recs_registry m_registry;
	std::function<void()> m_function;
	DrawManager m_drawManager;

public:

	Scene();
	~Scene();

	recs::recs_registry* GetRegistry();

	void SetLogic(std::function<void()> function);

	void Update();

	void Draw();
};