#pragma once

class PerlinNoise 
{
	int p[512];
	static int permutation[];


	// Fades the value of t, adds more curvature to the value, without curvature, the noise will linearly increase with the value of t
	static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10);	}

	// Linearly interpolates between the value a and b by the coefficient f
	static double lerp(double f, double a, double b) { return a + f * (b - a); }


public:
	PerlinNoise();

	double GetNoise2D(double x, double y);
	double GetNoise3D(double x, double y, double z);

	double OctaveNoise2D(double x, double y, int octaves, double persistence);

	// http://flafla2.github.io/2014/08/09/perlinnoise.html
	double OctaveNoise3D(double x, double y, double z, int octaves, double persistence);

	static double GetGradient(int hash, double x, double y, double z);
	static double GetGradient(int hash, double x, double y);
};


