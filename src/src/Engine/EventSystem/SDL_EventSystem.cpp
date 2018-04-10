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
	{ SDL_WINDOWEVENT_SHOWN, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_HIDDEN, ES_WIND_HIDE },
	{ SDL_WINDOWEVENT_EXPOSED, ES_WIND_EXPOSE },
	{ SDL_WINDOWEVENT_MOVED, ES_WIND_MOVE },
	{ SDL_WINDOWEVENT_RESIZED, ES_WIND_RESIZE },
	{ SDL_WINDOWEVENT_SIZE_CHANGED, ES_WIND_SIZE_CHANGE },
	{ SDL_WINDOWEVENT_MINIMIZED, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_MAXIMIZED, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_RESTORED, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_ENTER, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_LEAVE, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_FOCUS_GAINED, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_FOCUS_LOST, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_CLOSE, ES_WIND_CLOSE },
	{ SDL_WINDOWEVENT_TAKE_FOCUS, ES_WIND_SHOW },
	{ SDL_WINDOWEVENT_HIT_TEST, ES_WIND_SHOW },
};


const std::map<int, int> SDL_EventSystem::KEY_CODE_MAP = 
{
	{ SDLK_0, ES_KEYC_0 },
	{ SDLK_1, ES_KEYC_1 },
	{ SDLK_2, ES_KEYC_2 },
	{ SDLK_3, ES_KEYC_3 },
	{ SDLK_4, ES_KEYC_4 },
	{ SDLK_5, ES_KEYC_5 },
	{ SDLK_6, ES_KEYC_6 },
	{ SDLK_7, ES_KEYC_7 },
	{ SDLK_8, ES_KEYC_8 },
	{ SDLK_9, ES_KEYC_9 },


	{ SDLK_a, ES_KEYC_A },
	{ SDLK_b, ES_KEYC_B },
	{ SDLK_c, ES_KEYC_C },
	{ SDLK_d, ES_KEYC_D },
	{ SDLK_e, ES_KEYC_E },
	{ SDLK_f, ES_KEYC_F },
	{ SDLK_g, ES_KEYC_G },
	{ SDLK_h, ES_KEYC_H },
	{ SDLK_i, ES_KEYC_I },
	{ SDLK_j, ES_KEYC_J },
	{ SDLK_k, ES_KEYC_K },
	{ SDLK_l, ES_KEYC_L },
	{ SDLK_m, ES_KEYC_M },
	{ SDLK_n, ES_KEYC_N },
	{ SDLK_o, ES_KEYC_O },
	{ SDLK_p, ES_KEYC_P },
	{ SDLK_q, ES_KEYC_Q },
	{ SDLK_r, ES_KEYC_R },
	{ SDLK_s, ES_KEYC_S },
	{ SDLK_t, ES_KEYC_T },
	{ SDLK_u, ES_KEYC_U },
	{ SDLK_v, ES_KEYC_V },
	{ SDLK_w, ES_KEYC_W },
	{ SDLK_x, ES_KEYC_X },
	{ SDLK_y, ES_KEYC_Y },
	{ SDLK_z, ES_KEYC_Z },

	{ SDLK_LALT, ES_KEYC_LALT },
	{ SDLK_PRINTSCREEN, ES_KEYC_PRTSCR },
	{ SDLK_SPACE, ES_KEYC_SPACE }

};

const std::map<Uint8, int> SDL_EventSystem::MOUSE_BUTTON_MAP =
{
	{ SDL_BUTTON_LEFT, ES_MOUSE_BTN_L },
	{ SDL_BUTTON_RIGHT, ES_MOUSE_BTN_R },
	{ SDL_BUTTON_MIDDLE, ES_MOUSE_BTN_M },
	{ SDL_BUTTON_X1, ES_MOUSE_BTN_X1 },
	{ SDL_BUTTON_X2, ES_MOUSE_BTN_X2 }
};


void SDL_EventSystem::Update(double time)
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_WINDOWEVENT:
			processWindowEvent(sdlEvent.window.windowID, WINDOW_EVENT_TYPE_MAP.at(sdlEvent.window.event), sdlEvent.window.data1, sdlEvent.window.data2);
			break;
		case SDL_KEYUP:
		{
			int key = KEY_CODE_MAP.at(sdlEvent.key.keysym.sym);
			m_keydown[key] = false;
			processKeyboardEvent(ES_KEY_UP, KEY_CODE_MAP.at(sdlEvent.key.keysym.sym));
			break;
		}
		case SDL_KEYDOWN:
		{
			int key = KEY_CODE_MAP.at(sdlEvent.key.keysym.sym);
			m_keydown[key] = true;
			processKeyboardEvent(ES_KEY_DOWN, key);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			m_lastMousePosition.x = sdlEvent.motion.x;
			m_lastMousePosition.y = sdlEvent.motion.y;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			int mb = MOUSE_BUTTON_MAP.at(sdlEvent.button.button);
			m_mouseBtnDown[mb] = true;
			m_lastMousePosition.x = sdlEvent.button.x;
			m_lastMousePosition.y = sdlEvent.button.y;
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			int mb = MOUSE_BUTTON_MAP.at(sdlEvent.button.button);
			m_mouseBtnDown[mb] = false;
			m_lastMousePosition.x = sdlEvent.button.x;
			m_lastMousePosition.y = sdlEvent.button.y;
			break;
		}
		default:
			break;
		}

			

		
	}
}

