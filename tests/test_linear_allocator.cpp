/*
DemoFramework
Matt Hoyle
*/
#include "catch.hpp"
#include "core/linear_allocator.h"

TEST_CASE("Alloc works", "[Core::LinearAllocator]")
{
	SECTION("Size correct")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(16, 1);
		REQUIRE(allocator.TotalAllocated() == 16);
		void* p1 = allocator.Allocate(32, 1);
		REQUIRE(allocator.TotalAllocated() == 48);
	}

	SECTION("Alignment correct")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(8, 1);
		REQUIRE((reinterpret_cast<size_t>(p0) & 1) == 0);

		void* p1 = allocator.Allocate(32, 16);
		REQUIRE((reinterpret_cast<size_t>(p1) & 15) == 0);

		void* p2 = allocator.Allocate(8, 64);
		REQUIRE((reinterpret_cast<size_t>(p2) & 63) == 0);

		void* p3 = allocator.Allocate(8, 128);
		REQUIRE((reinterpret_cast<size_t>(p3) & 127) == 0);
	}

	SECTION("No overlaps")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(8, 1);
		void* p1 = allocator.Allocate(16, 1);
		void* p2 = allocator.Allocate(24, 1);
		void* p3 = allocator.Allocate(2, 1);
		REQUIRE((size_t)(p0)+8 <= (size_t)p1);
		REQUIRE((size_t)(p1)+16 <= (size_t)p2);
		REQUIRE((size_t)(p2)+24 <= (size_t)p3);
	}

	SECTION("Rewind")
	{
		Core::LinearAllocator allocator(1024 * 1024);
		void* p0 = allocator.Allocate(8, 1);
		void* p1 = allocator.Allocate(16, 1);
		void* p2 = allocator.Allocate(24, 1);
		void* p3 = allocator.Allocate(2, 1);
		allocator.Rewind();
		void* newP0 = allocator.Allocate(8, 1);
		void* newP1 = allocator.Allocate(16, 1);
		REQUIRE((size_t)(newP0) == (size_t)p0);
		REQUIRE((size_t)(newP1) == (size_t)p1);
	}
}
