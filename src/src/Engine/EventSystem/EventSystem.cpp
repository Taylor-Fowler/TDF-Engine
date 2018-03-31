#include <algorithm>

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

void EventSystem::SubscribeKeyUpEvents(std::shared_ptr<IKeyUp> observer)
{
	m_keyUpEvents.push_back(observer);
}

void EventSystem::UnsubscribeKeyUpEvents(std::shared_ptr<IKeyUp> observer)
{
	auto handler = std::find(m_keyUpEvents.begin(), m_keyUpEvents.end(), observer);
	if (handler != m_keyUpEvents.end())
		m_keyUpEvents.erase(handler);
}

void EventSystem::SubscribeKeyDownEvents(std::shared_ptr<IKeyDown> observer)
{
	m_keyDownEvents.push_back(observer);
}

void EventSystem::UnsubscribeKeyDownEvents(std::shared_ptr<IKeyDown> observer)
{
	auto handler = std::find(m_keyDownEvents.begin(), m_keyDownEvents.end(), observer);
	if (handler != m_keyDownEvents.end())
		m_keyDownEvents.erase(handler);
}

bool EventSystem::IsKeyDown(int keycode) const
{
	auto search = m_keydown.find(keycode);
	if (search != m_keydown.end())
		return search->second;

	return false;
}

bool EventSystem::IsMouseBtnDown(int btnCode) const
{
	auto search = m_mouseBtnDown.find(btnCode);
	if (search != m_mouseBtnDown.end())
		return search->second;

	return false;
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

void EventSystem::processKeyboardEvent(unsigned int eventID, int keycode)
{
	if (eventID == ES_KEY_UP)
	{
		for (auto &handler : m_keyUpEvents)
			handler->KeyUp(keycode);
	}
	else
	{
		for (auto &handler : m_keyDownEvents)
			handler->KeyDown(keycode);
	}
}

