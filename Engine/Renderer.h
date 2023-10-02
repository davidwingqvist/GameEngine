#pragma once
#include "Renderpass.h"
#include "PipelineManager.h"


class Renderer
{
private:

	std::vector<IRenderpass*> m_renderPasses;
	PipelineManager m_pipelineManager;

public:

	Renderer();
	~Renderer();

	void Initialize();

	void Draw(Scene* currentScene);

	PipelineManager& GetPipelineManager();
};