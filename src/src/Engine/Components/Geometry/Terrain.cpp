#include <GL/glew.h>

#include "Terrain.h"
#include "../../../Engine/RenderLoop.h"
#include "../../../RenderResources/Factory/RenderResourceFactory.h"
#include "../../../RenderResources/ShaderModule/ShaderModule.h"
#include "../../../RenderResources/Texture/Texture.h"
#include "../../../Utilities/ProceduralContent/WorldGeneration.h"


Terrain::Terrain()
{
	_renderLoop->GetModule("Terrain").lock()->Subscribe(this);
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/Gravel.jpg"));
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/Dirt.jpg"));
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/Grass.png"));
}

Terrain::~Terrain()
{
	_renderLoop->GetModule("Terrain").lock()->Unsubscribe(this);
}

void Terrain::Setup(float minHeight, float maxHeight, int width, int height, int chunkWidth, int chunkHeight, int seed)
{
	m_minimumHeight = minHeight;
	m_maximumHeight = maxHeight;

	if (m_worldGen == nullptr)
	{
		m_worldGen = std::make_shared<WorldGeneration>(width, height, chunkWidth, chunkHeight, seed);
	}
	else
	{
		m_worldGen->SetGridWidth(width);
		m_worldGen->SetGridHeight(height);
		m_worldGen->SetChunkWidth(chunkWidth);
		m_worldGen->SetChunkHeight(chunkHeight);
		m_worldGen->SetSeed(seed);
	}
	setupTerrain();
}

void Terrain::SetWidth(int width)
{
	m_worldGen->SetGridWidth(width);
	setupTerrain();
}

void Terrain::SetHeight(int height)
{
	m_worldGen->SetGridHeight(height);
	setupTerrain();
}

void Terrain::SetChunkWidth(int width)
{
	m_worldGen->SetChunkWidth(width);
	setupTerrain();
}

void Terrain::SetChunkHeight(int height)
{
	m_worldGen->SetChunkHeight(height);
	setupTerrain();
}

float Terrain::GetHeight(float x, float z)
{
	if (m_worldGen != nullptr)
		return m_worldGen->GetHeight(x, z, m_minimumHeight, m_maximumHeight);

	return 0.0f;
}

float Terrain::GetAbsoluteHeight(float x, float z)
{
	if (m_worldGen != nullptr)
		return m_worldGen->GetAbsoluteHeight(x, z, m_minimumHeight, m_maximumHeight);

	return 0.0f;
}

void Terrain::Render(std::shared_ptr<Program>& program, const RenderDetails & renderDetails)
{
	program->SendParam("minimumHeight", m_minimumHeight);
	program->SendParam("heightRange", m_maximumHeight - m_minimumHeight);

	program->SendParam("gravel", (int)0);
	glActiveTexture(GL_TEXTURE0);
	m_textures[0]->Bind();
	//glBindTexture(GL_TEXTURE_2D, 1);
	//program->SendParam("allTextures[0]", 0);

	program->SendParam("dirt", (int)1);
	glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, 1);
	m_textures[1]->Bind();
	//program->SendParam("allTextures[1]", 1);

	program->SendParam("grass", (int)2);
	glActiveTexture(GL_TEXTURE2);
	m_textures[2]->Bind();
	//glBindTexture(GL_TEXTURE_2D, 1);
	//program->SendParam("allTextures[2]", 2);


	m_mesh->Render(program, renderDetails);
}

void Terrain::setupTerrain()
{
	MeshBuilder meshBuilder;
	meshBuilder.CreateMeshData("Terrain");
	meshBuilder.CreateMeshNode("Terrain");
	std::vector<float> vert = m_worldGen->GenerateVertices(m_minimumHeight, m_maximumHeight);
	meshBuilder.SetVertices(vert);
	meshBuilder.SetNormals(m_worldGen->GenerateNormals(vert));
	meshBuilder.SetTextureCoordinates(m_worldGen->GenerateTextureCoordinates());
	meshBuilder.SetIndices(m_worldGen->GenerateIndices());
	meshBuilder.SetTransform(glm::mat4(1.0f));
	meshBuilder.AttachMeshData();
	meshBuilder.AddMeshNode();

	m_mesh = meshBuilder.GetMesh();
}
