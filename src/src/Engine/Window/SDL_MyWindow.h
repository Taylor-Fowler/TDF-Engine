#pragma once
#include "SDL.h"
#include "Window.h"



class SDL_MyWindow : public Window
{
private:
	SDL_Window* m_window = nullptr;

public:
	SDL_MyWindow();
	SDL_MyWindow(unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title);
	~SDL_MyWindow() override {};

	void ShowWindow() override {};
	void HideWindow() override {};
	void ExposeWindow() override {};
	void MoveWindow(int x, int y) override {};
	void ResizeWindow(int x, int y) override {};
	void ChangeWindowSize(int x, int y) override {};
	void CloseWindow() override {};

private:
	void init();
};