/*
SDLEngine
Matt Hoyle
*/
#pragma once

namespace Platform
{
	namespace SystemEvents
	{
		enum class Event
		{
			None,
			QuitRequest
		};

		bool PollEvent(Event& eventOut);
	}
}