#pragma once
#include "Light.h"



class PointLight : public Light
{
public:
	static const Vector3f DEFAULT_SPECULAR;

protected:
	Vector3f		m_specular	= DEFAULT_SPECULAR;


private:
	float			*m_shadowMatrix; // This should be a vector of 6 elements, one shadow matrix for each cube face

public:
	PointLight();
	~PointLight() override {};

	void SetShadowMatrix(float *shadow) override { m_shadowMatrix = shadow; }
	void SetSpecular(const Vector3f& s) { m_specular = s; }


	Vector3f& GetSpecular() { return m_specular; }


	void Awake() override {};
	void Update() override {};
	bool Initialise() override { return true; };

};