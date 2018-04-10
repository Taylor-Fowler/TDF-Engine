#include "GL\glew.h"
#include "SDL.h"

#include "IO\Loader3D.h"
#include "IO\SDL_ReadWrite.h"
#include "IO\ImageLoader.h"

#include "Engine\Window\SDL_MyWindow.h"
#include "Engine\EventSystem\SDL_EventSystem.h"
#include "Engine\RenderLoop.h"
#include "Engine\Components\Component.h"

#include "RenderResources\ResourceManager.h"
#include "RenderResources\Factory\GL_ResourceFactory.h"
#include "RenderResources\ShaderModule\ShaderModule.h"
#include "RenderResources\ShaderModule\ReflectionCubeModule.h"
#include "RenderResources\Program\Program.h"
#include "RenderResources\Shader\Shader.h"
#include "Utilities\Time.h"

#include "Engine\CustomScenes\HeroScene.h"


#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"


SDL_EventSystem eventSystem;
SDL_ReadWrite readWrite;

RenderLoop renderLoop;
ResourceManager resourceManager;
Loader3D loader3D;
ImageLoader iLoader;

SDL_MyWindow *mainWindow;
GL_ResourceFactory *resourceFactory;


bool Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// OpenGL 4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// Buffering and Depth size
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	mainWindow = new SDL_MyWindow(eventSystem);
	glEnable(GL_DEPTH_TEST);

	if (GLenum e = glewInit() != GLEW_OK)
	{
		std::cout << glewGetErrorString(e) << std::endl;
		return false;
	}
	resourceFactory = new GL_ResourceFactory(&renderLoop, &readWrite, &resourceManager, &loader3D, &iLoader);

	AppTime::Initialise();

	return true;
}


int main(int argc, char *argv[])
{
	SDL_SetMainReady();
	if (!Init())
	{
		return 1;
	}
	Component::_eventSystem = &eventSystem;
	Component::_renderResourceFactory = resourceFactory;
	Component::_renderLoop = &renderLoop;

	// Create the default rendering program and add it to the render loop
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		shaders.push_back(resourceFactory->CreateShader("Assets/GLSL Source/Default.vert", Shader::SHADER_TYPE::VERTEX));
		shaders.push_back(resourceFactory->CreateShader("Assets/GLSL Source/Default.frag", Shader::SHADER_TYPE::FRAGMENT));

		auto program = resourceFactory->CreateProgram(shaders, "Default");
		program->Use();
		glm::mat4 projectionMatrix = glm::perspective(1.0472f, 800.0f * 1.0f / 600.0f, 0.02f, 1000.0f);
		program->SendParam("projectionMatrix", glm::value_ptr(projectionMatrix));
		program->SendParam("ambientLight", 1.0f, 1.0f, 1.0f);

		renderLoop.m_defaultProgram = program;
		renderLoop.m_defaultModule = std::make_shared<ShaderModule>(program);
		renderLoop.AddModule(renderLoop.m_defaultModule, 10, "Default");

		//renderLoop.AddModule(std::make_shared<ReflectionCubeModule>(program), 1, "ReflectionCube");
	}
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		shaders.push_back(resourceFactory->CreateShader("Assets/GLSL Source/BasicTerrain.vert", Shader::SHADER_TYPE::VERTEX));
		shaders.push_back(resourceFactory->CreateShader("Assets/GLSL Source/BasicTerrain.frag", Shader::SHADER_TYPE::FRAGMENT));

		auto program = resourceFactory->CreateProgram(shaders, "Terrain");
		program->Use();
		glm::mat4 projectionMatrix = glm::perspective(1.0472f, 800.0f * 1.0f / 600.0f, 0.02f, 1000.0f);
		program->SendParam("projectionMatrix", glm::value_ptr(projectionMatrix));
		program->SendParam("ambientMaterial", 1.0f, 1.0f, 1.0f);

		renderLoop.AddModule(std::make_shared<ShaderModule>(program), 1, "Terrain");
	}


	HeroScene scene(*resourceFactory, renderLoop);


	while (!mainWindow->IsClosed())
	{		
		AppTime::UpdateDeltaTime();
		double deltaTime = AppTime::GetDeltaTime();
		renderLoop.RenderFrame();

		for (auto& component : Component::_allComponents)
			component->Update();
		scene.Update();

		mainWindow->SwapBuffer();
		eventSystem.Update(deltaTime);
		
	}
	
	SDL_Quit();
	return 0;
}