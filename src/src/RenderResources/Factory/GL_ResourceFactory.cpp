#include "GL\glew.h"

#include "GL_ResourceFactory.h"
#include "..\Texture\GL_Texture.h"
#include "..\Texture\GL_CubeTexture.h"
#include "..\Program\GL_Program.h"
#include "..\Shader\GL_Shader.h"

#include "..\..\Engine\RenderLoop.h"

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
	unsigned int width, height;
	void * data;

	if ((data = m_imageLoader->Load(name, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<Texture>();

	texture = std::make_shared<GL_Texture>(width, height, data);
	m_resourceManager->AddTexture(name, texture);

	return texture;
}

Texture * GL_ResourceFactory::LoadDynamicTexture(const std::string & name) const
{
	return nullptr;
}

std::shared_ptr<CubeTexture> GL_ResourceFactory::LoadStaticCubeTexture(const std::string & x_pos, const std::string & x_neg, const std::string & y_pos, const std::string & y_neg, const std::string & z_pos, const std::string & z_neg) const
{
	std::shared_ptr<CubeTexture> texture;

	unsigned int width, height, finalWidth, finalHeight;
	void *data1, *data2, *data3, *data4, *data5, *data6;

	finalWidth = finalHeight = UINT16_MAX;

	// X POS
	if ((data1 = m_imageLoader->Load(x_pos, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;
	// X NEG
	if ((data2 = m_imageLoader->Load(x_neg, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;
	// Y POS
	if ((data3 = m_imageLoader->Load(y_pos, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;
	// Y NEG
	if ((data4 = m_imageLoader->Load(y_neg, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;
	// Z POS
	if ((data5 = m_imageLoader->Load(z_pos, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;
	// Z NEG
	if ((data6 = m_imageLoader->Load(z_neg, GL_RGBA, width, height)) == 0)
		return std::shared_ptr<CubeTexture>();
	finalWidth = (finalWidth > width) ? width : finalWidth;
	finalHeight = (finalHeight > height) ? height : finalHeight;


	texture = std::make_shared<GL_CubeTexture>(finalWidth, finalHeight, data1, data2, data3, data4, data5, data6);


	return texture;
}

std::shared_ptr<Texture> GL_ResourceFactory::CreateStaticTexture(unsigned int width, unsigned int height) const
{
	return std::shared_ptr<Texture>();
}

Texture * GL_ResourceFactory::CreateDynamicTexture(unsigned int width, unsigned int height) const
{
	return nullptr;
}

std::shared_ptr<Texture> GL_ResourceFactory::WhiteTexture() const
{
	std::shared_ptr<Texture> texture = m_resourceManager->FindTexture("White");
	if (texture != nullptr)
		return texture;

	texture = std::make_shared<GL_Texture>();
	m_resourceManager->AddTexture("White", texture);

	return texture;
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

std::shared_ptr<Program> GL_ResourceFactory::CreateProgram(std::vector<std::shared_ptr<Shader>>& shaders, const std::string& name) const
{
	if(shaders.size() == 0)
		return std::shared_ptr<Program>();

	auto program = std::make_shared<GL_Program>();
	for (auto &shader : shaders)
	{
		if (!program->AttachShader(shader))
			return std::shared_ptr<Program>();
	}

	if (program->Link())
	{
		auto validName = m_renderLoop->NextValidProgramName(name);
		m_renderLoop->AddProgram(program, validName);
		return program;
	}
	
	return std::shared_ptr<Program>();
}

std::shared_ptr<Program> GL_ResourceFactory::CreateFeedbackProgram(std::vector<std::shared_ptr<Shader>>& shaders, const char * varyings[], unsigned int varyingCount, const std::string & name) const
{
	if(shaders.size() == 0)
		return std::shared_ptr<Program>();

	auto program = std::make_shared<GL_Program>();
	for (auto &shader : shaders)
	{
		if (!program->AttachShader(shader))
			return std::shared_ptr<Program>();
	}
	glTransformFeedbackVaryings(program->ID(), varyingCount, varyings, GL_SEPARATE_ATTRIBS);

	if (program->Link())
	{
		auto validName = m_renderLoop->NextValidProgramName(name);
		m_renderLoop->AddProgram(program, validName);
		return program;
	}

	return std::shared_ptr<Program>();
}
