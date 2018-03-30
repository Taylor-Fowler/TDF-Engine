#pragma once
#include <string>
#include "Shader.h"


class GL_Shader : public Shader
{
public:
	GL_Shader(std::string source, SHADER_TYPE type);
	~GL_Shader() override;
};