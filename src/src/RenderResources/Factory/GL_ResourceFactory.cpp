#include "GL_ResourceFactory.h"

GL_ResourceFactory::GL_ResourceFactory(RenderLoop * const renderLoop, FileReadWrite * const fileRW, ResourceManager *const resourceManager, Loader3D *const loader3D)
	:
	RenderResourceFactory(renderLoop, fileRW, resourceManager, loader3D)
{
}

std::shared_ptr<Texture> GL_ResourceFactory::CreateStaticTexture(const std::string & name) const
{
	return std::shared_ptr<Texture>();
}

Texture * GL_ResourceFactory::CreateDynamicTexture(const std::string & name) const
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

	if (!m_fileRW->FileExists(name))
		return m_loader3D->LoadGL_3D_Model(name);


	return std::shared_ptr<Mesh>();
}

Mesh * GL_ResourceFactory::CreateDynamicMesh(const std::string & name) const
{
	return nullptr;
}
