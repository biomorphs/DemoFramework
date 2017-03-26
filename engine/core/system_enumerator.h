/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include <string>

namespace Core
{
	class ISystem;

	class ISystemEnumerator
	{
	public:
		virtual ISystem* GetSystem(const char* systemName) = 0;
	};
}