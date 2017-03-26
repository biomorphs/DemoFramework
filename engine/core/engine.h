/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <functional>
#include <memory>
#include "system_manager.h"

namespace Core
{
	class Engine
	{
	public:
		Engine() = default;
		Engine(const Engine&) = delete;
		~Engine();

		// Callback is fired when user systems should be registered
		bool Initialise(std::function<void(ISystemRegistrar&)> userSystemRegistrationCallback);
		
		// This function will not return until the engine is shut down
		// OS message pump will run here
		void RunMainThread();

	private:
		void RegisterEngineSystems(std::function<void(ISystemRegistrar&)>& userSystemRegistrationCallback);
		void Shutdown();

		std::unique_ptr<SystemManager> m_systemManager;
	};
}