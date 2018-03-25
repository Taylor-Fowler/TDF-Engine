#pragma once
#include <memory>
#include <map>
#include "EventDefs.h"
#include "EventInterfaces\IWindowEvents.h"
#include "Collections\WindowEventMap.h"


class EventSystem
{
private:
	WindowEventMap m_windowEvents;

public:
	virtual void Update(double time) = 0;

	void SubscribeWindowEvents(std::shared_ptr<IWindowEvents> observer, unsigned int windowID);
	void UnsubscribeWindowEvents(unsigned int windowID);
	virtual ~EventSystem() = 0 {};

protected:
	void processWindowEvent(unsigned int windowID, int eventID, int data1, int data2);
	void processEvent(int eventType, int eventID, int data1, int data2);
};