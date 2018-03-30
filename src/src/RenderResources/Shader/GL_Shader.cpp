#include <iostream>

#include "GL_Shader.h"
#include "GL\glew.h"

GL_Shader::GL_Shader(std::string source, SHADER_TYPE type)
	: Shader(type)
{
	if(type == VERTEX)
		m_id = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FRAGMENT)
		m_id = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type == GEOMETRY)
		m_id = glCreateShader(GL_GEOMETRY_SHADER);
	else if (type == TESSELATION)
		m_id = glCreateShader(GL_TESS_CONTROL_SHADER);
	else if (type == COMPUTE)
		m_id = glCreateShader(GL_COMPUTE_SHADER);

	auto glchar = static_cast<const GLchar*>(source.c_str());

	glShaderSource(m_id, 1, &glchar, 0);
	glCompileShader(m_id);

	GLint isCompiled = 0;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		std::cout << "GL Shader compilation failed." << std::endl;
		glDeleteShader(m_id);
		return;
	}
	
	m_compiled = true;
}

GL_Shader::~GL_Shader()
{
	glDeleteShader(m_id);
}
