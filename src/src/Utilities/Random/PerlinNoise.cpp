#include "PerlinNoise.h"
#include <cmath>

//https://github.com/TheThinMatrix/LowPolyTerrain/blob/master/src/generation/PerlinNoise.java

int PerlinNoise::permutation[] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };



PerlinNoise::PerlinNoise()
{
	for (int i = 0; i < 256; i++) p[256 + i] = p[i] = permutation[i];
}

double PerlinNoise::GetNoise2D(double x, double y)
{
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;

	// Find relative x, y, z of point in cube
	x -= floor(x);
	y -= floor(y);

	// Compute fade curves for each of x, y, z
	double u = fade(x);
	double v = fade(y);

	// X, Y and Z always range from 0 to 255
	// The p array has values ranging from 0 to 255
	// A and B will always result in a value between 0 and 510
	// AA, AB, BA and BB will result in a value between 0 and 510

	// Any two given x, y, z positions that are in the same unit cube, will result in the same hash co-ordinates

	// Hash coordinates of the 4 cube corners
	int A = p[X + p[Y]];
	int AB = p[X + p[Y + 1]];
	int B = p[X + 1 + p[Y]];
	int BB = p[X + 1 + p[Y + 1]];




	double resA = lerp(u, GetGradient(p[A], x, y - 1), GetGradient(p[AB], x, y));
	double resB = lerp(u, GetGradient(p[B], x - 1, y - 1), GetGradient(p[BB], x - 1, y));

	double res = lerp(v, resA, resB);


	return (res + 1.0) * 0.5;
}

double PerlinNoise::GetNoise3D(double x, double y, double z)
{
	// Imagine there is a grid of cubes, 256 cubes wide (x), 256 cubes tall (y), and 256 cubes deep (z)
	// The cube at the origin is located at 0, 0, 0
	// The cube at the farthest point point from the origin is located at 255, 255, 255

	// Given any x, y, z value, we have to find which cube in our grid that point is located in
	// At this point in time
	// Find the unit cube that contains the point
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	int Z = (int)floor(z) & 255;

	// Find relative x, y, z of point in cube
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	// Compute fade curves for each of x, y, z
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);

	// X, Y and Z always range from 0 to 255
	// The p array has values ranging from 0 to 255
	// A and B will always result in a value between 0 and 510
	// AA, AB, BA and BB will result in a value between 0 and 510

	// Any two given x, y, z positions that are in the same unit cube, will result in the same hash co-ordinates

	// Hash coordinates of the 8 cube corners
	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;



	//double 	// Add blended results from 8 corners of cube
	double res = lerp(w, lerp(v, lerp(u, GetGradient(p[AA], x, y, z), GetGradient(p[BA], x - 1, y, z)), 
		lerp(u, GetGradient(p[AB], x, y - 1, z), GetGradient(p[BB], x - 1, y - 1, z))), 
		lerp(v, lerp(u, GetGradient(p[AA + 1], x, y, z - 1), GetGradient(p[BA + 1], x - 1, y, z - 1)), 
			lerp(u, GetGradient(p[AB + 1], x, y - 1, z - 1), GetGradient(p[BB + 1], x - 1, y - 1, z - 1))));

	return (res + 1.0) * 0.5;
}

double PerlinNoise::OctaveNoise2D(double x, double y, int octaves, double persistence)
{
	double total = 0;
	double ampl = persistence;
	double max = 0;
	double freq = 1;

	for (int i = 0; i < octaves; i++)
	{
		total += GetNoise2D(x * freq, y * freq) * ampl;
		freq *= 2;
		max += ampl;
		ampl *= persistence;
	}

	return total / max;
}


// Octaves create a more natural perlin noise result
double PerlinNoise::OctaveNoise3D(double x, double y, double z, int octaves, double persistence)
{
	double noise, frequency, amplitude, maxNoise;

	// Amplitude refers to the scalar co-effecient of each noise iteration
	// Frequency = 2 ^ iteration
	amplitude = frequency = 1.0;

	// No iterations have passed, the max noise cannot have a value
	noise = maxNoise = 0.0;

	for (int i = 0; i < octaves; ++i)
	{
		noise += GetNoise3D(x * frequency, y * frequency, z * frequency) * amplitude;

		maxNoise += amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}

	// Normalise the result
	return noise / maxNoise;
}

// Get Gradient returns the dot product between a random gradient vector (of unit length)
// and the vector representing the x, y, z point in the unit cube
// NOTE: This function is biased towards 4 gradients because it is faster 
// to do hash & 15 than hash % 11 (as there should only be 12 gradient vectors)
// Source: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html
double PerlinNoise::GetGradient(int hash, double x, double y, double z)
{
	// Convert lower 4 bits of hash into 12 gradient directions
	switch (hash & 0xF)
	{
		case 0x0: return  x + y;
		case 0x1: return -x + y;
		case 0x2: return  x - y;
		case 0x3: return -x - y;
		case 0x4: return  x + z;
		case 0x5: return -x + z;
		case 0x6: return  x - z;
		case 0x7: return -x - z;
		case 0x8: return  y + z;
		case 0x9: return -y + z;
		case 0xA: return  y - z;
		case 0xB: return -y - z;
		case 0xC: return  y + x;
		case 0xD: return -y + z;
		case 0xE: return  y - x;
		case 0xF: return -y - z;
		default: return 0;
	}
}

double PerlinNoise::GetGradient(int hash, double x, double y)
{
	switch (hash & 0xF)
	{
	case 0x0: return x + y;
	case 0x1: return -x + y;
	case 0x2: return x - y;
	case 0x3: return -x - y;

	case 0x4: return x + y;
	case 0x5: return -x + y;
	case 0x6: return x - y;
	case 0x7: return -x - y;

	case 0x8: return x + y;
	case 0x9: return -x + y;
	case 0xA: return x - y;
	case 0xB: return -x - y;

	case 0xC: return x + y;
	case 0xD: return -x + y;
	case 0xE: return x - y;
	case 0xF: return -x - y;
	}
	return 0.0;
}
