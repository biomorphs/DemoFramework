#include "platform/platform.h"

int main (int argc, char *argv[])
{
	Platform::Initialise(argc, argv);
	Platform::Shutdown();
	return 0;
}