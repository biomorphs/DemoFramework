/*
DemoFramework
Matt Hoyle
*/
#include "linear_allocator.h"
#include <intrin.h>  

namespace Core
{
	LinearAllocator::LinearAllocator(int32_t totalSizeBytes)
		: m_buffer(new uint8_t[totalSizeBytes])
	{
		m_head.Set(0);
		m_totalSize = totalSizeBytes;
	}

	LinearAllocator::~LinearAllocator()
	{
	}

	void* LinearAllocator::Allocate(int32_t bytes)
	{
		int32_t current = 0;
		do
		{
			current = m_head.Get();
			if (m_totalSize - current < bytes)
			{
				return 0;
			}
		} while (m_head.CAS(current, current + bytes ) == false);
		return reinterpret_cast<void*>( m_buffer.get() + current );
	}

	void LinearAllocator::Rewind()
	{
		int32_t currentHead = 0;
		do
		{
			currentHead = m_head.Get();
		} while (m_head.CAS(currentHead, 0) == false);
	}
}
