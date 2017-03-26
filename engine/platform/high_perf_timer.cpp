/*
SDLEngine
Matt Hoyle
*/
#include "time.h"
#include <sdl_timer.h>

namespace Platform
{
	namespace HighPerformanceTimer
	{
		uint64_t Ticks()
		{
			return SDL_GetPerformanceCounter();
		}

		uint64_t Frequency()
		{
			return SDL_GetPerformanceFrequency();
		}
	}
}