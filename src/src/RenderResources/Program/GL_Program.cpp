#include <iostream>

#include "GL_Program.h"
#include "GL\glew.h"



GL_Program::GL_Program()
{
	m_id = glCreateProgram();
}

GL_Program::~GL_Program()
{
	glDeleteProgram(m_id);

	for (std::shared_ptr<Shader>& shader : m_attachedShaders)
	{
		glDeleteShader(shader->GetShaderID());
	}

	m_attachedShaders.clear();
}

bool GL_Program::AttachShader(std::shared_ptr<Shader>& addShader)
{
	if (!Program::AttachShader(addShader))
	{
		return false;
	}

	glAttachShader(m_id, addShader->GetShaderID());

	if (GLenum error = glGetError())
	{
		std::cout << "Error creating GL Program. Error ID: " << error << std::endl;
		return false;
	}

	return true;
}

bool GL_Program::Link()
{
	glLinkProgram(m_id);

	GLint isLinked = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);

		std::cout << "Error Linking GL Program. " << &infoLog[0] << std::endl;
		return false;
	}

	return true;
}

void GL_Program::Use()
{
	glUseProgram(m_id);

	glValidateProgram(m_id);
	GLint status = 0;
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "Error Validating GL Program" << std::endl;
	}
}

bool GL_Program::SendParam(const std::string & parameterName, float v0)
{
	int location = getUniformLocation(parameterName);

	if (location == -1)
		return false;

	glUniform1f(location, v0);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, float v0, float v1)
{
	int location = getUniformLocation(parameterName);

	if (location == -1)
		return false;

	glUniform2f(location, v0, v1);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, float v0, float v1, float v2)
{
	int location = getUniformLocation(parameterName);

	if (location == -1)
		return false;

	glUniform3f(location, v0, v1, v2);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, float v0, float v1, float v2, float v3)
{
	int location = getUniformLocation(parameterName);

	if (location == -1)
		return false;

	glUniform4f(location, v0, v1, v2, v3);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, float * v0, unsigned int parameterSize, unsigned int arraySize)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, const float matrix[16])
{
	int location = getUniformLocation(parameterName);
	
	if (location == -1)
		return false;

	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, int v0)
{
	int location = getUniformLocation(parameterName);

	if (location == -1)
		return false;

	glUniform1i(location, v0);
	return true;
}

bool GL_Program::SendParam(const std::string & parameterName, int v0, int v1)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, int v0, int v1, int v2)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, int v0, int v1, int v2, int v3)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, int * v0, unsigned int parameterSize, unsigned int arraySize)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, unsigned int v0)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, unsigned int v0, unsigned int v1)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, unsigned int v0, unsigned int v1, unsigned int v2)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
	return false;
}

bool GL_Program::SendParam(const std::string & parameterName, unsigned int * v0, unsigned int parameterSize, unsigned int arraySize)
{
	return false;
}

bool GL_Program::SendParam(const unsigned int paramLocation, float v0, float v1, float v2)
{
	glUniform3f(paramLocation, v0, v1, v2);
	return true;
}

unsigned int GL_Program::GetLocation(const std::string & paramName)
{
	return (unsigned int)getUniformLocation(paramName);
}

int GL_Program::getUniformLocation(const std::string &name)
{
	std::map<std::string, int>::iterator it;
	
	it = m_uniformMap.find(name);

	// Found the uniform location in the map
	if (it != m_uniformMap.end())
	{
		return it->second;
	}
	// Didnt find the uniform location, search for it
	int location = glGetUniformLocation(m_id, name.c_str());

	// If the name does not correspond to an active uniform name then print an error
	if (location == -1)
	{
		//std::cout << "Error finding uniform in GL Program. Uniform: " << name << " either does not exist or is not active." << std::endl;
		return -1;
	}

	// A valid location was found, so store it in the map
	m_uniformMap.emplace(std::pair<std::string, int>(name, location));

	return location;
}
