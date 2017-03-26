#include "catch.hpp"
#include "core/string_hashing.h"

TEST_CASE("Simple string hashing correct", "[Core::StringHashing]")
{
	SECTION("Null string is empty hash")
	{
		REQUIRE(Core::StringHashing::GetHash(nullptr) == Core::StringHashing::EmptyHash);
	}

	SECTION("Empty string is empty hash")
	{
		REQUIRE( Core::StringHashing::GetHash("") == Core::StringHashing::EmptyHash );
	}

	SECTION("Different strings give different hashes")
	{
		auto stringHash0 = Core::StringHashing::GetHash("AString");
		auto stringHash1 = Core::StringHashing::GetHash("ADifferentString");
		REQUIRE(stringHash0 != stringHash1);
	}

	SECTION("Matching strings give same hash")
	{
		auto stringHash0 = Core::StringHashing::GetHash("Some random string");
		auto stringHash1 = Core::StringHashing::GetHash("Some random string");
		REQUIRE(stringHash0 == stringHash1);
	}
}