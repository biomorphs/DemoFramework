/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <stdint.h>
#include <memory>
#include "platform\atomics.h"

namespace Core
{
	class LinearAllocator
	{
	public:
		LinearAllocator(int32_t totalSizeBytes);
		~LinearAllocator();

		void* Allocate(int32_t bytes);
		void Rewind();

	private:
		std::unique_ptr<uint8_t[]> m_buffer;
		Platform::AtomicInt32 m_head;
		int32_t m_totalSize;
	};
}