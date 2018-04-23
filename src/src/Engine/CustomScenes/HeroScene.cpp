#include <cstdlib>
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "HeroScene.h"

#include "..\RenderLoop.h"
#include "..\..\RenderResources\Factory\RenderResourceFactory.h"

#include "..\GameObject\GameObject.h"
#include "..\Components\Camera\Camera.h"
#include "..\Components\Renderer\Renderer.h"
#include "..\Components\Geometry\Terrain.h"
#include "..\Components\Lighting\Light.h"

#include "..\..\CustomComponents\BasicCameraController.h"
#include "..\..\CustomComponents\ShaderSubscribers\Explosion.h"
#include "..\..\CustomComponents\ShaderSubscribers\SphericalDrip.h"
#include "..\..\CustomComponents\ShaderSubscribers\FloatyThing.h"

#include "..\..\RenderResources\ShaderModule\ExplosionModule.h"

DirectionalLight *dirLight;

HeroScene::HeroScene(RenderResourceFactory& renderResourceFactory, RenderLoop& renderLoop)
{
	Light::SetAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	BasicCameraController * bcc;
	Terrain * terr;
	// Main Camera
	{
		GameObject * cameraObject = new GameObject();
		Camera& cam = cameraObject->AddComponent<Camera>();
		
		cam.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		cam.SetSkybox(renderResourceFactory.LoadStaticCubeTexture(
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0001.bmp",
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0004.bmp",
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0003.bmp",
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0003.bmp",
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0005.bmp",
			"Assets/Textures/Skyboxes/skyboxsun5deg/skyrender0002.bmp"
			));

		bcc = &cameraObject->AddComponent<BasicCameraController>();
		m_objects.push_back(std::shared_ptr<GameObject>(cameraObject));

		dirLight = &cameraObject->AddComponent<DirectionalLight>();
		dirLight->SetDiffuse({ 1.0f, 0.1f, 0.1f });
		
	}
	// Terrain
	{
		GameObject *terrain = new GameObject();
		terr = &terrain->AddComponent<Terrain>();
		terr->Setup(-20.0f, 12.0f, 128, 128, 16, 16, 0);
		m_objects.push_back(std::shared_ptr<GameObject>(terrain));

		bcc->SetTerrain(terr);
	}

	// Custom Shaders
	// Explosion Shader
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/Default.vert", Shader::SHADER_TYPE::VERTEX));
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/Explosion.frag", Shader::SHADER_TYPE::FRAGMENT));
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/Explosion.geom", Shader::SHADER_TYPE::GEOMETRY));

		auto program = renderResourceFactory.CreateProgram(shaders, "Explosion");
		program->Use();
		program->BindUniformBlock("lights", Light::GetUniformBufferBindingPoint());

		renderLoop.AddModule(std::make_shared<ExplosionModule>(program), 11, "Explosion");
	}
	// SphericalDrip Shader
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/SphericalDrip.vert", Shader::SHADER_TYPE::VERTEX));
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/ColourOut.frag", Shader::SHADER_TYPE::FRAGMENT));

		const char* varyings[] = { "hit1", "spawned1", "pos1", "velocity1" };
		auto program = renderResourceFactory.CreateFeedbackProgram(shaders, varyings, 4, "SphericalDrip");
		program->Use();

		renderLoop.AddModule(std::make_shared<ShaderModule>(program), 12, "SphericalDrip");
	}
	// Floaty thing shader
	{
		std::vector<std::shared_ptr<Shader>> shaders;
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/FloatyThing.vert", Shader::SHADER_TYPE::VERTEX));
		shaders.push_back(renderResourceFactory.CreateShader("Assets/GLSL Source/ColourOut.frag", Shader::SHADER_TYPE::FRAGMENT));

		const char* varyings[] = { "pos1", "vel1" };
		auto program = renderResourceFactory.CreateFeedbackProgram(shaders, varyings, 2, "FloatyThing");
		program->Use();

		renderLoop.AddModule(std::make_shared<ShaderModule>(program), 13, "FloatyThing");
	}

	// Generate rocks
	{
		std::vector<glm::vec2> positions;
		auto rock = renderResourceFactory.CreateStaticMesh("Assets/Models/Rock.obj");
		auto tex = renderResourceFactory.LoadStaticTexture("Assets/Textures/Rock.png");
		
		for (int i = 0; i < 100; i++)
		{
			glm::vec2 possiblePosition = { 1024 - rand() % 2048, 1024 - rand() % 2048 };
			bool success = true;
			for (auto pos : positions)
			{
				if (glm::distance(possiblePosition, pos) < 15)
				{
					i--;
					success = false;
					break;
				}
			}

			if (success)
			{
				GameObject * obj = new GameObject();
				Renderer& rend = obj->AddComponent<Renderer>();
				rend.m_mesh = rock;

				auto mat = std::make_shared<Material>(renderLoop.DefaultShaderModule());
				mat->AddParameter("ambientMaterial", std::move(std::make_unique<FloatData3>(1.0f, 1.0f, 1.0f)));
				mat->AddParameter("diffuseMaterial", std::move(std::make_unique<FloatData3>(1.0f, 1.0f, 1.0f)));
				mat->AddParameter("texture0", renderResourceFactory.LoadStaticTexture("Assets/Textures/Rock.png"));
				rend.AddMaterial(mat);

				obj->GetTransform()->SetPosition({ possiblePosition.x, terr->GetHeight(possiblePosition.x, possiblePosition.y), possiblePosition.y });
				obj->GetTransform()->SetScale({ 5.0f, 5.0f, 5.0f });
				positions.push_back(possiblePosition);
				m_rocks.push_back(std::shared_ptr<GameObject>(obj));
			}
		}
	}

	// Exploding Rock
	{
		GameObject * cube = new GameObject();
		Renderer& cubeRend = cube->AddComponent<Renderer>();
		cubeRend.m_mesh = renderResourceFactory.CreateStaticMesh("Assets/Models/Rock.obj");
		cube->AddComponent<Explosion>();
		cube->GetTransform()->SetPosition(glm::vec3(-25.0f, terr->GetHeight(-25.0f, -5.0f), -5.0f));
		cube->GetTransform()->SetScale({ 5.0f, 5.0f, 5.0f });
		m_objects.push_back(std::shared_ptr<GameObject>(cube));
	}

	// Test Cube
	{
		GameObject * cube = new GameObject();
		Renderer& rend = cube->AddComponent<Renderer>();
		rend.m_mesh = renderResourceFactory.CreateStaticMesh("Assets/Models/Cube.obj");

		auto mat = std::make_shared<Material>(renderLoop.DefaultShaderModule());
		mat->AddParameter("ambientMaterial", std::move(std::make_unique<FloatData3>(1.0f, 0.1f, 0.1f)));
		mat->AddParameter("texture0", renderResourceFactory.WhiteTexture());
		rend.AddMaterial(mat);

		cube->GetTransform()->SetPosition(glm::vec3(-25.0f, terr->GetHeight(-25.0f, -5.0f) + 10.0f, -5.0f));
		cube->GetTransform()->SetScale({ 5.0f, 5.0f, 5.0f });
		m_objects.push_back(std::shared_ptr<GameObject>(cube));
	}

	{
		GameObject *particleSystem = new GameObject();
		particleSystem->AddComponent<SphericalDrip>();
		m_objects.push_back(std::shared_ptr<GameObject>(particleSystem));
	}

	{
		GameObject *particleSystem = new GameObject();
		particleSystem->AddComponent<FloatyThing>();
		m_objects.push_back(std::shared_ptr<GameObject>(particleSystem));
	}
}

void HeroScene::Update()
{
	glm::vec3 pos = Camera::main()->Position();

	m_rocks.erase(std::remove_if(m_rocks.begin(), m_rocks.end(), 
		[&, pos](std::shared_ptr<GameObject> obj)
		{
		return glm::distance(pos, obj->GetTransform()->Position()) < 10.0f;
		}
		), m_rocks.end());
}

HeroScene::~HeroScene()
{
	m_objects.clear();
}
