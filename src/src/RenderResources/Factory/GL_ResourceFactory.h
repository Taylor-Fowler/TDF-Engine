#pragma once
#include "RenderResourceFactory.h"


class GL_ResourceFactory : public RenderResourceFactory
{

public:
	GL_ResourceFactory(RenderLoop *const renderLoop, FileReadWrite *const fileRW, ResourceManager *const resourceManager, Loader3D *const loader3D);

	~GL_ResourceFactory() override {};


	std::shared_ptr<Texture> CreateStaticTexture(const std::string& name) const override;
	Texture* CreateDynamicTexture(const std::string& name) const override;

	std::shared_ptr<Material> CreateStaticMaterial(unsigned int programID) const override;
	Material* CreateDynamicMaterial(unsigned int programID) const override;

	std::shared_ptr<Mesh> CreateStaticMesh(const std::string& name) const override;
	Mesh* CreateDynamicMesh(const std::string& name) const override;

	std::shared_ptr<Shader> CreateShader(const std::string& name) const override {};
	std::shared_ptr<Program> CreateProgram(std::vector<std::shared_ptr<Shader>>& shaders) const override {};

};