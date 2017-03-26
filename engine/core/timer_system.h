/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <stdint.h>
#include "system.h"

namespace Core
{
	class TimerSystem : public ISystem
	{
	public:
		TimerSystem() = default;
		virtual ~TimerSystem() = default;

		float TimeSinceInitialiseSeconds() const;
		float TimeSinceLastUpdateSeconds() const;

		bool Initialise() override;
		bool Tick() override;

	private:
		float ToSeconds(uint64_t ticks) const;
		
		uint64_t m_ticksAtInitialise;
		uint64_t m_lastUpdateTicks;
		uint64_t m_currentUpdateTicks;
	};
}