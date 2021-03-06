#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../EventSystem/EventInterfaces/IWindowEvents.h"

class EventSystem;

class Window : public IWindowEvents
{
protected:
	static std::vector<Window*> _allWindows;
	static Window* _activeWindow;

	int				m_id		= -1;
	unsigned int	m_width		= 1200;
	unsigned int	m_height	= 900;
	unsigned int	m_x			= 400;
	unsigned int	m_y			= 300;
	std::string		m_title		= "A Window";
	bool			m_closed	= false;

public:
	static Window* const active();
	static std::vector<Window*> AllWindows();

	virtual void SwapBuffer() = 0;
	virtual ~Window() = 0 {};

	void CloseWindow() override
	{
		m_closed = true;
	}
	bool IsClosed()
	{
		return m_closed;
	}
	void ShowWindow() override = 0;
	void HideWindow() override = 0;
	void ExposeWindow() override = 0;
	void MoveWindow(int x, int y) override = 0;
	void ResizeWindow(int x, int y) override = 0;
	void ChangeWindowSize(int x, int y) override = 0;

	unsigned int Width()
	{
		return m_width;
	}
	unsigned int Height()
	{
		return m_height;
	}
	unsigned int X()
	{
		return m_x;
	}
	unsigned int Y()
	{
		return m_y;
	}

protected:
	Window() {};
	Window(unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title)
		: m_width(width), m_height(height), m_x(x), m_y(y), m_title(title)
	{}

	virtual void init(EventSystem& eventSystem);
};