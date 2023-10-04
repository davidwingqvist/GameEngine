#include "Header.h"
#include "Scene.h"
#include "D3D11Context.h"
#include "Resource.h"
#include "Debugger.h"


Scene::Scene()
{
	//m_objectBuffer.Create(D3D11Core::Get().Device());
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
	m_registry.View<model>().ForEach([&](model& model){

		//m_objectBuffer.SetData(D3D11Core::Get().Context(), model.worldMatrix);

		// draw each model.
		model.data->Draw();

		});
	m_drawManager.Draw();
}
