/*
DemoFramework
Matt Hoyle
*/
#pragma once

#include <stdlib.h>

namespace Core
{
	void* HeapAllocate(size_t bytes, size_t alignment)
	{
		return _aligned_malloc(bytes, alignment);
	}

	void HeapFree(void* ptr)
	{
		_aligned_free(ptr);
	}
}