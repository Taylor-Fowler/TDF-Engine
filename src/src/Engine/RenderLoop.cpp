#include "GL\glew.h"

#include "RenderLoop.h"
#include "Components\Camera\Camera.h"
#include "Components\Renderer\Renderer.h"
#include "..\RenderResources\ShaderModule\ShaderModule.h"

void RenderLoop::RenderFrame()
{
	m_defaultProgram->Use();

	for (auto& camera : Camera::AllCameras())
	{
		auto clearColour = camera->m_clearColour;
		glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		camera->Render(m_defaultProgram);
		m_defaultModule->Render(camera);
	}

}

void RenderLoop::AddProgram(std::shared_ptr<Program> program, const std::string& name)
{
	m_programs[name] = program;
}

std::weak_ptr<Program> RenderLoop::GetProgram(const std::string & programName) const
{
	auto program = m_programs.find(programName);

	if (program != m_programs.end())
	{
		return std::weak_ptr<Program>(program->second);
	}

	return std::weak_ptr<Program>();
}

std::string RenderLoop::NextValidProgramName(const std::string & name) const
{
	std::string append = "";
	int i = 0;

	while (!GetProgram(name + append).expired())
	{
		i++;
		append = " " + i;
	}

	return name + append;
}
