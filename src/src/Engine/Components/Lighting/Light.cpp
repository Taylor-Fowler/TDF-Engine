#include "Light.h"

#include "../Objects/GameObject.h"
#include "../Transform/Transform.h"


const Vector3f	Light::DEFAULT_DIFFUSE					= Vector3f(0.4f, 0.4f, 0.4f);
const Vector3f	Light::DEFAULT_DIRECTION				= Vector3f(0.0f, -1.0f, 0.0f);
const double	Light::DEFAULT_SHADOW_UPDATE_INTERVAL	= 0.2;


void Light::UpdatedShadow(double time)
{
	m_lastShadowUpdate = time;
}

Vector3f& Light::GetPosition()
{
	return m_objectAttachedTo->GetTransform()->GetPosition();
}

bool Light::IsTimeToUpdate(double time)
{
	return m_lastShadowUpdate + m_shadowUpdateInterval < time;
}
