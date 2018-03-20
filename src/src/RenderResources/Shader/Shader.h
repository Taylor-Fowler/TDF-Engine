#pragma once


class Shader
{
public:
	enum SHADER_TYPE { VERTEX, FRAGMENT, GEOMETRY, TESSELATION, COMPUTE };
protected:
	unsigned int	m_id		= 0;
	bool			m_compiled	= false;
	SHADER_TYPE		m_type		= VERTEX;

public:
	Shader(SHADER_TYPE type) 
		: m_type(type) {};
	virtual ~Shader() = 0 {};


	unsigned int GetShaderID() const { return m_id; }
	SHADER_TYPE	GetShaderType() const { return m_type; }
};