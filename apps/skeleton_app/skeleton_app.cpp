/*
DemoFramework
Matt Hoyle
*/
#pragma once

#include "core/module_export.h"
#include "core/system.h"
#include "core/system_registrar.h"
#include "core/system_enumerator.h"
#include "core/timer_system.h"

class SkeletonSystem : public Core::ISystem
{
public:
	SkeletonSystem() = default;
	~SkeletonSystem() = default;

	bool PreInit(Core::ISystemEnumerator& systemEnumerator) override
	{
		m_timerSystem = static_cast<Core::TimerSystem*>( systemEnumerator.GetSystem("Core::TimerSystem") );
		return true;
	}
	bool Initialise() override
	{
		printf("Initialise!\n");
		return true;
	}
	bool Tick() override
	{
		printf("Tick! %f seconds since initialise! Shutting down...\n", m_timerSystem->TimeSinceInitialiseSeconds());
		return false; 
	}
	void Shutdown() override 
	{
		printf("Shutdown!\n");
	}

	Core::TimerSystem* m_timerSystem;
};

DEMO_EXPORT void RegisterAppSystems(Core::ISystemRegistrar& systemRegistrar)
{
	printf("Whutwhut! Register your systems here\n");
	systemRegistrar.RegisterSystem("SkeletonSystem", new SkeletonSystem);
}