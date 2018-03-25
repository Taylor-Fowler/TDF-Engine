#include "SDL.h"

#include "SDL_EventSystem.h"
#include "EventDefs.h"

const std::map<Uint32, int> SDL_EventSystem::EVENT_TYPE_MAP =
{
	{ SDL_WINDOWEVENT, ES_EVENT_WINDOW },
	{ SDL_KEYDOWN, ES_EVENT_KEYBOARD },
	{ SDL_KEYUP, ES_EVENT_KEYBOARD },
	{ SDL_MOUSEMOTION, ES_EVENT_MOUSE_MOVE },
	{ SDL_MOUSEBUTTONDOWN, ES_EVENT_MOUSE_BUTTON },
	{ SDL_MOUSEBUTTONUP, ES_EVENT_MOUSE_BUTTON },
	{ SDL_MOUSEWHEEL, ES_EVENT_MOUSE_WHEEL }
};

const std::map<Uint8, int> SDL_EventSystem::WINDOW_EVENT_TYPE_MAP =
{
	{ SDL_WINDOWEVENT_SHOWN, ES_WIND_SHOW }
};


void SDL_EventSystem::Update(double time)
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_WINDOWEVENT)
		{
			processWindowEvent(sdlEvent.window.windowID, WINDOW_EVENT_TYPE_MAP[sdlEvent.window.event], sdlEvent.window.data1, sdlEvent.window.data2);
		}
	}
}
