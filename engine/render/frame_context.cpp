/*
DemoFramework
Matt Hoyle
*/
#include "frame_context.h"
#include "device.h"

namespace RenderInternal
{
	void ClearScreenCmd(const void* colourAsVec4, Render::Device& d)
	{
		auto colour = *reinterpret_cast<const glm::vec4*>(colourAsVec4);
		d.ClearColourDepthTarget(colour);
	}
}

namespace Render
{
	FrameContext::FrameContext(size_t maximumSize)
		: m_cmdBuffer(maximumSize)
	{

	}

	void FrameContext::ClearScreen(const glm::vec4 colour)
	{
		m_cmdBuffer.PushCommand(RenderInternal::ClearScreenCmd, colour);
	}

	void FrameContext::DrawFrame(Device& device)
	{
		m_cmdBuffer.CallCommands(device);
	}
}