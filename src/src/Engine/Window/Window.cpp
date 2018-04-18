#include "Window.h"
#include "../EventSystem/EventSystem.h"

std::vector<Window*> Window::_allWindows;
Window* Window::_activeWindow = nullptr;

void Window::init(EventSystem & eventSystem)
{
	if (_activeWindow == nullptr)
	{
		_activeWindow = this;
	}
	_allWindows.push_back(this);

	eventSystem.SubscribeWindowEvents(std::shared_ptr<IWindowEvents>(this), m_id);
}

Window * const Window::active()
{
	return _activeWindow;
}

std::vector<Window*> Window::AllWindows()
{
	return _allWindows;
}
