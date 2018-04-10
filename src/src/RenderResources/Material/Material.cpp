#include "Material.h"
#include "..\..\Engine\Components\Renderer\Renderer.h"

Material::Material(std::shared_ptr<ShaderModule> module) : ShaderParamList(module)
{
}

void Material::Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) 
{
	ShaderParamList::Render(program, renderDetails);
	m_attachedTo->Render(program, renderDetails);
}
