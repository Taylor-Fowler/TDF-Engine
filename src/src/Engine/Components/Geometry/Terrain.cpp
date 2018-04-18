#include <GL/glew.h>

#include "Terrain.h"
#include "../../../Engine/RenderLoop.h"
#include "../Camera/Camera.h"
#include "../../../RenderResources/Factory/RenderResourceFactory.h"
#include "../../../RenderResources/ShaderModule/ShaderModule.h"
#include "../../../RenderResources/Texture/Texture.h"
#include "../../../Utilities/Random/PerlinNoise.h"


Terrain::Terrain()
{
	_renderLoop->GetModule("Terrain").lock()->Subscribe(this);
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/Gravel.jpg"));
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/Dirt.jpg"));
	m_textures.push_back(_renderResourceFactory->LoadStaticTexture("Assets/Textures/DryGrass.jpg"));

	m_lastGeneratedPosition = Camera::main()->Position();
	m_lastGeneratedPosition.y = 0;
}

Terrain::~Terrain()
{
	_renderLoop->GetModule("Terrain").lock()->Unsubscribe(this);
}

void Terrain::Setup(float minHeight, float maxHeight, int width, int height, int chunkWidth, int chunkHeight, int seed)
{
	//m_minimumHeight = minHeight;
	//m_maximumHeight = maxHeight;

	//if (m_worldGen == nullptr)
	//{
	//	m_worldGen = std::make_shared<WorldGeneration>(width, height, chunkWidth, chunkHeight, seed);
	//}
	//else
	//{
	//	m_worldGen->SetGridWidth(width);
	//	m_worldGen->SetGridHeight(height);
	//	m_worldGen->SetChunkWidth(chunkWidth);
	//	m_worldGen->SetChunkHeight(chunkHeight);
	//	m_worldGen->SetSeed(seed);
	//}
	//setupTerrain();
}

void Terrain::SetWidth(int width)
{
	setupTerrain();
}

void Terrain::SetHeight(int height)
{
	setupTerrain();
}

void Terrain::SetChunkWidth(int width)
{
	setupTerrain();
}

void Terrain::SetChunkHeight(int height)
{
	setupTerrain();
}


float Terrain::GetHeight(float x, float z)
{
	float noiseX = (x + m_seeds[0]) * 0.2137f * (1.0f / m_chunkWidth);
	float noiseZ = (z + m_seeds[0]) * 0.2137f * (1.0f / m_chunkDepth);

	float result = (PerlinNoise::cnoise(glm::vec2(noiseX, noiseZ)) +
		(PerlinNoise::cnoise(glm::vec2(2 * noiseX, 2 * noiseZ)) * 0.5) +
		(PerlinNoise::cnoise(glm::vec2(4 * noiseX, 4 * noiseZ)) * 0.25)) / 1.75f;

	result += 1.0f;
	result /= 2.0f;
	result = powf(result, 3.74f);

	return m_minimumHeight + (result * (m_maximumHeight - m_minimumHeight));
}

void Terrain::Render(std::shared_ptr<Program>& program, const RenderDetails & renderDetails)
{
	program->SendParam("minimumHeight", m_minimumHeight);
	program->SendParam("heightRange", m_maximumHeight - m_minimumHeight);
	

	program->SendParam("gravel", (int)0);
	glActiveTexture(GL_TEXTURE0);
	m_textures[0]->Bind();

	program->SendParam("dirt", (int)1);
	glActiveTexture(GL_TEXTURE1);
	m_textures[1]->Bind();


	program->SendParam("grass", (int)2);
	glActiveTexture(GL_TEXTURE2);
	m_textures[2]->Bind();

	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, (m_gridWidth - 1) * (m_gridDepth - 1) * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//m_mesh->Render(program, renderDetails);
}

void Terrain::RegenerateVertices()
{
	auto program = _renderLoop->GetProgram("TerrainGeneration").lock();
	program->Use();

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_verticesBuffer[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_verticesBuffer[1]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_textureCoordinateBuffer);

	float x = Camera::main()->Position().x + m_cubeSize * 0.5f;
	x -= fmod(x, m_cubeSize);

	float z = Camera::main()->Position().z + m_cubeSize * 0.5f;
	z -= fmod(z, m_cubeSize);

	program->SendParam("blockSize", m_cubeSize);
	program->SendParam("minimumHeight", m_minimumHeight);
	program->SendParam("heightRange", m_maximumHeight - m_minimumHeight);
	program->SendParam("cameraPosition", x, z);
	program->SendParam("seeds[0]", m_seeds[0]);
	program->SendParam("seeds[1]", m_seeds[1]);
	program->SendParam("chunkWidth", m_chunkWidth);
	program->SendParam("chunkDepth", m_chunkDepth);
	program->SendParam("chunkCubeWidth", float(1.0f / m_chunkWidth));
	program->SendParam("chunkCubeDepth", float(1.0f / m_chunkDepth));

	glDispatchCompute(m_gridWidth / 8, m_gridDepth / 8, 1);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);


	program = _renderLoop->GetProgram("TerrainNormalGeneration").lock();
	program->Use();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_verticesBuffer[1]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_normalBuffer);

	glDispatchCompute(m_gridWidth / 8, m_gridDepth / 8, 1);
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

}

void Terrain::setupTerrain()
{

}

void Terrain::Update()
{
	glm::vec3 pos = Camera::main()->Position();
	if (glm::distance(m_lastGeneratedPosition, glm::vec3(pos.x, 0.0f, pos.z)) > 32.0f)
	{
		RegenerateVertices();
		m_lastGeneratedPosition.x = pos.x;
		m_lastGeneratedPosition.z = pos.z;
	}
}

bool Terrain::Initialise()
{
	m_seeds[0] = rand() + (float)rand() / UINT16_MAX;
	m_seeds[1] = rand() + (float)rand() / UINT16_MAX;

	if (m_gridWidth % 2 != 0)
		m_gridWidth++;
	if (m_gridDepth % 2 != 0)
		m_gridDepth++;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	float x = ((m_gridWidth * 0.5f) - m_gridWidth) * m_cubeSize;
	


	for (int i = 0; i < m_gridWidth; i++)
	{
		float z = ((m_gridDepth * 0.5f) - m_gridDepth) * m_cubeSize;

		for (int j = 0; j < m_gridDepth; j++)
		{
			vertices.push_back(x);
			vertices.push_back(0.0f);
			vertices.push_back(z);
			vertices.push_back(1.0f);

			normals.push_back(0.0f);
			normals.push_back(0.0f);
			normals.push_back(0.0f);
			normals.push_back(0.0f);

			z += m_cubeSize;
		}
		x += m_cubeSize;
	}

	for (int i = 0; i < m_gridWidth - 1; i++)
		for (int j = 0; j < m_gridDepth - 1; j++)
		{
			// Bottom left corner
			indices.push_back(i * m_gridDepth + j);
			// Top left corner
			indices.push_back(i * m_gridDepth + j + 1);
			// Bottom right corner
			indices.push_back((i + 1) * m_gridDepth + j);


			// Top left corner
			indices.push_back(i * m_gridDepth + j + 1);
			// Top right corner
			indices.push_back((i + 1) * m_gridDepth + j + 1);
			// Bottom right corner
			indices.push_back((i + 1) * m_gridDepth + j);
		}

	unsigned int buffers[5];
	glGenBuffers(5, buffers);
	m_verticesBuffer[0] = buffers[0];
	m_verticesBuffer[1] = buffers[1];
	m_normalBuffer = buffers[2];
	m_textureCoordinateBuffer = buffers[3];
	m_indicesBuffer = buffers[4];


	// Vertices buffers
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_verticesBuffer[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_verticesBuffer[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(float), NULL, GL_DYNAMIC_DRAW);

	// Tex Coord buffers
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_textureCoordinateBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * 0.5 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

	// Normal buffer
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_normalBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(float), NULL, GL_DYNAMIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, m_indicesBuffer);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_COPY);

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_verticesBuffer[1]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordinateBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
	glBindVertexArray(0);

	RegenerateVertices();
	

	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_verticesBuffer[1]);
	//float* vert = new float[256 * 256 * 4];
	//glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, m_gridDepth * m_gridWidth * 4 * sizeof(float), vert);

	return true;
}
