#pragma once
#include "ShaderModule.h"

class Mesh;

class SkyboxModule : public ShaderModule
{
protected:
	std::shared_ptr<Mesh> m_skyboxMesh;

public:
	SkyboxModule(std::shared_ptr<Program> program);

	~SkyboxModule() override {};

	void Render(RenderDetails renderDetails) override;

protected:

};