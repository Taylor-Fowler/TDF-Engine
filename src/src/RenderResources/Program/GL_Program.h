#pragma once
#include <map>
#include "Program.h"



class GL_Program : public Program
{
private:
	std::map<std::string, int> m_uniformMap;


public:
	GL_Program();
	~GL_Program() override;

	bool AttachShader(std::shared_ptr<Shader>&) override;
	bool Link() override;
	void Use() override;


	bool SendParam(const std::string& parameterName, float v0) override;
	bool SendParam(const std::string& parameterName, float v0, float v1)override;
	bool SendParam(const std::string& parameterName, float v0, float v1, float v2) override;
	bool SendParam(const std::string& parameterName, float v0, float v1, float v2, float v3) override;
	bool SendParam(const std::string& parameterName, float *v0, unsigned int parameterSize, unsigned int arraySize) override;
	bool SendParam(const std::string& parameterName, const float matrix[16]) override;


	bool SendParam(const std::string& parameterName, int v0) override;
	bool SendParam(const std::string& parameterName, int v0, int v1) override;
	bool SendParam(const std::string& parameterName, int v0, int v1, int v2) override;
	bool SendParam(const std::string& parameterName, int v0, int v1, int v2, int v3) override;
	bool SendParam(const std::string& parameterName, int *v0, unsigned int parameterSize, unsigned int arraySize) override;

	bool SendParam(const std::string& parameterName, unsigned int v0) override;
	bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1) override;
	bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1, unsigned int v2) override;
	bool SendParam(const std::string& parameterName, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) override;
	bool SendParam(const std::string& parameterName, unsigned int *v0, unsigned int parameterSize, unsigned int arraySize) override;

	bool SendParam(const unsigned int paramLocation, float v0, float v1, float v2) override;
	unsigned int GetLocation(const std::string& paramName) override;
private:
	int getUniformLocation(const std::string& name);
};