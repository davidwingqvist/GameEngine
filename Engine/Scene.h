#pragma once
#include "DrawManager.h"

class Scene
{
private:

	recs::recs_registry m_registry;
	std::vector<recs::Entity> m_entities;
	std::function<void(recs::recs_registry&)> m_function;
	DrawManager m_drawManager;

public:

	Scene(recs::recs_registry* registry);
	Scene();
	~Scene();

	void SetLogic(std::function<void(recs::recs_registry&)> function);

	void Update();

	void Draw();
};