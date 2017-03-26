#include "platform/platform.h"
#include "core/module_export.h"
#include "core/engine.h"
#include "core/timer_system.h"

// Apps should export this function
extern DEMO_IMPORT void RegisterAppSystems(Core::ISystemRegistrar&);

void RegisterSystems(Core::ISystemRegistrar& registrar)
{
	// Register Engine systems ran before user code
	registrar.RegisterSystem("TimerSystem", new Core::TimerSystem());

	// Register user systems
	RegisterAppSystems(registrar);

	// Register Engine systems ran after user code
}

int main (int argc, char *argv[])
{
	if (Platform::Initialise(argc, argv) != Platform::InitResult::InitOK)
	{
		return -1;
	}

	Core::Engine engine;
	
	if (engine.Initialise(RegisterSystems))
	{
		engine.RunMainThread();
	}

	Platform::Shutdown();
	return 0;
}