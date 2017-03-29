/*
DemoFramework
Matt Hoyle
*/
#include "command_buffer.h"

namespace Render
{
	CommandBuffer::CommandBuffer(Device& d, size_t maximumSize)
		: m_device(d)
		, m_cmdBufferAllocator(maximumSize)
	{
	}
}