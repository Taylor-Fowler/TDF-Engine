#pragma once
#include <memory>
#include "glm\glm.hpp"
#include "..\Component.h"
#include "..\..\..\RenderResources\IRender.h"
#include "..\..\..\RenderResources\Material\Material.h"


class Mesh;



// A renderer controls how and what data is sent to the rendering pipeline for a given object.
// The renderer consists of a model and a material, these member's properties are sent to the
// rendering pipeline.

class Renderer : public Component, public IRender
{
public:
	std::shared_ptr<Mesh> m_mesh;
protected:
	std::vector<std::shared_ptr<Material>> m_materials;

public:
	~Renderer();
	void AddMaterial(std::shared_ptr<Material> material);
	void RemoveMaterial(std::shared_ptr<Material> material);

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;


//
//public:
//	Renderer();
//	// Create a renderer that is attached to a given object, with a model to render and an optional
//	// material. If a material is not supplied, a defaul material will be used.
//	Renderer(C3dglModel *model, Material *material = nullptr);
//	Renderer(TDF::Mesh *mesh, Material *material = nullptr);
//
//
//	// calls the model render function.
//	void Render(C3dglProgram *program, GameObject *exclude = nullptr);
//
//
//	Material& GetMaterial()
//	{
//		return *m_material;
//	}
//
//	void SetMaterial(Material* mat);
//	void SetMesh(TDF::Mesh *mesh);
//	void SetModel(C3dglModel *model);
//	void SetTerrain(C3dglTerrain *terrain);
//
//private:
//	// Cannot copy the renderer, the renderer shouldnt be attached to the same game object
//	Renderer(const Renderer& rend) {};
//
//	//bool attachToGameObject();
//
//
//
//
};