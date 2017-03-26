/*
DemoFramework
Matt Hoyle
*/
#include "timer_system.h"
#include "platform/high_perf_timer.h"
#include <algorithm>

namespace Core
{
	bool TimerSystem::Initialise()
	{
		m_ticksAtInitialise = Platform::HighPerformanceTimer::Ticks();
		m_lastUpdateTicks = m_ticksAtInitialise;
		m_currentUpdateTicks = m_ticksAtInitialise;
		return true;
	}

	bool TimerSystem::Tick()
	{
		m_lastUpdateTicks = m_currentUpdateTicks;
		m_currentUpdateTicks = Platform::HighPerformanceTimer::Ticks();

		m_currentUpdateTicks = std::max(m_currentUpdateTicks, m_lastUpdateTicks);	// Ensure time doesn't go backwards!

		return true;
	}

	float TimerSystem::ToSeconds(uint64_t ticks) const
	{
		return (float)ticks / (float)Platform::HighPerformanceTimer::Frequency();
	}

	float TimerSystem::TimeSinceInitialiseSeconds() const
	{
		return ToSeconds(m_currentUpdateTicks - m_ticksAtInitialise);
	}

	float TimerSystem::TimeSinceLastUpdateSeconds() const
	{
		return ToSeconds(m_currentUpdateTicks - m_lastUpdateTicks);
	}
}