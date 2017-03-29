/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include "platform\atomics.h"
#include "memory.h"
#include <stdint.h>

namespace Core
{
	class LinearAllocator
	{
	public:
		typedef void* (*AllocFn)(size_t, size_t);
		typedef void (*FreeFn)(void*);
		LinearAllocator(int32_t totalSizeBytes, AllocFn allocFn = Core::HeapAllocate, FreeFn freeFn = Core::HeapFree);
		~LinearAllocator();

		void* Allocate(size_t bytes, size_t align);
		void Rewind();

	private:
		uint8_t* m_buffer;
		Platform::AtomicInt32 m_head;
		int32_t m_totalSize;
		AllocFn m_alloc;
		FreeFn m_free;
	};
}