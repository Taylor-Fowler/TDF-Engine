#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>

#include "WorldGeneration.h"
#include "..\Random\PerlinNoise.h"
//#include <math.h>


const BIOME_SETTING WorldGeneration::BIOMES[6] = {
	BIOME_SETTING(BIOME::MOUNTAIN, 1.0f, 0.8f, 1.0f, 0.5f, 2, 0.75f),
	BIOME_SETTING(BIOME::HILL, 1.0f, 0.8f, 0.5f, 0.0f, 2, 0.75f),

	BIOME_SETTING(BIOME::GRASSLAND, 0.8f, 0.2f, 1.0f, 0.5f, 6, 0.001f),
	BIOME_SETTING(BIOME::BASALT, 0.8f, 0.2f, 0.5f, 0.0f, 6, 0.001f),

	BIOME_SETTING(BIOME::BEACH, 0.2f, 0.0f, 1.0f, 0.8f, 4, 0.9f),
	BIOME_SETTING(BIOME::SEA, 0.2f, 0.0f, 0.8f, 0.0f, 2, 0.5f)
};


WorldGeneration::WorldGeneration(int gridWidth, int gridHeight, int chunkWidth, int chunkHeight, double seed)
	: gridWidth(gridWidth), gridHeight(gridHeight), chunkWidth(chunkWidth), chunkHeight(chunkHeight)
{
	// If a seed is given, seed the RNG with seed and assign the given seed.
	if (seed != 0)
		m_seed = seed;
	// No seed given results in a seed being randomly generated by the RNG (seeded by the system time)
	else {
		srand(time(NULL));
		m_seed = rand() + (double)rand() / UINT16_MAX;
	}
	// Seed the RNG with the newly assigned/generated seed
	srand(m_seed);

	// A secondary seed is required to add another dimension to the randomness
	m_secondarySeed = rand() + (double)rand() / UINT16_MAX;

	amplifierX = rand() +(double)rand() / UINT16_MAX;
	amplifierZ = rand() +(double)rand() / UINT16_MAX;
	// The number of chunks that lie on each axis in the grid
	chunksInGridX = gridWidth / chunkWidth;
	chunksInGridZ = gridHeight / chunkHeight;
}


//void WorldGeneration::GenerateVertices(vector<float>& vertices, float minHeight, float maxHeight, float positionX, float positionZ)
//{
//	float rndrange = abs(maxHeight - minHeight);
//	float midHeight = minHeight + (rndrange * 0.5f);
//
//	float cw = 1.0f / chunkWidth;
//	float ch = 1.0f / chunkHeight;
//
//	vector<BIOME> biomes;
//	GenerateBiomes(biomes, positionX, positionZ);
//
//	float startingX = positionX - gridWidth * 0.5f;
//	float startingZ = positionZ - gridHeight * 0.5f;
//
//	int startingChunkX = int(startingX) * cw;
//	int startingChunkZ = int(startingZ) * ch;
//
//	// TEMP
//	startingChunkX = startingChunkZ = 0;
//
//	for (int x = 0; x < gridWidth; x++)
//	{
//		int chunkX = startingChunkX + x * cw;
//		for (int z = 0; z < gridHeight; z++)
//		{
//			int chunkZ = startingChunkZ + z * ch;
//			BIOME_SETTING bs = BIOMES[int(biomes[chunkZ + chunkX * chunksInGridZ])];
//
//			float oNoise = perlin.OctaveNoise(
//				(positionX + (float)x + amplifierX) * cw, 
//				seed, 
//				(positionZ + (float)z + amplifierZ) * ch,
//				bs.Octaves,
//				bs.Persistance
//			);
//
//			float y = oNoise * rndrange + minHeight;
//
//			vertices.push_back(positionX + (float)x * 2 - gridWidth / 2);
//			vertices.push_back(y);
//			vertices.push_back(positionZ + (float)z * 2 - gridHeight / 2);
//		}
//	}
//}
void WorldGeneration::GenerateVertices(std::vector<float>& vertices, float minHeight, float maxHeight, float positionX, float positionZ)
{
	vertices.clear();
	float rndrange = abs(maxHeight - minHeight);
	float midHeight = minHeight + (rndrange * 0.5f);

	float cw = 1.0f / chunkWidth;
	float ch = 1.0f / chunkHeight;


	int posX = (int)positionX - gridWidth * 2;
	int posZ = (int)positionZ - gridHeight * 2;

	posX -= posX % 4;
	posZ -= posZ % 4;

	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{

			float oNoise = perlin.OctaveNoise3D(
				(posX + (float)x * 4.0f + m_secondarySeed) * cw * 0.233f,
				(posZ + (float)z * 4.0f + m_secondarySeed) * ch * 0.233f,
				m_seed,
				4,
				0.01f
			);

			float y = oNoise * rndrange + minHeight;

			vertices.push_back(posX + (float)x * 4.0f);
			vertices.push_back(y);
			vertices.push_back(posZ + (float)z * 4.0f);
		}
	}
}


void WorldGeneration::GenerateNormals(std::vector<float>& normals, const std::vector<float>& vertices)
{
	normals.clear();

	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{
			// If x is 0, leave it alone, otherwise we care about the previous X 
			int x0 = (x == 0) ? x : x - 1;
			// If x is the last x position, leave it alone, otherwise use the next X position
			int x1 = (x == gridWidth - 1) ? x : x + 1;
			// Same as previously but with z
			int z0 = (z == 0) ? z : z - 1;
			int z1 = (z == gridHeight - 1) ? z : z + 1;


			float dx = vertices[(x1 * gridHeight + z) * 3 + 1] - vertices[(x0 * gridHeight + z) * 3 + 1];
			float dz = vertices[(x * gridHeight + z1) * 3 + 1] - vertices[(x * gridHeight + z0) * 3 + 1];

			float magnitude = sqrt(dx * dx + 4 + dz * dz);
			normals.push_back(-dx / magnitude);
			normals.push_back(2 / magnitude);
			normals.push_back(-dz / magnitude);
		}
	}
}

void WorldGeneration::GenerateNormalLines(std::vector<float>& normalLines, const std::vector<float>& normals, const std::vector<float>& vertices, float length)
{
	normalLines.clear();

	for (int i = 0; i < vertices.size() / 3; i++)
	{
		normalLines.push_back(vertices[i * 3]);
		normalLines.push_back(vertices[i * 3 + 1]);
		normalLines.push_back(vertices[i * 3 + 2]);

		normalLines.push_back(vertices[i * 3] + length * normals[i * 3]);
		normalLines.push_back(vertices[i * 3 + 1] + length * normals[i * 3 + 1]);
		normalLines.push_back(vertices[i * 3 + 2] + length * normals[i * 3 + 2]);
	}
}

void WorldGeneration::GenerateUV(std::vector<float>& uv)
{
	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{
			//uv.push_back((float)(gridHeight - z) / gridHeight);
			//uv.push_back((float)(gridWidth - x) / gridWidth);
			uv.push_back((float)z / gridHeight);
			uv.push_back((float)x / gridWidth);
		}
	}
}


void WorldGeneration::GenerateIndices(std::vector<int>& indices)
{
	// Check that the WorldGeneration has been initialised
	if (gridHeight < 2 || gridWidth < 2) return;

	for (int x = 0; x < gridWidth - 1; x++)
	{
		for (int z = 0; z < gridHeight - 1; z++)
		{
			// Bottom left corner
			indices.push_back(x * gridHeight + z);
			// Top left corner
			indices.push_back(x * gridHeight + z + 1);
			// Bottom right corner
			indices.push_back((x + 1) * gridHeight + z);


			// Top left corner
			indices.push_back(x * gridHeight + z + 1);
			// Top right corner
			indices.push_back((x + 1) * gridHeight + z + 1);
			// Bottom right corner
			indices.push_back((x + 1) * gridHeight + z);
		}
	}
}

// Did not work how I want so isnt used in the Outdoor Scene
void WorldGeneration::GenerateBiomes(std::vector<BIOME>& biomes, float positionX, float positionZ)
{
	biomes.clear();

	// Every 4 chunks there point lies in a different unit square
	float chunkIncrement = 0.25f;

	int posX = (int)positionX;
	int posZ = (int)positionZ;

	// We need to find the starting x and z chunks
	// First we find the starting x and z position which is equal to:
	// realX = xPos - half the gridW
	// realZ = zPos - half the gridH
	// Then we find the actual chunk the position lies in by dividing each axis by the chunk size for that axis
	// Finally add the amplifier to each axis for some randomness of the unit cube
	float startingChunkX = (posX - gridWidth / 2) / chunkWidth + amplifierX;
	float startingChunkZ = (posZ - gridHeight / 2) / chunkHeight + amplifierZ;

	//int chunkLoopsX = 4, chunkLoopsZ = 4;

	//if(positionX != posX)

	for (int x = 0; x < chunksInGridX + 1; x++)
	{
		float chunkPositionX = startingChunkX + (x * chunkIncrement);
		for (int z = 0; z < chunksInGridZ + 1; z++)
		{
			float chunkPositionZ = startingChunkZ + (z * chunkIncrement);
			float height = perlin.GetNoise2D(chunkPositionX + amplifierX, chunkPositionZ + amplifierZ);
			float moisture = perlin.GetNoise2D(chunkPositionX + amplifierX, chunkPositionZ + amplifierZ);

			for (int i = 0; i < (int)BIOME::SEA + 1; i++)
			{
				if (height >= BIOMES[i].HeightMin && height < BIOMES[i].HeightMax &&
					moisture >= BIOMES[i].MoistureMin && moisture < BIOMES[i].MoistureMax)
				{
					biomes.push_back(static_cast<BIOME>(i));
					break;
				}
			}
		}

	}

}

int WorldGeneration::GetIndicesCount(int w, int h)
{
	return (w - 1) * (h - 1) * 6;
}

std::vector<float> WorldGeneration::GenerateVertices(float minHeight, float maxHeight, float positionX, float positionZ)
{
	std::vector<float> vertices;

	float rndrange = abs(maxHeight - minHeight);
	float midHeight = minHeight + (rndrange * 0.5f);

	float cw = 1.0f / chunkWidth;
	float ch = 1.0f / chunkHeight;


	int posX = (int)positionX - gridWidth * 2;
	int posZ = (int)positionZ - gridHeight * 2;

	posX -= std::fmod(posX, m_distanceBetweenVertices);
	posZ -= std::fmod(posZ, m_distanceBetweenVertices);

	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{

			float oNoise = perlin.OctaveNoise3D(
				(posX + (float)x * m_distanceBetweenVertices + m_secondarySeed) * cw * 0.233f,
				(posZ + (float)z * m_distanceBetweenVertices + m_secondarySeed) * ch * 0.233f,
				m_seed,
				4,
				0.01f
			);

			float y = oNoise * rndrange + minHeight;

			vertices.push_back(posX + (float)x * m_distanceBetweenVertices);
			vertices.push_back(y);
			vertices.push_back(posZ + (float)z * m_distanceBetweenVertices);
		}
	}

	return vertices;
}

std::vector<float> WorldGeneration::GenerateNormals(std::vector<float> vertices)
{
	std::vector<float> normals;

	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{
			// If x is 0, leave it alone, otherwise we care about the previous X 
			int x0 = (x == 0) ? x : x - 1;
			// If x is the last x position, leave it alone, otherwise use the next X position
			int x1 = (x == gridWidth - 1) ? x : x + 1;
			// Same as previously but with z
			int z0 = (z == 0) ? z : z - 1;
			int z1 = (z == gridHeight - 1) ? z : z + 1;


			float dx = vertices[(x1 * gridHeight + z) * 3 + 1] - vertices[(x0 * gridHeight + z) * 3 + 1];
			float dz = vertices[(x * gridHeight + z1) * 3 + 1] - vertices[(x * gridHeight + z0) * 3 + 1];

			float magnitude = sqrt(dx * dx + 4 + dz * dz);
			normals.push_back(-dx / magnitude);
			normals.push_back(2 / magnitude);
			normals.push_back(-dz / magnitude);
		}
	}

	return normals;
}

std::vector<float> WorldGeneration::GenerateTextureCoordinates()
{
	std::vector<float> textureCoordinates;

	for (int x = 0; x < gridWidth; x++)
	{
		for (int z = 0; z < gridHeight; z++)
		{
			//uv.push_back((float)(gridHeight - z) / gridHeight);
			//uv.push_back((float)(gridWidth - x) / gridWidth);
			textureCoordinates.push_back((float)z / gridHeight);
			textureCoordinates.push_back((float)x / gridWidth);
		}
	}

	return textureCoordinates;
}

std::vector<unsigned int> WorldGeneration::GenerateIndices()
{
	std::vector<unsigned int> indices;

	if (gridHeight < 2 || gridWidth < 2) return indices;

	for (unsigned int x = 0; x < gridWidth - 1; x++)
	{
		for (unsigned int z = 0; z < gridHeight - 1; z++)
		{
			// Bottom left corner
			indices.push_back(x * gridHeight + z);
			// Top left corner
			indices.push_back(x * gridHeight + z + 1);
			// Bottom right corner
			indices.push_back((x + 1) * gridHeight + z);


			// Top left corner
			indices.push_back(x * gridHeight + z + 1);
			// Top right corner
			indices.push_back((x + 1) * gridHeight + z + 1);
			// Bottom right corner
			indices.push_back((x + 1) * gridHeight + z);
		}
	}

	return indices;
}

float WorldGeneration::GetHeight(float x, float z, float minHeight, float maxHeight)
{
	float cw = 1.0f / chunkWidth;
	float ch = 1.0f / chunkHeight;

	float rndrange = abs(maxHeight - minHeight);
	float midHeight = minHeight + (rndrange * 0.5f);

	x -= std::fmod(x, m_distanceBetweenVertices);
	z -= std::fmod(z, m_distanceBetweenVertices);

	float oNoise = perlin.OctaveNoise3D(
		(x + m_secondarySeed) * cw * 0.233f,
		(z + m_secondarySeed) * ch * 0.233f,
		m_seed,
		4,
		0.01f
	);

	float y = oNoise * rndrange + minHeight;

	return y;
}

float WorldGeneration::GetAbsoluteHeight(float x, float z, float minHeight, float maxHeight)
{
	float cw = 1.0f / chunkWidth;
	float ch = 1.0f / chunkHeight;

	float rndrange = abs(maxHeight - minHeight);
	float midHeight = minHeight + (rndrange * 0.5f);

	float oNoise = perlin.OctaveNoise3D(
		(x + m_secondarySeed) * cw * 0.233f,
		(z + m_secondarySeed) * ch * 0.233f,
		m_seed,
		4,
		0.01f
	);

	float y = oNoise * rndrange + minHeight;

	return y;
}
