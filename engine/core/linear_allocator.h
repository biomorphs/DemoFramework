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
		LinearAllocator(const LinearAllocator&) = delete;
		LinearAllocator(LinearAllocator&&);
		~LinearAllocator();

		void* Allocate(size_t bytes, size_t align);
		void Rewind();

		inline const void* const GetBuffer() const {
			return m_buffer;
		}
		size_t TotalAllocated() const { return static_cast< size_t >( m_head.Get() ); }

	private:
		uint8_t* m_buffer;
		Platform::AtomicInt32 m_head;
		int32_t m_totalSize;
		AllocFn m_alloc;
		FreeFn m_free;
	};
}