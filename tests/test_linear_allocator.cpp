#include "catch.hpp"
#include "core/linear_allocator.h"

TEST_CASE("Alloc works", "[Core::LinearAllocator]")
{	
	SECTION("No overlaps")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(8);
		void* p1 = allocator.Allocate(16);
		void* p2 = allocator.Allocate(24);
		void* p3 = allocator.Allocate(2);
		REQUIRE((size_t)(p0)+8 <= (size_t)p1);
		REQUIRE((size_t)(p1)+16 <= (size_t)p2);
		REQUIRE((size_t)(p2)+24 <= (size_t)p3);
	}

	SECTION("Rewind")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(8);
		void* p1 = allocator.Allocate(16);
		void* p2 = allocator.Allocate(24);
		void* p3 = allocator.Allocate(2);
		allocator.Rewind();
		void* newP0 = allocator.Allocate(8);
		void* newP1 = allocator.Allocate(16);
		REQUIRE((size_t)(newP0) == (size_t)p0);
		REQUIRE((size_t)(newP1) == (size_t)p1);
	}
}
