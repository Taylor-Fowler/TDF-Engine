#pragma once
#include "Shader.h"


class GL_Shader : Shader
{
public:
	GL_Shader(const char** string, SHADER_TYPE type);
	~GL_Shader() override;
};