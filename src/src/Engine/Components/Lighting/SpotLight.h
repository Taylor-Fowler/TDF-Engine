#pragma once
#include "PointLight.h"
#include "../Rendering/FBOs/DepthPlanarFBC.h"

class SpotLight : public PointLight
{

private:
	Vector3f		m_direction		= DEFAULT_DIRECTION;
	float			m_cutoff		= 45.0f;
	float			m_attenuation	= 1.0f;
	float			*m_shadowMatrix;
	DepthPlanarFBC	m_depthFBC;

public:
	SpotLight();
	~SpotLight() override {};

	void SetDirection(const Vector3f& d)			{ m_direction = d; }
	void SetCutoff(float c)							{ m_cutoff = c; }
	void SetAttenuation(float a)					{ m_attenuation = a; }
	void SetShadowMatrix(float *shadow) override	{ m_shadowMatrix = shadow; }

	// TO DO: Get forward vector from gameObject transform and use that as direction
	//		  Add the option for static direction, set a direction that is not dependant on parent direction
	Vector3f&				GetDirection()			{ return m_direction; }
	float					GetCutoff() const		{ return m_cutoff; }
	float					GetAttenuation() const	{ return m_attenuation; }
	FrameBufferController&	GetShadowFBO()			{ return m_depthFBC; }
	float*					GetShadowMatrix()		{ return m_shadowMatrix; }

	void Awake() override {};
	void Update() override {};
	bool Initialise() override;
};