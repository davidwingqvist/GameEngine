#include "Header.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

recs::recs_registry* Scene::GetRegistry()
{
	return &m_registry;
}

void Scene::SetLogic(std::function<void()> function)
{
	m_function = function;
}

void Scene::Update()
{
	if (m_function)
		m_function();
}

void Scene::Draw()
{
	m_drawManager.Draw();
}
