#include "GL\glew.h"

#include "GL_ResourceFactory.h"
#include "..\Texture\GL_Texture.h"
#include "..\Program\GL_Program.h"
#include "..\Shader\GL_Shader.h"

GL_ResourceFactory::GL_ResourceFactory(RenderLoop * const renderLoop, FileReadWrite * const fileRW, ResourceManager *const resourceManager, Loader3D *const loader3D, ImageLoader *const iLoader)
	:
	RenderResourceFactory(renderLoop, fileRW, resourceManager, loader3D, iLoader)
{
}

std::shared_ptr<Texture> GL_ResourceFactory::LoadStaticTexture(const std::string & name) const
{
	std::shared_ptr<Texture> texture = m_resourceManager->FindTexture(name);
	if (texture != nullptr)
		return texture;

	if (!m_imageLoader->Load(name, GL_RGBA))
		return std::shared_ptr<Texture>();

	texture = std::make_shared<GL_Texture>(m_imageLoader->LoadedImageWidth(), m_imageLoader->LoadedImageHeight(), m_imageLoader->LoadedImageBits());
	m_resourceManager->AddTexture(name, texture);

	return texture;
}

Texture * GL_ResourceFactory::LoadDynamicTexture(const std::string & name) const
{
	return nullptr;
}

std::shared_ptr<Texture> GL_ResourceFactory::CreateStaticTexture(unsigned int width, unsigned int height) const
{
	return std::shared_ptr<Texture>();
}

Texture * GL_ResourceFactory::CreateDynamicTexture(unsigned int width, unsigned int height) const
{
	return nullptr;
}





std::shared_ptr<Material> GL_ResourceFactory::CreateStaticMaterial(unsigned int programID) const
{
	return std::shared_ptr<Material>();
}

Material * GL_ResourceFactory::CreateDynamicMaterial(unsigned int programID) const
{
	return nullptr;
}

std::shared_ptr<Mesh> GL_ResourceFactory::CreateStaticMesh(const std::string& name) const
{
	// Look for the mesh in the managed resources
	std::shared_ptr<Mesh> meshPtr = m_resourceManager->FindMesh(name);


	if (meshPtr != nullptr)
		return meshPtr;

	if (m_fileRW->FileExists(name))
		return m_loader3D->LoadGL_3D_Model(name);


	return std::shared_ptr<Mesh>();
}

Mesh * GL_ResourceFactory::CreateDynamicMesh(const std::string & name) const
{
	return nullptr;
}

std::shared_ptr<Shader> GL_ResourceFactory::CreateShader(const std::string & name, Shader::SHADER_TYPE type) const
{
	if (!m_fileRW->FileExists(name))
		return std::shared_ptr<Shader>();

	return std::make_shared<GL_Shader>(m_fileRW->ImportTextFile(name), type);
}

std::shared_ptr<Program> GL_ResourceFactory::CreateProgram(std::vector<std::shared_ptr<Shader>>& shaders) const
{
	if(shaders.size() == 0)
		return std::shared_ptr<Program>();

	auto program = std::make_shared<GL_Program>();
	for (auto &shader : shaders)
	{
		if (!program->AttachShader(shader))
		{
			return std::shared_ptr<Program>();
		}
	}

	program->Link();
	return program;
}
