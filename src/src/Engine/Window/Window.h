#pragma once
#include <string>
#include <memory>

#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EventInterfaces/IWindowEvents.h"

class Window : IWindowEvents
{
protected:
	int				m_id		= -1;
	unsigned int	m_width		= 800;
	unsigned int	m_height	= 600;
	unsigned int	m_x			= 400;
	unsigned int	m_y			= 300;
	std::string		m_title		= "A Window";

public:
	virtual void SwapBuffer() = 0;
	virtual ~Window() = 0 {};

protected:
	Window(EventSystem& eventSystem)
	{
		init(eventSystem);
	}
	Window(EventSystem& eventSystem, unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title)
		: m_width(width), m_height(height), m_x(x), m_y(y), m_title(title)
	{
		init(eventSystem);
	}

private:
	void init(EventSystem& eventSystem)
	{
		eventSystem.SubscribeWindowEvents(std::make_shared<IWindowEvents>(this), m_id);
	}
};