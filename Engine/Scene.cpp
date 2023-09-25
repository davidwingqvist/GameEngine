#include "Header.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(recs::recs_registry* registry)
{
	m_registry = registry;
}

Scene::~Scene()
{
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
