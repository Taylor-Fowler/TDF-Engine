#pragma once
#include "Light.h"

class GameObject;

class DirectionalLight : public Light
{
private:
	Vector3f	m_direction		= DEFAULT_DIRECTION;
	float		*m_shadowMatrix;

public:
	DirectionalLight();
	~DirectionalLight() override {};

	void SetDirection(const Vector3f& d) { m_direction = d; }
	void SetShadowMatrix(float *shadow) override { m_shadowMatrix = shadow; }

	Vector3f& GetDirection() { return m_direction; }
};