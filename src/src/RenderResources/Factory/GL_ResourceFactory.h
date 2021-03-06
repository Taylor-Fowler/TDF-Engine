#pragma once
#include "RenderResourceFactory.h"


class GL_ResourceFactory : public RenderResourceFactory
{

public:
	GL_ResourceFactory(RenderLoop *const renderLoop, FileReadWrite *const fileRW, ResourceManager *const resourceManager, Loader3D *const loader3D, ImageLoader *const iLoader);

	~GL_ResourceFactory() override {};


	std::shared_ptr<Texture> LoadStaticTexture(const std::string& name) const override;
	Texture* LoadDynamicTexture(const std::string& name) const override;

	std::shared_ptr<CubeTexture> LoadStaticCubeTexture(const std::string& x_pos, const std::string& x_neg, const std::string& y_pos, const std::string& y_neg, const std::string& z_pos, const std::string& z_neg) const override;

	std::shared_ptr<Texture> CreateStaticTexture(unsigned int width, unsigned int height) const override;
	Texture* CreateDynamicTexture(unsigned int width, unsigned int height) const override;

	std::shared_ptr<Texture> WhiteTexture() const override;

	std::shared_ptr<Material> CreateStaticMaterial(unsigned int programID) const override;
	Material* CreateDynamicMaterial(unsigned int programID) const override;

	std::shared_ptr<Mesh> CreateStaticMesh(const std::string& name) const override;
	Mesh* CreateDynamicMesh(const std::string& name) const override;

	std::shared_ptr<Shader> CreateShader(const std::string& name, Shader::SHADER_TYPE type) const override;
	std::shared_ptr<Program> CreateProgram(std::vector<std::shared_ptr<Shader>>& shaders, const std::string& name) const override;
	std::shared_ptr<Program> CreateFeedbackProgram(std::vector<std::shared_ptr<Shader>>& shaders, const char* varyings[], unsigned int varyingCount, const std::string& name) const override;
};