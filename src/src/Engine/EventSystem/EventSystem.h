#pragma once
#include <memory>
#include "EventDefs.h"
#include "EventInterfaces\IWindowEvents.h"



class EventSystem
{
public:
	virtual void Update(double time) = 0;

	void SubscribeWindowEvents(std::shared_ptr<IWindowEvents> observer, unsigned int windowID) {};
	virtual ~EventSystem() = 0 {};
};