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
	std::shared_ptr<WorldGeneration> m_worldGen;
	std::shared_ptr<Mesh> m_mesh;

	float m_minimumHeight = -5.0f;
	float m_maximumHeight = 15.0f;
	std::vector<std::shared_ptr<Texture>> m_textures;

public:
	Terrain();
	~Terrain() override;

	void Setup(float minHeight, float maxHeight, int width, int height, int chunkWidth, int chunkHeight, int seed = 0);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetChunkWidth(int width);
	void SetChunkHeight(int height);

	float GetHeight(float x, float z);
	float GetAbsoluteHeight(float x, float z);

	void Render(std::shared_ptr<Program>& program, const RenderDetails &renderDetails) override;

protected:
	void setupTerrain();
};