#include <algorithm>

#include "Component.h"
#include "..\GameObject\GameObject.h"

std::vector<Component*> Component::_allComponents;
EventSystem*			Component::_eventSystem				= nullptr;
RenderResourceFactory*	Component::_renderResourceFactory	= nullptr;

Component::Component()
{
	_allComponents.push_back(this);
}

Component::~Component()
{
	auto it = std::find(_allComponents.begin(), _allComponents.end(), this);

	if (it != _allComponents.end())
		_allComponents.erase(it);

	m_objectAttachedTo->RemoveComponent(this);
}
