#include "SDL_MyWindow.h"

SDL_MyWindow::SDL_MyWindow()
{
	init();
}

SDL_MyWindow::SDL_MyWindow(unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title)
	: Window(width, height, x, y, title)
{
	init();
}

void SDL_MyWindow::init()
{
	m_window = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_width, m_height, SDL_WINDOW_OPENGL);
}
