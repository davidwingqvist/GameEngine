#include "Header.h"
#include "Renderer.h"
#include "BasicPass.h"

Renderer::Renderer()
{
	BasicPass basicPass(&m_pipelineManager);
	m_renderPasses.push_back(&basicPass);
}

Renderer::~Renderer()
{
	for (int i = 0; i < m_renderPasses.size(); i++)
	{
		if (m_renderPasses[i])
		{
			delete m_renderPasses[i];
		}
	}
}

void Renderer::Initialize()
{
	m_pipelineManager.Initialize();
}

void Renderer::Draw(Scene* currentScene)
{
	for (auto& pass : m_renderPasses)
	{
		if (pass->IsActive())
		{
			pass->Prepass();
			pass->Pass(currentScene);
			pass->Postpass();
		}
	}
}

PipelineManager& Renderer::GetPipelineManager()
{
	return m_pipelineManager;
}
