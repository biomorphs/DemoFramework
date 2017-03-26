/*
DemoFramework
Matt Hoyle
*/
#pragma once

#include "core/module_export.h"
#include "core/system.h"
#include "core/system_registrar.h"

class SkeletonSystem : public Core::ISystem
{
public:
	SkeletonSystem() = default;
	~SkeletonSystem() = default;

	bool Initialise() override
	{
		printf("Initialise!\n");
		return true;
	}
	bool Tick() override
	{
		printf("Tick! Shutting down...\n");
		return false; 
	}
	void Shutdown() override 
	{
		printf("Shutdown!\n");
	}
};

DEMO_EXPORT void RegisterAppSystems(Core::ISystemRegistrar& systemRegistrar)
{
	printf("Whutwhut! Register your systems here\n");
	systemRegistrar.RegisterSystem("SkeletonSystem", new SkeletonSystem);
}