#pragma once
#include <vector>
#include "..\..\Utilities\Time.h"

// Forward declarations
class GameObject;
class EventSystem;
class RenderResourceFactory;
class RenderLoop;

class Component
{
	friend class GameObject;
	friend int main(int argc, char *argv[]);
private:
	static std::vector<Component*>	_allComponents;
protected:
	static EventSystem *			_eventSystem;
	static RenderResourceFactory *	_renderResourceFactory;
	static RenderLoop *				_renderLoop;

	GameObject	*m_objectAttachedTo	= nullptr;
	bool		m_enabled			= true;
	

public:
	~Component();


	bool IsEnabled() {
		return m_enabled;
	}

	void Enable() {
		m_enabled = true;
	}

	void Disable() {
		m_enabled = false;
	}

	GameObject& GetGameObject() {
		return *m_objectAttachedTo;
	}

	static void AwakeAll() {
		for (auto& component : _allComponents)
			component->Awake();
	}

protected:
	Component();

	static EventSystem * const eventSystem() {
		return _eventSystem;
	}
	static RenderResourceFactory * const renderResourceFactory() {
		return _renderResourceFactory;
	}

	virtual void Update() {};
	virtual void Awake() {};
	virtual bool Initialise() { return true; }

};