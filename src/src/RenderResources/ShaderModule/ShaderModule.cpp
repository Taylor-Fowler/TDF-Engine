#include "ShaderModule.h"
#include "..\..\Engine\Components\Camera\Camera.h"
#include "..\ShaderParameter\ShaderParamList.h"
#include "..\Factory\RenderResourceFactory.h"

#include <algorithm>
#include "GL\glew.h"
#include "glm\gtc\type_ptr.hpp"
#include <iostream>

RenderResourceFactory* ShaderModule::_renderResourceFactory = nullptr;

ShaderModule::ShaderModule(std::shared_ptr<Program> program)
{
	m_mainProgram = program;
}

void ShaderModule::Render(RenderDetails renderDetails)
{
	m_mainProgram->Use();
	m_mainProgram->SendParam("texture0", 0);
	m_mainProgram->SendParam("viewMatrix", glm::value_ptr(renderDetails.viewMatrix));
	m_mainProgram->SendParam("projectionMatrix", glm::value_ptr(renderDetails.projectionMatrix));

	

	for (auto& sub : m_paramSubscribers)
	{
		glActiveTexture(GL_TEXTURE0);

		auto texture = sub->GetTexture("texture0");
		if (texture == nullptr)
			texture = _renderResourceFactory->WhiteTexture();

		texture->Bind();
		sub->Render(m_mainProgram, renderDetails);
		texture->Unbind();
	}

	for (auto sub : m_renderSubscribers)
		sub->Render(m_mainProgram, renderDetails);
}

void ShaderModule::Unsubscribe(ShaderParamList* params)
{
	if (m_paramSubscribers.size() != 0)
	{
		auto location = std::find(m_paramSubscribers.begin(), m_paramSubscribers.end(), params);
		if (location != m_paramSubscribers.end())
			m_paramSubscribers.erase(location);
	}
}

void ShaderModule::Unsubscribe(IRender* renderable)
{
	if (m_renderSubscribers.size() != 0)
	{
		auto location = std::find(m_renderSubscribers.begin(), m_renderSubscribers.end(), renderable);
		if (location != m_renderSubscribers.end())
			m_renderSubscribers.erase(location);
	}
}
