/*
SDLEngine
Matt Hoyle
*/
#include "event_system.h"
#include "platform/system_events.h"

namespace Core
{
	EventSystem::EventSystem()
	{

	}

	EventSystem::~EventSystem()
	{

	}

	bool EventSystem::Tick()
	{
		auto theEvent = Platform::SystemEvents::Event::None;
		bool quitRequested = false;
		while (Platform::SystemEvents::PollEvent(theEvent))
		{
			switch (theEvent)
			{
			case Platform::SystemEvents::Event::QuitRequest:
				quitRequested = true;
				break;
			}
		}
		return !quitRequested;
	}
}