#pragma once


// Material Definition within TDF:
// ========================================================
//
// A collection of shader parameters that define the attributes of a given object in relation to a specified shader program.
// The material class is simplistically, a specialised parameter collection. The material is associated with a specific shader program
// which, as the active rendering program, will trigger the shader parameter collection to be sent down the rendering pipeline.

#include "../IRender.h"

class Material : public IRender
{
private:
	unsigned int m_programID; // The ID of the Shader Program that this material is registered to



public:
	Material() {};
	~Material() override {};

	void Render(std::shared_ptr<Program>& program) const override {};



};