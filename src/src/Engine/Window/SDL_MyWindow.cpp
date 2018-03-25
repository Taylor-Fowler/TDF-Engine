#include "SDL_MyWindow.h"

SDL_MyWindow::SDL_MyWindow()
	: Window()
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	m_x = (dm.w - m_width) / 2;
	m_y = (dm.h - m_height) / 2;

	init();
}

SDL_MyWindow::SDL_MyWindow(unsigned int width, unsigned int height, unsigned int x, unsigned int y, std::string title)
	: Window(width, height, x, y, title)
{
	init();
}

SDL_MyWindow::~SDL_MyWindow()
{
	SDL_GL_DeleteContext(m_glContext);
}

void SDL_MyWindow::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}

void SDL_MyWindow::init()
{
	m_window = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	m_glContext = SDL_GL_CreateContext(m_window);
}
