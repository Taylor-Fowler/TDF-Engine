#pragma once
#include <memory>
#include "../Component.h"
#include "../../../RenderResources/IRender.h"
#include "../../../RenderResources/Mesh/Builder/MeshBuilder.h"

class WorldGeneration;
class Texture;


class Terrain : public Component, public IRender
{
private:

	float m_seeds[2];
	float m_minimumHeight = -64.0f;
	float m_maximumHeight = 64.0f;
	int m_gridWidth = 256;
	int m_gridDepth = 256;
	int m_chunkWidth = 32;
	int m_chunkDepth = 32;
	float m_cubeSize = 8.0f;
	glm::vec3 m_lastGeneratedPosition;

	std::shared_ptr<Texture> m_dirt;
	std::shared_ptr<Texture> m_dirtGrass;
	std::shared_ptr<Texture> m_grassLong;
	std::shared_ptr<Texture> m_rockyDirt;
	std::shared_ptr<Texture> m_dryGrass;

	unsigned int m_verticesBuffer[2];
	unsigned int m_normalBuffer;
	unsigned int m_textureCoordinateBuffer;
	unsigned int m_indicesBuffer;
	unsigned int m_moistureBuffer;
	unsigned int m_vaoID;

public:
	Terrain();
	~Terrain() override;

	void Setup(float minHeight, float maxHeight, int width, int height, int chunkWidth, int chunkHeight, int seed = 0);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetChunkWidth(int width);
	void SetChunkHeight(int height);

	float GetHeight(float x, float z);

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

private:
	void RegenerateVertices();
protected:
	void setupTerrain();

	void Update() override;
	bool Initialise() override;
};