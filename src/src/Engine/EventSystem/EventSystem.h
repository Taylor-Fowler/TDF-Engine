#pragma once
#include <memory>
#include <map>
#include <vector>

#include "EventDefs.h"
#include "EventInterfaces\IWindowEvents.h"
#include "EventInterfaces\IKeyboardEvents.h"
#include "Collections\WindowEventMap.h"

struct MousePosition
{
	int x, y;
};

class EventSystem
{
private:
	using KeyboardUpEventList = std::vector<std::shared_ptr<IKeyUp>>;
	using KeyboardDownEventList = std::vector<std::shared_ptr<IKeyDown>>;

	WindowEventMap m_windowEvents;
	KeyboardUpEventList m_keyUpEvents;
	KeyboardDownEventList m_keyDownEvents;
protected:
	MousePosition m_lastMousePosition = { 0, 0 };
	std::map<int, bool> m_keydown;
	std::map<int, bool> m_mouseBtnDown;

public:
	virtual void Update(double time) = 0;

	void SubscribeWindowEvents(std::shared_ptr<IWindowEvents> observer, unsigned int windowID);
	void UnsubscribeWindowEvents(unsigned int windowID);

	void SubscribeKeyUpEvents(std::shared_ptr<IKeyUp> observer);
	void UnsubscribeKeyUpEvents(std::shared_ptr<IKeyUp> observer);

	void SubscribeKeyDownEvents(std::shared_ptr<IKeyDown> observer);
	void UnsubscribeKeyDownEvents(std::shared_ptr<IKeyDown> observer);
	bool IsKeyDown(int keycode) const;

	bool IsMouseBtnDown(int btnCode) const;
	MousePosition GetMousePosition() const
	{
		return m_lastMousePosition;
	}

	virtual ~EventSystem() = 0 {};


protected:
	void processWindowEvent(unsigned int windowID, int eventID, int data1, int data2);
	void processKeyboardEvent(unsigned int eventID, int keycode);
};