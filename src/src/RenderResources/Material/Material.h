#pragma once
#include <memory>

// Material Definition within TDF:
// ========================================================
//
// A collection of shader parameters that define the attributes of a given object in relation to a specified shader program.
// The material class is simplistically, a specialised parameter collection. The material is associated with a specific shader program
// which, as the active rendering program, will trigger the shader parameter collection to be sent down the rendering pipeline.

#include "../ShaderParameter/ShaderParamList.h"

class Renderer;
class ShaderModule;

class Material : public ShaderParamList
{
	friend class Renderer;
private:
	Renderer*		m_attachedTo	= nullptr;

public:
	Material(std::shared_ptr<ShaderModule> module);

	~Material(){};

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;
	Renderer* AttachedTo()
	{
		return m_attachedTo;
	}
};