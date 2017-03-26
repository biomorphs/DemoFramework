/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include <stdint.h>

namespace Platform
{
	namespace HighPerformanceTimer
	{
		uint64_t Ticks();
		uint64_t Frequency();
	}
}