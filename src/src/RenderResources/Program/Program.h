#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../Shader/Shader.h"

class Program
{
protected:
	unsigned int							m_id				= 0;
	bool									m_compiled			= false;
	std::vector<std::shared_ptr<Shader>>	m_attachedShaders;


public:
	Program() {};
	virtual ~Program() = 0 {};

	virtual bool AttachShader(std::shared_ptr<Shader>& addShader) {
		for (std::shared_ptr<Shader>& shader : m_attachedShaders)
		{
			// Cannot have more than one of the same type of shader
			if (shader->GetShaderType() == addShader->GetShaderType())
			{
				return false;
			}
		}

		m_attachedShaders.push_back(addShader);
		return true;
	}

	virtual bool Link() = 0;
	virtual void Use() = 0;

	virtual bool SendParam(const std::string& parameterName, float v0) = 0;
	virtual bool SendParam(const std::string& parameterName, float v0, float v1) = 0;
	virtual bool SendParam(const std::string& parameterName, float v0, float v1, float v2) = 0;
	virtual bool SendParam(const std::string& parameterName, float v0, float v1, float v2, float v3) = 0;
	virtual bool SendParam(const std::string& parameterName, float *v0, unsigned int parameterSize, unsigned int arraySize) = 0;
	virtual bool SendParam(const std::string& parameterName, const float matrix[16]) = 0;


	virtual bool SendParam(const std::string& parameterName, int v0) = 0;
	virtual bool SendParam(const std::string& parameterName, int v0, int v1) = 0;
	virtual bool SendParam(const std::string& parameterName, int v0, int v1, int v2) = 0;
	virtual bool SendParam(const std::string& parameterName, int v0, int v1, int v2, int v3) = 0;
	virtual bool SendParam(const std::string& parameterName, int *v0, unsigned int parameterSize, unsigned int arraySize) = 0;

	virtual bool SendParam(const std::string& parameterName, unsigned int v0) = 0;
	virtual bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1) = 0;
	virtual bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1, unsigned int v2) = 0;
	virtual bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) = 0;
	virtual bool SendParam(const std::string& parameterName, unsigned int *v0, unsigned int parameterSize, unsigned int arraySize) = 0;

	virtual bool BindUniformBlock(const std::string& uniformName, unsigned int uniformIndex) = 0;

	unsigned int ID() { return m_id; }


	virtual bool SendParam(const unsigned int paramLocation, float v0, float v1, float v2) = 0;
	virtual unsigned int GetLocation(const std::string& paramName) = 0;

};


