#include "platform/platform.h"
#include "core/module_export.h"
#include "core/engine.h"

// Apps should export this function
extern DEMO_IMPORT void RegisterAppSystems(Core::ISystemRegistrar&);

int main (int argc, char *argv[])
{
	if (Platform::Initialise(argc, argv) != Platform::InitResult::InitOK)
	{
		return -1;
	}

	Core::Engine engine;
	if (engine.Initialise(RegisterAppSystems))
	{
		engine.RunMainThread();
	}

	Platform::Shutdown();
	return 0;
}