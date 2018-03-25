#include "EventSystem.h"
#include "EventDefs.h"

void EventSystem::SubscribeWindowEvents(std::shared_ptr<IWindowEvents> observer, unsigned int windowID)
{
	m_windowEvents.Add(windowID, observer);
}

void EventSystem::UnsubscribeWindowEvents(unsigned int windowID)
{
	m_windowEvents.Remove(windowID);
}

void EventSystem::processWindowEvent(unsigned int windowID, int eventID, int data1, int data2)
{
	std::shared_ptr<IWindowEvents> eventHandler = m_windowEvents.FindEvent(windowID);
	if (eventHandler == nullptr)
	{
		return;
	}

	switch (eventID)
	{
	case ES_WIND_SHOW:
		eventHandler->ShowWindow();
		break;
	case ES_WIND_HIDE:
		eventHandler->HideWindow();
		break;
	case ES_WIND_EXPOSE:
		eventHandler->ExposeWindow();
		break;
	case ES_WIND_MOVE:
		eventHandler->MoveWindow(data1, data2);
		break;
	case ES_WIND_RESIZE:
		eventHandler->ResizeWindow(data1, data2);
		break;
	case ES_WIND_SIZE_CHANGE:
		eventHandler->ChangeWindowSize(data1, data2);
		break;
	case ES_WIND_CLOSE:
		eventHandler->CloseWindow();
	default:
		// Error territory
		break;
	}
}

void EventSystem::processEvent(int eventType, int eventID, int data1, int data2)
{
	if (eventType == ES_EVENT_WINDOW)
	{

	}
}
