#pragma once
#include <chrono>

using namespace std::chrono;

class AppTime
{

public:

private:
	static high_resolution_clock::time_point StartTime;
	static high_resolution_clock::time_point PreviousFrame;
	static double DeltaTime;

public:
	// TO DO: Hide this so can only be called when program starts
	static void Initialise();
	static double GetDeltaTime();
	static double GetTime();
	static void UpdateDeltaTime();

private:


};