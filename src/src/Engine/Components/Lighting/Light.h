#pragma once
#include "..\Component.h"
#include "glm\glm.hpp"

const unsigned int MAX_DIRECTIONAL_LIGHTS = 10;
const unsigned int MAX_POINT_LIGHTS = 10;
const unsigned int MAX_SPOT_LIGHTS = 10;

class Light : public Component
{
public:
	static const double		DEFAULT_SHADOW_UPDATE_INTERVAL;

protected:
	static glm::vec4	AmbientLight;

	// Light shadow attributes
	bool	m_shadowsEnabled		= false;
	double	m_lastShadowUpdate		= 0.0;
	double	m_shadowUpdateInterval	= DEFAULT_SHADOW_UPDATE_INTERVAL;

private:
	static unsigned int			UniformBufferID;
	static const unsigned int	UniformBufferBindingPoint;

public:
	Light();
	virtual ~Light() = 0 {};

	static unsigned int GetUniformBufferID()
	{
		return UniformBufferID;
	}
	static unsigned int GetUniformBufferBindingPoint()
	{
		return UniformBufferBindingPoint;
	}

	static void SetAmbientLight(glm::vec4 ambient);
	static glm::vec4 GetAmbientLight()
	{
		return AmbientLight;
	}


	static void InitialiseUniformBuffer();



	//virtual void SetShadowMatrix(float *shadow) = 0;

	void UpdatedShadow(double time);
	bool IsTimeToUpdate(double time);


	void EnableShadows()				{ m_shadowsEnabled = true; }
	void DisableShadows()				{ m_shadowsEnabled = false; }
	void ToggleShadows()				{ m_shadowsEnabled = !m_shadowsEnabled; }


	bool		IsShadowsEnabled()		{ return m_shadowsEnabled; }
	double		GetLastShadowUpdate()	{ return m_lastShadowUpdate; }

	void Enable() override
	{
		if (!m_enabled)
			updateUbo();
		Component::Enable();
	}

	void Disable() override
	{
		if (m_enabled)
			updateUbo();

		Component::Disable();
	}

protected:
	virtual void updateUbo() = 0;
};


class DirectionalLight : public Light
{
private:
	static unsigned int Count; // = 0
	unsigned int		m_index;

	glm::vec3 m_direction = glm::vec3(0.5f, -1.0f, 0.5f);
	glm::vec3 m_diffuse = glm::vec3(1.0f, 0.2f, 0.2f);

public:
	DirectionalLight();
	~DirectionalLight() override {};

	void SetDiffuse(glm::vec3 diffuse)
	{
		m_diffuse = diffuse;
		if (m_enabled)
			updateUbo();
	}
	void SetDirection(glm::vec3 direction)
	{
		m_direction = direction;
		if (m_enabled)
			updateUbo();
	}


	glm::vec3 GetDiffuse()
	{
		return m_diffuse;
	}
	glm::vec3 GetDirection()
	{
		return m_direction;
	}

protected:
	void Update() override;
	bool Initialise() override;

	void updateUbo() override;
};


class PointLight : public Light
{
private:
	static unsigned int Count; // = 0
	unsigned int		m_index;

	glm::vec3 m_position;
	glm::vec3 m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	PointLight();
	~PointLight() override {};

	void SetDiffuse(glm::vec3 diffuse)
	{
		m_diffuse = diffuse;
		if (m_enabled)
			updateUbo();
	}
	void SetSpecular(glm::vec3 specular)
	{
		m_specular = specular;
		if (m_enabled)
			updateUbo();
	}


	glm::vec3 GetDiffuse()
	{
		return m_diffuse;
	}
	glm::vec3 GetSpecular()
	{
		return m_specular;
	}


protected:
	void Update() override;
	bool Initialise() override;

	void updateUbo() override;
};


class SpotLight : public Light
{
private:
	static unsigned int Count; // = 0
	unsigned int		m_index;

	glm::vec3	m_position;
	glm::vec3	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3	m_direction = glm::vec3(-0.577f, -0.577f, -0.577f);
	float		m_cutoff = 60.0f;
	float		m_attenuation = 3.0f;

public:
	SpotLight();
	~SpotLight() override {};




protected:
	bool Initialise() override;

	void updateUbo() override;
};
