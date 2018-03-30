#pragma once
#include <memory>
#include <vector>

class GameObject;

class Scene
{
private:
	// Have a collection of game objects?
	bool m_initialised = false;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

public:
	virtual ~Scene() = 0 {};

	virtual bool Initialise() = 0;


	bool HasInitialised() const
	{
		return m_initialised;
	}
};