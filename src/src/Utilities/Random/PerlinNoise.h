#pragma once
#include "glm\glm.hpp"

class PerlinNoise 
{
	int p[512];
	static int permutation[];


	// Fades the value of t, adds more curvature to the value, without curvature, the noise will linearly increase with the value of t
	static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10);	}

	// Linearly interpolates between the value a and b by the coefficient f
	static double lerp(double f, double a, double b) { return a + f * (b - a); }

	static glm::vec4 mod289(glm::vec4 x)
	{
		return x - floor(x * (1.0f / 289.0f)) * 289.0f;
	}

	static glm::vec4 permute(glm::vec4 x)
	{
		return mod289(((x*34.0f) + 1.0f)*x);
	}

	static glm::vec4 taylorInvSqrt(glm::vec4 r)
	{
		return 1.79284291400159f - 0.85373472095314f * r;
	}

	static glm::vec2 fade(glm::vec2 t)
	{
		return t*t*t*(t*(t*6.0f - 15.0f) + 10.0f);
	}

public:
	PerlinNoise();

	static float cnoise(glm::vec2 P);

	double GetNoise2D(double x, double y);
	double GetNoise3D(double x, double y, double z);

	double OctaveNoise2D(double x, double y, int octaves, double persistence);

	// http://flafla2.github.io/2014/08/09/perlinnoise.html
	double OctaveNoise3D(double x, double y, double z, int octaves, double persistence);

	static double GetGradient(int hash, double x, double y, double z);
	static double GetGradient(int hash, double x, double y);
};


