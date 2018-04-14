#pragma once
#include <vector>
#include "..\Random\PerlinNoise.h"


#define UINT16_MAX 65536

enum BIOME { MOUNTAIN, HILL, GRASSLAND, BASALT, BEACH, SEA};

struct BIOME_SETTING
{
	BIOME_SETTING(BIOME b, float hMax, float hMin, float mMax, float mMin, int oct, double per) 
		: Biome(b), HeightMax(hMax), HeightMin(hMin), MoistureMax(mMax), MoistureMin(mMin), Octaves(oct), Persistance(per)
	{};

	BIOME Biome;
	float HeightMax;
	float HeightMin;
	float MoistureMax;
	float MoistureMin;
	int Octaves;
	double Persistance;
};

class WorldGeneration
{
private:
	double m_seed;
	double m_secondarySeed;
	double amplifierX, amplifierZ;
	int gridWidth, gridHeight;
	int chunkWidth, chunkHeight;
	int chunksInGridX, chunksInGridZ;
	float m_distanceBetweenVertices = 4.0f;


	PerlinNoise perlin;
public:
	const static BIOME_SETTING BIOMES[6];

	WorldGeneration(int gridWidth, int gridHeight, int chunkWidth, int chunkHeight, double seed = 0);

	void SetGridWidth(int width)
	{
		gridWidth = width;
	}

	void SetGridHeight(int height)
	{
		gridHeight = height;
	}

	void SetChunkWidth(int width)
	{
		chunkWidth = width;
	}

	void SetChunkHeight(int height)
	{
		chunkHeight = height;
	}
	void SetSeed(double seed)
	{
		this->seed = seed;
	}

	void GenerateVertices(std::vector<float>& vertices, float minHeight, float maxHeight, float positionX = 0.0f, float positionZ = 0.0f);

	

	void GenerateNormals(std::vector<float>& normals, const std::vector<float>& vertices);
	void GenerateNormalLines(std::vector<float>& normalLines, const std::vector<float>& normals, const std::vector<float>& vertices, float length = 1.0f);

	void GenerateUV(std::vector<float>& uv);
	void GenerateIndices(std::vector<int>& indices);

	void GenerateBiomes(std::vector<BIOME>& biomes, float positionX = 0.0f, float positionZ = 0.0f);
	// Add a get biome function based on world position...if biomes are ever implemented successfully
	static int GetIndicesCount(int w, int h);


	std::vector<float> GenerateVertices(float minHeight, float maxHeight, float positionX = 0.0f, float positionZ = 0.0f);


	std::vector<float> GenerateNormals(std::vector<float> vertices);

	std::vector<float> GenerateTextureCoordinates();
	std::vector<unsigned int> GenerateIndices();

	float GetHeight(float x, float z, float minHeight, float maxHeight);
	float GetAbsoluteHeight(float x, float z, float minHeight, float maxHeight);
};