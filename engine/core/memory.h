/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <memory>

namespace Core
{
	void* HeapAllocate(size_t bytes, size_t alignment);
	void HeapFree(void* ptr);
}