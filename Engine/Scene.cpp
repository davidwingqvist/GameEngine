#include "Header.h"
#include "Scene.h"
#include "D3D11Context.h"
#include "Resource.h"
#include "Debugger.h"

void UpdatePublicBuffer(ID3D11Buffer* buffer, const sm::Matrix& matrix_data)
{

}

Scene::Scene()
{
	m_publicBuffer = nullptr;
	this->CreatePublicBuffer();
}

Scene::~Scene()
{
	if (m_publicBuffer)
		m_publicBuffer->Release();
}

void Scene::CreatePublicBuffer()
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

		UpdatePublicBuffer(m_publicBuffer, model.worldMatrix);

		// draw each model.
		model.data->Draw();

		});
	m_drawManager.Draw();
}
