#include "GameObject.h"
#include "..\Components\Transform\Transform.h"


GameObject::GameObject()
{		
	m_transform = new Transform();		
}
GameObject::~GameObject()
{
	for (int i = 0; i < m_objectComponents.size(); i++)
		delete m_objectComponents[i];
	m_objectComponents.clear();
	delete m_renderer;
	delete m_transform;
}
//
//GameObject::GameObject(Transform &transform)
//{
//	m_transform = new Transform(transform);
//}
//
//
//GameObject::GameObject(GameObject *parent) : GameObject()
//{
//	m_parentObject = parent;
//}
//
//GameObject::GameObject(GameObject *parent, Transform &transform)
//{
//	m_parentObject = parent;
//	m_transform = new Transform(transform);
//}
//
//GameObject::GameObject(const Renderer &renderer)
//{
//	m_transform = new Transform();
//	m_renderer = renderer.CreateInstance(this);
//}
//
//
//GameObject::GameObject(const GameObject &copyFrom)
//{
//	m_transform = new Transform(*copyFrom.GetTransform());
//	m_renderer = copyFrom.GetRenderer()->CreateInstance(this);
//}