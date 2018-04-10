#pragma once
#include "..\..\Engine\Components\Component.h"
#include "..\..\RenderResources\ShaderParameter\ShaderParameters.h"
#include "..\..\RenderResources\IRender.h"


class SphericalDrip : public Component, public IRender
{
private:
	const static unsigned int PARTICLE_COUNT = 100000;

	float		m_createdAt			= 0.0f;
	float		m_spawnDelay		= 2.0f;
	float		m_sphereRadius		= 4.0f;
	FloatData3	m_spherePosition	= { -5.0f, 16.0f, -5.0f };
	float		m_sphereBottomY		= 12.0f;

	unsigned int m_vaos[2];
	unsigned int m_transformFeedback[2];
	unsigned int m_hitBuffer[2];
	unsigned int m_spawnedBuffer[2];
	unsigned int m_velBuffer[2];
	unsigned int m_posBuffer[2];
	unsigned int m_curr;


	int		*m_hit			= new int[PARTICLE_COUNT];
	float	*m_spawnedAt	= new float[PARTICLE_COUNT];
	float	*m_pos			= new float[PARTICLE_COUNT * 3];
	float	*m_vel			= new float[PARTICLE_COUNT * 3];

public:
	SphericalDrip();
	~SphericalDrip();
	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

protected:
	bool Initialise() override;
};