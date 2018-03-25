#pragma once
#include <map>
#include <memory>

#include "../EventInterfaces/IWindowEvents.h"

class WindowEventMap
{
private:
	std::map<unsigned int, std::shared_ptr<IWindowEvents>> m_windowEvents;

public:
	bool Add(unsigned int windowID, std::shared_ptr<IWindowEvents> windowEvent)
	{
		if (m_windowEvents.find(windowID) == m_windowEvents.end())
		{
			m_windowEvents.emplace(std::pair<unsigned int, std::shared_ptr<IWindowEvents>>(windowID, windowEvent));
			return true;
		}
		return false;
	}

	bool Remove(unsigned int windowID)
	{
		std::map<unsigned int, std::shared_ptr<IWindowEvents>>::iterator it;
		it = m_windowEvents.find(windowID);

		if (it != m_windowEvents.end())
		{
			m_windowEvents.erase(windowID);
			return true;
		}

		return false;
	}

	bool Exists(unsigned int windowID)
	{
		return m_windowEvents.find(windowID) != m_windowEvents.end();
	}

	std::shared_ptr<IWindowEvents> FindEvent(unsigned int windowID)
	{
		if (m_windowEvents.find(windowID) != m_windowEvents.end())
		{
			return m_windowEvents[windowID];
		}
		return std::shared_ptr<IWindowEvents>();
	}
};