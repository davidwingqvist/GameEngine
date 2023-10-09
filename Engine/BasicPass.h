#pragma once
#include "Renderpass.h"
#include "Shader.h"

class BasicPass : public IRenderpass
{
private:

	PixelShader m_pixelShader;
	VertexShader m_vertexShader;

public:

	BasicPass();
	virtual ~BasicPass() override;

	virtual void Prepass() override;
	virtual void Pass(Scene* currentScene) override;
	virtual void Postpass() override;
};