#pragma once
#include "ShaderModule.h"


class ExplosionModule : public ShaderModule
{
public:
	ExplosionModule(std::shared_ptr<Program> program) : ShaderModule(program) {};
};