#include "Header.h"
#include "Scene.h"
#include "D3D11Context.h"


Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::SetLogic(std::function<void(recs::recs_registry&)> function)
{
	m_function = function;
}

void Scene::Update()
{
	if (m_function)
		m_function(m_registry);
}

void Scene::Draw()
{
	m_drawManager.Draw();
}
