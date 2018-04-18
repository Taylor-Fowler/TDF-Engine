#include "SkyboxModule.h"
#include "..\Program\Program.h"
#include "..\ShaderParameter\ShaderParamList.h"
#include "..\..\Engine\Components\Camera\Camera.h"
#include "..\Factory\RenderResourceFactory.h"
#include "..\Mesh\Mesh.h"

#include "GL\glew.h"
#include "glm\gtc\type_ptr.hpp"

SkyboxModule::SkyboxModule(std::shared_ptr<Program> program)
	: ShaderModule(program)
{
	m_skyboxMesh = _renderResourceFactory->CreateStaticMesh("Assets/Models/Cube.obj");
}

void SkyboxModule::Render(RenderDetails renderDetails)
{
	// If camera has skybox, render it
	if (renderDetails.renderingCamera == nullptr)
		return;

	auto skybox = renderDetails.renderingCamera->Skybox().lock();
	if (skybox == nullptr)
		return;

	// Credit to Jarek Francik for the depth mask implementation
	GLboolean depthMask;
	::glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
	glDepthMask(GL_FALSE);
	renderDetails.viewMatrix[3].x = 0;
	renderDetails.viewMatrix[3].y = 0;
	renderDetails.viewMatrix[3].z = 0;

	m_mainProgram->Use();
	m_mainProgram->SendParam("skyboxMap", 0);
	m_mainProgram->SendParam("viewMatrix", glm::value_ptr(renderDetails.viewMatrix));
	m_mainProgram->SendParam("projectionMatrix", glm::value_ptr(renderDetails.projectionMatrix));

	

	glActiveTexture(GL_TEXTURE0);
	skybox->Bind();
	m_skyboxMesh->Render(m_mainProgram, renderDetails);
	skybox->Unbind();
	
	glDepthMask(depthMask);
}

