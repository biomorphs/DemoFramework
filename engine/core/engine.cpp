/*
DemoFramework
Matt Hoyle
*/
#include "engine.h"

namespace Core
{
	Engine::~Engine()
	{
		Shutdown();
	}

	bool Engine::Initialise(std::function<void(ISystemRegistrar&)> userSystemRegistrationCallback)
	{
		m_systemManager = std::make_unique<SystemManager>();

		// call this after input, etc, but before render
		userSystemRegistrationCallback( *m_systemManager );

		// start up all systems
		if ( !m_systemManager->Initialise() )
		{
			Shutdown();
			return false;
		}
		
		return true;
	}

	void Engine::Shutdown()
	{
		if (m_systemManager != nullptr)
		{
			// systems call be shutdown even if they were never Init! make sure to handle it
			m_systemManager->Shutdown();
			m_systemManager = nullptr;
		}
	}

	void Engine::RunMainThread()
	{
		bool stillRunning = true;
		while (stillRunning)
		{
			stillRunning = m_systemManager->Tick();
		}
		Shutdown();
	}
}