#pragma once

class Scene
{
private:

	recs::recs_registry* m_registry = nullptr;
	std::function<void()> m_function;

public:

	Scene();
	Scene(recs::recs_registry* registry);
	~Scene();

	void SetLogic(std::function<void()> function);

	void Update();
};