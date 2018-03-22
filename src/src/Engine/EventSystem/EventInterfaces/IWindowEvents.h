#pragma once

class IShowWindow
{
public:
	virtual void ShowWindow() = 0;
};

class IHideWindow
{
public:
	virtual void HideWindow() = 0;
};
class IExposeWindow
{
public:
	virtual void ExposeWindow() = 0;
};
class IMoveWindow
{
public:
	virtual void MoveWindow(int x, int y) = 0;
};
class IResizeWindow
{
public:
	virtual void ResizeWindow(int x, int y) = 0;
};
class IChangeWindowSize
{
public:
	virtual void ChangeWindowSize(int x, int y) = 0;
};
class ICloseWindow
{
public:
	virtual void CloseWindow() = 0;
};

class IWindowEvents
	: public IShowWindow, public IHideWindow, public IExposeWindow,
	public IMoveWindow, public IResizeWindow, public IChangeWindowSize,
	public ICloseWindow
{
public:
	void ShowWindow() override = 0;
	void HideWindow() override = 0;
	void ExposeWindow() override = 0;
	void MoveWindow(int x, int y) override = 0;
	void ResizeWindow(int x, int y) override = 0;
	void ChangeWindowSize(int x, int y) override = 0;
	void CloseWindow() override = 0;
};