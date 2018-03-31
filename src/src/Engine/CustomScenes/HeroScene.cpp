#include "HeroScene.h"

#include "..\RenderLoop.h"
#include "..\..\RenderResources\Factory\RenderResourceFactory.h"

#include "..\GameObject\GameObject.h"
#include "..\Components\Camera\Camera.h"
#include "..\Components\Renderer\Renderer.h"

#include "..\..\CustomComponents\BasicCameraController.h"

HeroScene::HeroScene(RenderResourceFactory& renderResourceFactory, RenderLoop& renderLoop)
{
	GameObject * cameraObject = new GameObject();
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<BasicCameraController>();

	m_objects.push_back(cameraObject);


	GameObject * cube = new GameObject();
	Renderer& cubeRend = cube->AddComponent<Renderer>();
	cubeRend.m_mesh = renderResourceFactory.CreateStaticMesh("Assets/Models/Cube.obj");

	auto mat = std::make_shared<Material>(renderLoop.DefaultShaderModule());
	mat->AddParameter("vColour", std::move(std::make_unique<FloatData3>(0.0f, 1.0f, 0.0f)));
	cubeRend.AddMaterial(mat);

	m_objects.push_back(cube);
}
