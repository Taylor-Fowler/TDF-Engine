#include "Light.h"
#include "..\..\GameObject\GameObject.h"
#include "..\Transform\Transform.h"
#include "..\..\EventSystem\EventSystem.h"

#include "GL\glew.h"


glm::vec4			Light::AmbientLight						= glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
unsigned int		Light::UniformBufferID					= 0;
const unsigned int	Light::UniformBufferBindingPoint		= 1;

unsigned int		DirectionalLight::Count					= 0;
unsigned int		PointLight::Count						= 0;
unsigned int		SpotLight::Count						= 0;

const double	Light::DEFAULT_SHADOW_UPDATE_INTERVAL	= 0.2;


Light::Light()
{
}

void Light::SetAmbientLight(glm::vec4 ambient)
{
	AmbientLight = ambient;
	glBindBuffer(GL_UNIFORM_BUFFER, UniformBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(AmbientLight), &AmbientLight);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Light::InitialiseUniformBuffer()
{
	glGenBuffers(1, &UniformBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, UniformBufferID);
	glBufferData(
		GL_UNIFORM_BUFFER, 
		16 + 
		(48 * MAX_DIRECTIONAL_LIGHTS) +
		(52 * MAX_POINT_LIGHTS) + 
		(76 * MAX_SPOT_LIGHTS), 
		NULL, 
		GL_DYNAMIC_DRAW
	);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(AmbientLight), &AmbientLight);
	glBindBufferBase(GL_UNIFORM_BUFFER, UniformBufferBindingPoint, UniformBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Light::UpdatedShadow(double time)
{
	m_lastShadowUpdate = time;
}

bool Light::IsTimeToUpdate(double time)
{
	return m_lastShadowUpdate + m_shadowUpdateInterval < time;
}

DirectionalLight::DirectionalLight()
{
	m_index = Count;
	Count++;
}

void DirectionalLight::Update()
{
	if (_eventSystem->IsKeyDown(ES_KEYC_T))
	{
		if (m_enabled)
			Disable();
		else
			Enable();
	}
}

bool DirectionalLight::Initialise()
{
	updateUbo();
	return true;
}

void DirectionalLight::updateUbo()
{
	if (m_index < MAX_DIRECTIONAL_LIGHTS)
	{
		int en = (int)m_enabled;
		glBindBuffer(GL_UNIFORM_BUFFER, Light::GetUniformBufferID());
		glBufferSubData(GL_UNIFORM_BUFFER, 16 + (48 * m_index), 4, &en);
		// No need to update other properties if the light was justr disabled
		if (m_enabled)
		{
			glm::vec4 direction(m_direction, 1.0f);
			glm::vec4 diffuse(m_diffuse, 1.0f);
			/*glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * m_index) + 4, 16, &direction);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * m_index) + 20, 16, &diffuse);*/
			glBufferSubData(GL_UNIFORM_BUFFER, 32 + (48 * m_index), 16, &direction);
			glBufferSubData(GL_UNIFORM_BUFFER, 48 + (48 * m_index), 16, &diffuse); 
		}
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

PointLight::PointLight()
{
	m_index = Count;
	Count++;
}

void PointLight::Update()
{
	auto objPos = m_objectAttachedTo->GetTransform()->Position();

	if (objPos != m_position)
	{
		m_position = objPos;
		updateUbo();
	}
}

bool PointLight::Initialise()
{
	m_position = m_objectAttachedTo->GetTransform()->Position();
	updateUbo();
	return true;
}

void PointLight::updateUbo()
{
	if (m_index < MAX_DIRECTIONAL_LIGHTS)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, Light::GetUniformBufferID());
		glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * m_index), 4, &m_enabled);
		// No need to update other properties if the light was justr disabled
		if (m_enabled)
		{
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * m_index) + 4, 12, &m_position);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * m_index) + 20, 12, &m_diffuse);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * m_index) + 36, 12, &m_specular);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

SpotLight::SpotLight()
{
	m_index = Count;
	Count++;
}

bool SpotLight::Initialise()
{
	m_position = m_objectAttachedTo->GetTransform()->Position();
	updateUbo();
	return true;
}

void SpotLight::updateUbo()
{
	if (m_index < MAX_DIRECTIONAL_LIGHTS)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, Light::GetUniformBufferID());
		glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index), 4, &m_enabled);
		// No need to update other properties if the light was justr disabled
		if (m_enabled)
		{
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 4,  12, &m_position);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 20, 12, &m_diffuse);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 36, 12, &m_specular);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 52, 12, &m_direction);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 68, 4, &m_cutoff);
			glBufferSubData(GL_UNIFORM_BUFFER, 16 + (36 * MAX_DIRECTIONAL_LIGHTS) + (52 * MAX_POINT_LIGHTS) + (76 * m_index) + 72, 4, &m_attenuation);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
