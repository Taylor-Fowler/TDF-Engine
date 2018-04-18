#include "RenderLoop.h"
#include "Window\Window.h"
#include "Components\Camera\Camera.h"
#include "Components\Renderer\Renderer.h"
#include "..\RenderResources\ShaderModule\ShaderModule.h"
#include "..\Utilities\Math\MathHelpers.h"

#include "GL\glew.h"
#include "glm\gtc\matrix_transform.hpp"

void RenderLoop::RenderFrame()
{
	Window* window = Window::active();
	float aspectRatio = 1.333333f;

	if (window != nullptr && window->Height() != 0)
	{
		aspectRatio = (float)window->Width() * 1.0f / (float)window->Height();
	}

	for (auto& camera : Camera::AllCameras())
	{
		auto clearColour = camera->m_clearColour;
		glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		for (auto& modPos : m_modulePositions)
		{
			m_modules[modPos.second]->Render(
			{
				camera,
				camera->ViewMatrix(),
				glm::mat4(1),
				glm::perspective(camera->m_fovDegrees * DEG2RAD, aspectRatio, camera->m_nearPlane, camera->m_farPlane)
			});
		}
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

void RenderLoop::AddModule(std::shared_ptr<ShaderModule> shaderModule, unsigned int position, const std::string& name)
{
	// For now, no error checking, assume the user enters modules in correct layout
	if (shaderModule != nullptr)
	{
		m_modules[name] = shaderModule;
		m_modulePositions[position] = name;
	}
}

std::weak_ptr<ShaderModule> RenderLoop::GetModule(const std::string& programName) const
{
	auto shaderModule = m_modules.find(programName);
	if (shaderModule != m_modules.end())
	{
		return std::weak_ptr<ShaderModule>(shaderModule->second);
	}
	return std::weak_ptr<ShaderModule>();
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

void RenderLoop::initialise()
{
	//GLuint ubo = 0;
	//glGenBuffers(1, &m_ubo);
	//glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(m_lights), &m_lights, GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);


	//glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	//GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	//memcpy(p, &m_lights, sizeof(m_lights));
	//glUnmapBuffer(GL_UNIFORM_BUFFER);
}
