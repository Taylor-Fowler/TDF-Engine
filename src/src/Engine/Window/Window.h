#pragma once
#include <string>
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
	virtual ~Window() = 0 {};

protected:
	Window() {};
	Window(unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title)
		: m_width(width), m_height(height), m_x(x), m_y(y), m_title(title)
	{};
};