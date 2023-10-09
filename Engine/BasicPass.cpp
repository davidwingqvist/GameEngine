#include "Header.h"
#include "BasicPass.h"
#include "Debugger.h"
#include "D3D11Context.h"

BasicPass::BasicPass()
{
	if(!m_pixelShader.Create("BasicPixelShader"))
		DEBUG_ERROR("Couldnt create BasicPixelShader!\n")
	if(!m_vertexShader.Create("BasicVertexShader"))
		DEBUG_ERROR("Couldnt create BasicVertexShader!\n")
}

BasicPass::~BasicPass()
{

}

void BasicPass::Prepass()
{
	D3D11Core::Get().Context()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	D3D11Core::Get().Context()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
}

void BasicPass::Pass(Scene* currentScene)
{
	currentScene->Draw();
}

void BasicPass::Postpass()
{

}