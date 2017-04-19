/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include "command_buffer.h"
#include "core/vector_math.h"

namespace Render
{
	class FrameContext
	{
	public:
		FrameContext(size_t maximumSize = 1024 * 1024);
		~FrameContext() = default;
		FrameContext(const FrameContext&) = delete;
		FrameContext& operator=(const FrameContext&) = delete;
		FrameContext(FrameContext&&) = default;
		FrameContext& operator=(FrameContext&&) = default;

		void ClearScreen( const glm::vec4 colour );
		void DrawFrame(Device& device);

	private:
		CommandBuffer m_cmdBuffer;
	};
}