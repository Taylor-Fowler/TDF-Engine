#include "FloatyThing.h"
#include "GL\glew.h"
#include "..\..\Engine\RenderLoop.h"
#include "..\..\RenderResources\ShaderModule\ShaderModule.h"
#include "..\..\Engine\Components\Camera\Camera.h"


FloatyThing::FloatyThing()
{
	_renderLoop->GetModule("FloatyThing").lock()->Subscribe(this);
}

FloatyThing::~FloatyThing()
{
	_renderLoop->GetModule("FloatyThing").lock()->Unsubscribe(this);

	glDeleteBuffers(2, m_posBuffer);
	glDeleteTransformFeedbacks(2, m_transformFeedback);
	glDeleteVertexArrays(2, m_vaos);
	delete m_pos;
	delete m_vel;
}

void FloatyThing::Render(std::shared_ptr<Program>& program, const RenderDetails & renderDetails)
{
	if (m_createdAt + m_spawnDelay > AppTime::GetTime())
		return;

	float startSpawn = m_createdAt + m_spawnDelay;
	float elapsed = AppTime::GetTime() - startSpawn;
	if (m_followUniformLoc == 0) m_followUniformLoc = program->GetLocation("follow");


	


	glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer[m_curr]);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * PARTICLE_COUNT, m_pos);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glm::vec3 first(m_pos[0], m_pos[1], m_pos[2]);
	if(glm::distance(first, m_follow) < 1.0f)
	{
		m_follow[0] += ((rand() % 2) - 1) * (rand() % 100) * 0.1f;
		m_follow[1] += ((rand() % 2) - 1) * (rand() % 100) * 0.1f;
		m_follow[2] += ((rand() % 2) - 1) * (rand() % 100) * 0.1f;
	}
	else
	{
		m_follow = Camera::main()->Position() + Camera::main()->Forward() * 5.0f;
	}
	program->SendParam(m_followUniformLoc, m_follow[0], m_follow[1], m_follow[2]);
	program->SendParam("worldTime", (float)AppTime::GetDeltaTime());

	
	glPointSize(1);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_curr]);
	glBindVertexArray(m_vaos[1 - m_curr]);
	glEnable(GL_RASTERIZER_DISCARD);
	glBeginTransformFeedback(GL_POINTS);

	for (int i = 0; i < PARTICLE_COUNT * 0.1; i++)
	{
		if (elapsed < startSpawn + i * 0.0005)
			break;
		if (i != 0)
		{
			unsigned int x = (i - 1) * 3;
			program->SendParam(m_followUniformLoc, m_pos[x], m_pos[x + 1], m_pos[x + 2]);
		}


		glDrawArrays(GL_POINTS, i * 10, 10);
		
	}
	glEndTransformFeedback();
	glDisable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

	glBindVertexArray(m_vaos[m_curr]);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);
	glBindVertexArray(0);

	m_curr = 1 - m_curr;
}

bool FloatyThing::Initialise()
{
	m_createdAt = (float)AppTime::GetTime();
	m_follow = Camera::main()->Position() + Camera::main()->Forward() * 5.0f;
	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		m_pos[i * 3] = m_follow[0] - 5.0f + (rand() % 2) - 1 + rand() % 100 * 0.01f;
		m_pos[i * 3 + 1] = m_follow[1] - 5.0f;
		m_pos[i * 3 + 2] = m_follow[2] - 5.0f + (rand() % 2) - 1 + rand() % 100 * 0.01f;
	}

	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		m_vel[i * 3] = 0.0f;
		m_vel[i * 3 + 1] = 0.0f;
		m_vel[i * 3 + 2] = 0.0f;
	}

	
	glGenVertexArrays(2, m_vaos);
	glGenTransformFeedbacks(2, m_transformFeedback);
	glGenBuffers(2, m_posBuffer);
	glGenBuffers(2, m_velBuffer);
	//glGenBuffers(1, &m_followBuffer);

	for (unsigned int i = 0; i < 2; i++)
	{
		glBindVertexArray(m_vaos[i]);
		glBindBuffer(GL_ARRAY_BUFFER, m_posBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * PARTICLE_COUNT, m_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_velBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * PARTICLE_COUNT, m_vel, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//glBindBuffer(GL_ARRAY_BUFFER, m_followBuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, m_follow, GL_STATIC_DRAW);
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_posBuffer[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, m_velBuffer[i]);
	}
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glBindVertexArray(0);


	return true;
}
