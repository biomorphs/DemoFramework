#include "catch.hpp"
#include "core/engine.h"

TEST_CASE("User system registration", "[Core::Engine]")
{
	Core::Engine testEngine;

	SECTION("User registration CB Fires")
	{
		bool cbCalled = false;
		testEngine.Initialise([&](Core::ISystemRegistrar& registrar) {
			cbCalled = true;
		});
		REQUIRE(cbCalled == true);
	}
}