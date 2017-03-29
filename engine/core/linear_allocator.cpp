/*
DemoFramework
Matt Hoyle
*/
#include "linear_allocator.h"
#include "core/intmath.h"
#include <intrin.h>  

namespace Core
{
	const size_t c_bufferBaseAlignment = 1024 * 1024;	// Try to handle the largest alignment anyone will ask for

	LinearAllocator::LinearAllocator(int32_t totalSizeBytes, AllocFn allocFn, FreeFn freeFn)
	{
		m_buffer = reinterpret_cast<uint8_t*>(allocFn(totalSizeBytes, c_bufferBaseAlignment));
		m_head.Set(0);
		m_totalSize = totalSizeBytes;
	}

	LinearAllocator::~LinearAllocator()
	{
	}

	void* LinearAllocator::Allocate(size_t bytes, size_t align)
	{
		if (bytes >= INT32_MAX || align >= INT32_MAX)
		{
			return nullptr;
		}

		const int32_t requiredSize = bytes + align - 1;
		int32_t current = 0;
		do
		{
			current = m_head.Get();
			if (m_totalSize - current < requiredSize)
			{
				return 0;
			}
		} while (m_head.CAS(current, current + bytes ) == false);

		// Align up returned ptr
		int32_t alignedIndex = Core::AlignUp(current, (int32_t)align);
		return m_buffer + alignedIndex;
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
