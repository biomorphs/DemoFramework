/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include "core/linear_allocator.h"
#include "core/intmath.h"

namespace Render
{
	class Device;
	class CommandBuffer
	{
	public:
		CommandBuffer(size_t maximumSize = 1024 * 1024);
		~CommandBuffer() = default;
		CommandBuffer(const CommandBuffer&) = delete;

		// Command functions are
		// void command(void* commandPtr)
		using CommandFn = void(*)(const void*, Device&);

		template<class CommandData>
		void PushCommand(CommandFn fn, const CommandData& args);

		void CallCommands(Device& device);
		void Reset();

	private:
		// Aligned on 16 byte boundaries to accomodate SIMD data storage
		struct alignas(16) RenderCommand
		{
			CommandFn m_fn;
			uint32_t m_totalSize;
		};

		Core::LinearAllocator m_cmdBufferAllocator;
	};

	template<class CommandData>
	void CommandBuffer::PushCommand(CommandFn fn, const CommandData& args)
	{
		static_assert(alignof(CommandData) <= 16, "Command data alignment too large");
		const size_t realSizeRequired = Core::AlignUp( sizeof(RenderCommand) + sizeof(CommandData), size_t(16) );

		void* rawBuffer = m_cmdBufferAllocator.Allocate(realSizeRequired, 16);
		if (rawBuffer != nullptr)
		{
			RenderCommand* __restrict cmdHeader = reinterpret_cast<RenderCommand*>(rawBuffer);
			cmdHeader->m_fn = fn;
			cmdHeader->m_totalSize = realSizeRequired;

			auto rawBufferAddr = reinterpret_cast<const uintptr_t>(rawBuffer);
			CommandData* cmdDataPtr = reinterpret_cast<CommandData*>(rawBufferAddr + sizeof(RenderCommand));
			CommandData* newCommand = new(cmdDataPtr) CommandData(args);	// Forward arguments to CTOR
		}
	}
}