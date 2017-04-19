/*
DemoFramework
Matt Hoyle
*/
#include "catch.hpp"
#include "render\command_buffer.h"

namespace Render
{
	class Device;
}

std::string cmdResults;
void Cmd(const void* buffer, Render::Device&)
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
		cmdBuffer.CallCommands(*(Render::Device*)nullptr);
		REQUIRE(cmdResults == "Cmd1Cmd2Cmd3");
	}

	SECTION("Reset works")
	{
		cmdResults = "";
		Render::CommandBuffer cmdBuffer;
		cmdBuffer.PushCommand(Cmd, 1);
		cmdBuffer.PushCommand(Cmd, 2);
		cmdBuffer.CallCommands(*(Render::Device*)nullptr);
		REQUIRE(cmdResults == "Cmd1Cmd2");
		cmdBuffer.Reset();
		cmdBuffer.PushCommand(Cmd, 3);
		cmdBuffer.CallCommands(*(Render::Device*)nullptr);
		REQUIRE(cmdResults == "Cmd1Cmd2Cmd3");
	}
}