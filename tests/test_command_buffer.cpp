/*
DemoFramework
Matt Hoyle
*/
#include "catch.hpp"
#include "render\command_buffer.h"

std::string cmdResults;
void Cmd(const void* buffer)
{
	auto value = *reinterpret_cast<const int*>(buffer);
	cmdResults += "Cmd";
	cmdResults += std::to_string(value);;
}

TEST_CASE("Command buffer", "[Render::CommandBuffer]")
{
	SECTION("Commands fire in correct order")
	{
		cmdResults = "";
		Render::CommandBuffer cmdBuffer;
		cmdBuffer.PushCommand(Cmd, 1);
		cmdBuffer.PushCommand(Cmd, 2);
		cmdBuffer.PushCommand(Cmd, 3);
		cmdBuffer.CallCommands();
		REQUIRE(cmdResults == "Cmd1Cmd2Cmd3");
	}

	SECTION("Reset works")
	{
		cmdResults = "";
		Render::CommandBuffer cmdBuffer;
		cmdBuffer.PushCommand(Cmd, 1);
		cmdBuffer.PushCommand(Cmd, 2);
		cmdBuffer.CallCommands();
		REQUIRE(cmdResults == "Cmd1Cmd2");
		cmdBuffer.Reset();
		cmdBuffer.PushCommand(Cmd, 3);
		cmdBuffer.CallCommands();
		REQUIRE(cmdResults == "Cmd1Cmd2Cmd3");
	}
}