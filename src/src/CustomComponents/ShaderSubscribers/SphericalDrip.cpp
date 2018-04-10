#include "SphericalDrip.h"

#include "GL\glew.h"
#include "..\..\Engine\RenderLoop.h"
#include "..\..\RenderResources\ShaderModule\ShaderModule.h"

SphericalDrip::SphericalDrip()
{
	_renderLoop->GetModule("SphericalDrip").lock()->Subscribe(this);
}

SphericalDrip::~SphericalDrip()
{
	_renderLoop->GetModule("SphericalDrip").lock()->Unsubscribe(this);
	glDeleteBuffers(2, m_hitBuffer);
	glDeleteBuffers(2, m_posBuffer);
	glDeleteBuffers(2, m_velBuffer);
	glDeleteBuffers(2, m_spawnedBuffer);
	glDeleteTransformFeedbacks(2, m_transformFeedback);
	glDeleteVertexArrays(2, m_vaos);

	delete m_hit;
	delete m_spawnedAt;
	delete m_pos;
	delete m_vel;
}

void SphericalDrip::Render(std::shared_ptr<Program>& program, const RenderDetails & renderDetails)
{
	if (m_createdAt + m_spawnDelay > AppTime::GetTime())
		return;
	m_spherePosition.Render(program, "spherePosition");
	program->SendParam("ambientMaterial[0]", 0.0f, 1.0f, 0.0f);
	program->SendParam("ambientMaterial[1]", 0.0f, 0.0f, 1.0f);
	program->SendParam("sphereRadius", m_sphereRadius);
	program->SendParam("worldTime", (float)AppTime::GetTime());
	program->SendParam("sphereBottomY", m_sphereBottomY);

	glEnable(GL_RASTERIZER_DISCARD);
	glPointSize(1);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_curr]);


	glBeginTransformFeedback(GL_POINTS);
	glBindVertexArray(m_vaos[1 - m_curr]);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glBindVertexArray(m_vaos[m_curr]);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

	glBindVertexArray(0);

	m_curr = 1 - m_curr;
}

bool SphericalDrip::Initialise()
{
	m_createdAt = (float)AppTime::GetTime();
	float birthTime = m_createdAt + m_spawnDelay;
	float posx = m_spherePosition.Data()[0];
	float posy = m_spherePosition.Data()[1] + m_sphereRadius;
	float posz = m_spherePosition.Data()[2];

	for (unsigned int i = 0; i < PARTICLE_COUNT; i++)
	{
		m_hit[i] = 0;
		m_spawnedAt[i] = birthTime + 0.0001f * i;

		m_pos[i * 3] = posx;
		m_pos[i * 3 + 1] = posy;
		m_pos[i * 3 + 2] = posz;

		m_vel[i * 3] = 0.0f;
		m_vel[i * 3 + 1] = 0.0f;
		m_vel[i * 3 + 2] = 0.0f;
	}
	m_sphereBottomY = m_spherePosition.Data()[1] - m_sphereRadius;

	glGenVertexArrays(2, m_vaos);
	glGenTransformFeedbacks(2, m_transformFeedback);
	glGenBuffers(2, m_hitBuffer);
	glGenBuffers(2, m_spawnedBuffer);
	glGenBuffers(2, m_posBuffer);
	glGenBuffers(2, m_velBuffer);

	for (unsigned int i = 0; i < 2; i++)
	{
		glBindVertexArray(m_vaos[i]);
		glBindBuffer(GL_ARRAY_BUFFER, m_hitBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(int) * PARTICLE_COUNT, m_hit, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_spawnedBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PARTICLE_COUNT, m_spawnedAt, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * PARTICLE_COUNT, m_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_velBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * PARTICLE_COUNT, m_vel, GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(3);

		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_hitBuffer[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, m_spawnedBuffer[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, m_posBuffer[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 3, m_velBuffer[i]);

	}
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glBindVertexArray(0);

	return true;
}
