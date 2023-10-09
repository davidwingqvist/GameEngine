#include "Header.h"
#include "Scene.h"
#include "D3D11Context.h"
#include "Resource.h"
#include "Debugger.h"

void UpdatePublicBuffer(ID3D11Buffer* buffer, const sm::Matrix& matrix_data)
{
	D3D11_MAPPED_SUBRESOURCE sub;
	HRESULT hr = D3D11Core::Get().Context()->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &sub);
	if (FAILED(hr))
	{
		DEBUG_ERROR("Failed to map public buffer for scene!\n");
	}
	std::memcpy(sub.pData, &matrix_data, sizeof(matrix_data));
	D3D11Core::Get().Context()->Unmap(buffer, 0);

}

Scene::Scene()
{
	m_publicBuffer = nullptr;
	if (!this->CreatePublicBuffer())
		DEBUG_ERROR("Creating public buffer failed for scene!\n")

	UpdatePublicBuffer(m_publicBuffer, sm::Matrix());
}

Scene::~Scene()
{
	if (m_publicBuffer != nullptr)
		m_publicBuffer->Release();
}

bool Scene::CreatePublicBuffer()
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(sm::Matrix);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	return !FAILED(D3D11Core::Get().Device()->CreateBuffer(&desc, NULL, &m_publicBuffer));
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

void Scene::PreDraw()
{
	// Public buffer is set to the first slot in Vertex Shader
	D3D11Core::Get().Context()->VSSetConstantBuffers(0, 1, &m_publicBuffer);
}

void Scene::Draw()
{
	this->PreDraw();
	m_registry.View<model>().ForEach([&](model& model){

		UpdatePublicBuffer(m_publicBuffer, model.worldMatrix);

		// draw each model.
		model.data->Draw();

		});
	m_drawManager.Draw();
}
