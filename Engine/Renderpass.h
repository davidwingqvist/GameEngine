#pragma once
#include "Scene.h"

class IRenderpass
{
private:

	bool m_isActive = true;

public:
	IRenderpass() = default;
	virtual ~IRenderpass() = 0 {};

	void SetActive(const bool& tog);
	const bool& IsActive() const;

	virtual void Prepass() = 0;
	virtual void Pass(Scene* currentScene) = 0;
	virtual void Postpass() = 0;
};