#pragma once
#include <map>

#include "EventSystem.h"



class SDL_EventSystem : public EventSystem
{
private:
	static const std::map<Uint32, int> EVENT_TYPE_MAP;
	static const std::map<Uint8, int> WINDOW_EVENT_TYPE_MAP;

public:
	void Update(double time) override;

	~SDL_EventSystem() override {};
};