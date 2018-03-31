#pragma once

class IKeyDown
{
public:
	virtual void KeyDown(int keyCode) = 0;
};


class IKeyUp
{
public:
	virtual void KeyUp(int keyCode) = 0;
};


class IKeyboardEvents
	: public IKeyDown, public IKeyUp
{
public:
	void KeyDown(int keyCode) override = 0;
	void KeyUp(int keyCode) override = 0;
};
