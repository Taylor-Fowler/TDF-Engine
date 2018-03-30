#pragma once
#include <string>
#include <memory>


#include "../ResourceManager.h"
#include "../../IO/FileReadWrite.h"
#include "../../IO/Loader3D.h"
#include "../../IO/ImageLoader.h"
// TODO: Move enums to a single header, this is dirty below..., only including shader so that the class knows about the SHADER_TYPE enum
#include "../Shader/Shader.h"

// Forward declarations

// Engine objects
class RenderLoop;
// Resource objects
class Framebuffer;
class Material;
class Mesh;
class Program;
class Shader;
class Texture;




class RenderResourceFactory
{
protected:
	RenderLoop		*const m_renderLoop;
	FileReadWrite	*const m_fileRW;
	ResourceManager *const m_resourceManager;
	Loader3D		*const m_loader3D;
	ImageLoader		*const m_imageLoader;


public:
	RenderResourceFactory(RenderLoop *const renderLoop, FileReadWrite *const fileRW, ResourceManager *const resourceManager, Loader3D *const loader3D, ImageLoader *const iLoader) 
		:	m_renderLoop(renderLoop),
			m_fileRW(fileRW),
			m_resourceManager(resourceManager),
			m_loader3D(loader3D),
			m_imageLoader(iLoader)
	{};

	// Pure abstract
	virtual ~RenderResourceFactory() = 0 {};

	// Creates a static texture from a given file path, a static texture will never change. As long as there is an instance 
	// of the static texture in the scene, the texture will be loaded into memory.
	virtual std::shared_ptr<Texture> LoadStaticTexture(const std::string& name) const = 0;
	// Creates a dynamic texture from a given file path, a dynamic texture can change frequently. The dynamic texture is loaded into memory
	// but as a separate instance to other textures with an identical filepath.
	virtual Texture* LoadDynamicTexture(const std::string& name) const = 0;

	virtual std::shared_ptr<Texture> CreateStaticTexture(unsigned int width, unsigned int height) const = 0;
	virtual Texture* CreateDynamicTexture(unsigned int width, unsigned int height) const = 0;

	// Create a static material that shall be associated with a specified program ID. The program ID identifies the shader program that the materials
	// attributes correspond to. E.G. A material may be created with an associated to program A, now only when program A is rendering will the material
	// send its attributes down the rendering pipeline.
	// A material should be created as static when its attribute values exist among multiple render objects, and when one of those render objects has
	// the corresponding material attribute/s changed, all associated render objects reflect that change.
	virtual std::shared_ptr<Material> CreateStaticMaterial(unsigned int programID) const = 0;

	// Create a dynamic material that shall be associated with a specified program ID. The dynamic material, when changed, will only affect the render object that
	// has ownership of the material.
	virtual Material* CreateDynamicMaterial(unsigned int programID) const = 0;

	// Create a static mesh from a given file path, a static mesh will never change.
	virtual std::shared_ptr<Mesh> CreateStaticMesh(const std::string& name) const = 0;
	// Create a dynamic mesh from a given file path, a dynamic mesh may frequently change.
	virtual Mesh* CreateDynamicMesh(const std::string& name) const = 0;


	virtual std::shared_ptr<Shader> CreateShader(const std::string& name, Shader::SHADER_TYPE type) const = 0;
	virtual std::shared_ptr<Program> CreateProgram(std::vector<std::shared_ptr<Shader>>& shaders) const = 0;
	

};