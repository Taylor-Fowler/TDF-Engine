#pragma once
#include "EventSystem.h"



class SDL_EventSystem : public EventSystem
{
public:
	void Update(double time) override {};

	~SDL_EventSystem() override {};
};