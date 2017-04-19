/*
DemoFramework
Matt Hoyle
*/
#include "command_buffer.h"

namespace Render
{
	CommandBuffer::CommandBuffer(size_t maximumSize)
		: m_cmdBufferAllocator(maximumSize)
	{
	}

	void CommandBuffer::CallCommands(Device& device)
	{
		const size_t cmdListHeadAddr = reinterpret_cast<const size_t> (m_cmdBufferAllocator.GetBuffer());
		const size_t listSize = m_cmdBufferAllocator.TotalAllocated();
		size_t nextCmdOffset = 0;
		while (nextCmdOffset < listSize)
		{
			const size_t cmdHeadAddr = cmdListHeadAddr + nextCmdOffset;
			const size_t cmdDataAddr = cmdListHeadAddr + nextCmdOffset + sizeof(RenderCommand);
			const RenderCommand* __restrict cmdHeadPtr = reinterpret_cast<const RenderCommand*>(cmdHeadAddr);
			const void* __restrict cmdDataPtr = reinterpret_cast<const void*>(cmdDataAddr);
			nextCmdOffset += cmdHeadPtr->m_totalSize;
			cmdHeadPtr->m_fn(cmdDataPtr, device);
		}
	}

	void CommandBuffer::Reset()
	{
		m_cmdBufferAllocator.Rewind();
	}
}