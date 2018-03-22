#include "SDL.h"
#include "IO\Loader3D.h"
#include "IO\SDL_ReadWrite.h"
#include "RenderResources\Factory\GL_ResourceFactory.h"
#include "Engine\RenderLoop.h"
#include "RenderResources\ResourceManager.h"
#include "Engine\Window\SDL_MyWindow.h"

int main(int argc, char *argv[])
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_ReadWrite readWrite;
	RenderLoop renderLoop;
	ResourceManager resourceManager;
	Loader3D loader;

	SDL_MyWindow window()

	GL_ResourceFactory resourceFactory(&renderLoop, &readWrite, &resourceManager, &loader);
	std::shared_ptr<Mesh> mesh = resourceFactory.CreateStaticMesh("Assets/Models/Table.obj");


	//SDL_Window* window = SDL_CreateWindow("Testing SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Delay(3000);
	

	SDL_Quit();
	return 0;
}