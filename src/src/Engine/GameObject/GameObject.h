#pragma once
#include <memory>
#include <vector>


#include "..\Components\Component.h"
#include "..\Components\Renderer\Renderer.h"

class Transform;
class Renderer;

class GameObject
{
protected:
	GameObject				*m_parentObject		= nullptr;
	Transform				*m_transform		= nullptr;
	std::vector<Component*>	m_objectComponents;

public:
	Renderer	*m_renderer		= nullptr;


	// Create blank GameObject with default transform.
	// Example usage: placeholder
	GameObject();
	//// Create GameObject with a copied transform
	//// Example usage: Create a GameObject in the same position with the same rotation and scale as another object
	//GameObject(Transform &transform);
	//// Create GameObject with parent object and default transform.
	//// Example usage: creating a gameobject whose position is local to its parent
	//GameObject(GameObject *parent);
	//// Create GameObject with parent object and specified transform.
	//// Example usage: creating a gameobject whose position is local to its parent and initial position is specified
	//GameObject(GameObject *parent, Transform &transform);

	//// Create GameObject with copied renderer to render the same mesh with the same material
	//// with different components
	//// Example usage: Copy a model but have different behaviours/position
	//GameObject(const Renderer &renderer);



	//// Create a copy of the game object with instanced components
	//GameObject(const GameObject &copyFrom);

	/*template <class Derived>
	void AddComponent();*/

	template <class T>
	inline T& AddComponent()
	{
		Component* c = new T();
		m_objectComponents.push_back(c);

		c->m_objectAttachedTo = this;
		c->Initialise();

		return static_cast<T&>(*c);
	};

	template <>
	inline Renderer& AddComponent<Renderer>()
	{
		m_renderer = new Renderer();
		m_renderer->m_objectAttachedTo = this;
		
		return *m_renderer;
	}

	template <class T>
	inline void RemoveComponent(T* const component)
	{
		auto location = std::find(m_objectComponents.begin(), m_objectComponents.end(), component);
		if (location != m_objectComponents.end())
			m_objectComponents.erase(location);
	}

	Transform* GetTransform() const
	{
		return m_transform;
	}

	Renderer* GetRenderer() const
	{
		return m_renderer;
	}

	GameObject* GetParentObject() const
	{
		return m_parentObject;
	}

protected:

private:
	//GameObject(const GameObject& copyFrom) {}; // Cannot copy game object
};