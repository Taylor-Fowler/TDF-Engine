#include "GL\glew.h"
#include "SDL.h"
#include "IO\Loader3D.h"
#include "IO\SDL_ReadWrite.h"
#include "IO\ImageLoader.h"
#include "RenderResources\ResourceManager.h"
#include "RenderResources\Factory\GL_ResourceFactory.h"
#include "RenderResources\ShaderParameter\ShaderParamList.h"
#include "Engine\RenderLoop.h"
#include "Engine\Components\Camera\Camera.h"
#include "Engine\Window\SDL_MyWindow.h"
#include "Engine\EventSystem\SDL_EventSystem.h"
#include "Utilities\Time.h"
#include "RenderResources\Shader\Shader.h"
#include "RenderResources\Program\Program.h"


#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"


SDL_EventSystem eventSystem;
SDL_ReadWrite readWrite;

RenderLoop renderLoop;
ResourceManager resourceManager;
Loader3D loader3D;
ImageLoader iLoader;
Camera mainCam;

SDL_MyWindow *mainWindow;

float vertices[] = {
	0.0f,  0.5f, -1.0f, // Vertex 1 (X, Y)
	0.5f, -0.5f, -1.0f, // Vertex 2 (X, Y)
	-0.5f, -0.5f, -1.0f  // Vertex 3 (X, Y)
};

unsigned int vaoid = 0;



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

	if (GLenum e = glewInit() != GLEW_OK)
	{
		std::cout << glewGetErrorString(e) << std::endl;
		return false;
	}
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

	GL_ResourceFactory resourceFactory(&renderLoop, &readWrite, &resourceManager, &loader3D, &iLoader);
	std::shared_ptr<Mesh> mesh = resourceFactory.CreateStaticMesh("Assets/Models/Table.obj");
	std::shared_ptr<Texture> texture = resourceFactory.LoadStaticTexture("Assets/Textures/Table.jpg");

	std::shared_ptr<Mesh> mesh2 = resourceFactory.CreateStaticMesh("Assets/Models/Cube.obj");

	std::vector<std::shared_ptr<Shader>> shaders;
	shaders.push_back(resourceFactory.CreateShader("Assets/GLSL Source/Default.vert", Shader::SHADER_TYPE::VERTEX));
	shaders.push_back(resourceFactory.CreateShader("Assets/GLSL Source/Default.frag", Shader::SHADER_TYPE::FRAGMENT));
	
	auto program = resourceFactory.CreateProgram(shaders);
	program->Use();

	ShaderParamList spl;
	spl.AddParameter("vColour", std::move(std::make_unique<FloatData3>(0.0f, 1.0f, 0.0f)));

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 2.0f, -2.0f), glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 projectionMatrix = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);
	program->SendParam("projectionMatrix", glm::value_ptr(projectionMatrix));
	program->SendParam("modelMatrix", glm::value_ptr(glm::mat4(1.0f)));


	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	unsigned int a;
	glGenBuffers(1, &a);
	glBindBuffer(GL_ARRAY_BUFFER, a);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);



	while (!mainWindow->IsClosed())
	{		
		AppTime::UpdateDeltaTime();
		double deltaTime = AppTime::GetDeltaTime();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		spl.Render(program);
		mesh->Render(program);
		mesh2->Render(program);
		mainCam.Render(program);
		mainCam.RotateY(0.01f);
		glm::vec3 translation = viewMatrix[3];

		//viewMatrix = glm::translate(viewMatrix, translation);
		//viewMatrix = glm::rotate(viewMatrix, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		//viewMatrix = glm::translate(viewMatrix, -translation);
		//program->SendParam("viewMatrix", glm::value_ptr(viewMatrix));

		program->SendParam("modelMatrix", glm::value_ptr(glm::mat4(1.0f)));
		glBindVertexArray(vaoid);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		if (GLenum e = glGetError() != GL_NO_ERROR)
		{
			std::cout << e << std::endl;
		}

		mainWindow->SwapBuffer();
		eventSystem.Update(deltaTime);
	}
	
	SDL_Quit();
	return 0;
}