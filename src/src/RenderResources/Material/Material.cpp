#include "Material.h"
#include "..\..\Engine\Components\Renderer\Renderer.h"

Material::Material(std::shared_ptr<ShaderModule> module) : ShaderParamList(module)
{
}

void Material::Render(std::shared_ptr<Program>& program) const
{
	ShaderParamList::Render(program);
	m_attachedTo->Render(program);
}
