#pragma once
#include "..\..\Engine\Components\Component.h"
#include "..\..\RenderResources\ShaderParameter\ShaderParameters.h"
#include "..\..\RenderResources\IRender.h"



class FloatyThing : public Component, public IRender
{
private:
	const static unsigned int PARTICLE_COUNT = 111110;

	float		m_createdAt = 0.0f;
	float		m_spawnDelay = 2.0f;
	glm::vec3   m_follow;
	float *m_pos	= new float[PARTICLE_COUNT * 3];
	float *m_vel	= new float[PARTICLE_COUNT * 3];
	unsigned int m_vaos[2];
	unsigned int m_transformFeedback[2];
	unsigned int m_posBuffer[2];
	unsigned int m_velBuffer[2];
	unsigned int m_curr = 0;
	unsigned int m_followBuffer;
	unsigned int m_followUniformLoc = 0;


public:
	FloatyThing();
	~FloatyThing();
	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

protected:
	bool Initialise() override;
};
