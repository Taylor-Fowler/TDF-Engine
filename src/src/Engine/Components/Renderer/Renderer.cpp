#include "Renderer.h"
#include "..\..\..\RenderResources\Mesh\Mesh.h"

void Renderer::AddMaterial(std::shared_ptr<Material> material)
{
	m_materials.push_back(material);
	material->m_attachedTo = std::shared_ptr<Renderer>(this);
}

void Renderer::RemoveMaterial(std::shared_ptr<Material> material)
{
	auto location = std::find(m_materials.begin(), m_materials.end(), material);
	if (location != m_materials.end())
		m_materials.erase(location);
}

void Renderer::Render(std::shared_ptr<Program>& program) const
{
	m_mesh->Render(program);
}
