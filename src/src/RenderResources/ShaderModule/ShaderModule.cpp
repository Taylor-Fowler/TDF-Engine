#include <algorithm>

#include "ShaderModule.h"
#include "..\..\Engine\Components\Camera\Camera.h"
#include "..\ShaderParameter\ShaderParamList.h"

ShaderModule::ShaderModule(std::shared_ptr<Program> program)
{
	m_mainProgram = program;
}

void ShaderModule::Render(Camera * const camera)
{
	camera->Render(m_mainProgram);
	for (auto& sub : m_moduleSubscribers)
	{
		sub->Render(m_mainProgram);
	}
}

void ShaderModule::Unsubscribe(std::shared_ptr<ShaderParamList> params)
{
	auto location = std::find(m_moduleSubscribers.begin(), m_moduleSubscribers.end(), params);
	if (location != m_moduleSubscribers.end())
		m_moduleSubscribers.erase(location);
}
