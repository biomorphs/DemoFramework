/*
SDLEngine
Matt Hoyle
*/
#pragma once
#include <stdint.h>

namespace Platform
{
	class Semaphore
	{
	public:
		Semaphore(uint32_t initialValue);
		~Semaphore();

		void Post();
		void Wait();

	private:
		void* m_semaphore;
	};
}