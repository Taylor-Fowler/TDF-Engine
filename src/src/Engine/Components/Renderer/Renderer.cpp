#include "Renderer.h"
#include "..\..\..\RenderResources\Mesh\Mesh.h"
#include "..\..\GameObject\GameObject.h"
#include "..\Transform\Transform.h"

Renderer::~Renderer()
{
	m_materials.clear();
}

void Renderer::AddMaterial(std::shared_ptr<Material> material)
{
	m_materials.push_back(material);
	material->m_attachedTo = this;
}

void Renderer::RemoveMaterial(std::shared_ptr<Material> material)
{
	auto location = std::find(m_materials.begin(), m_materials.end(), material);
	if (location != m_materials.end())
		m_materials.erase(location);
}

void Renderer::Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails)
{
	m_mesh->Render(program, { renderDetails.viewMatrix, renderDetails.transformMatrix * m_objectAttachedTo->GetTransform()->Matrix() });
}
