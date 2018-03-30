#include "Time.h"



high_resolution_clock::time_point	AppTime::StartTime;
high_resolution_clock::time_point	AppTime::PreviousFrame;
double	AppTime::DeltaTime		= 0.0f;



void AppTime::Initialise()
{
	StartTime = high_resolution_clock::now();
	PreviousFrame = StartTime;
}

double AppTime::GetDeltaTime()
{
	return DeltaTime;
}

double AppTime::GetTime()
{
	return duration_cast<duration<double>>(high_resolution_clock::now() - StartTime).count();
}

void AppTime::UpdateDeltaTime()
{
	high_resolution_clock::time_point current = high_resolution_clock::now();
	
	DeltaTime = duration_cast<duration<double>>(current - PreviousFrame).count();

	PreviousFrame = current;
}
