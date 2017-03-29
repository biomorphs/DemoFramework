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
		CommandBuffer(Device& d, size_t maximumSize = 1024 * 1024);
		~CommandBuffer() = default;
		CommandBuffer(const CommandBuffer&) = delete;

		// Command functions are
		// void command(void* commandPtr, Device&)
		using CommandFn = void(*)(void*, Device&);

		// Variadic template pushes arguments to command constructor
		template<class ... CommandData>
		void PushCommand(CommandFn fn, CommandData ... args);

	private:
		// Aligned on 16 byte boundaries to accomodate SIMD data storage
		struct alignas(16) maximumSize
		{
			CommandFn m_fn;
			uint32_t m_totalSize;
		};

		Device& m_device;
		Core::LinearAllocator m_cmdBufferAllocator;
	};

	template<class ... CommandData>
	void CommandBuffer::PushCommand(CommandFn fn, CommandData ... args)
	{
		const size_t realSizeRequired = sizeof(RenderCommand) + sizeof(CommandData);

		// This will not align the object correctly if its alignment requirement is > 16 bytes
		void* rawBuffer = m_cmdBufferAllocator.Allocate(realSizeRequired, 16);
		if (rawBuffer != nullptr)
		{
			RenderCommand* cmdHeader = reinterpret_cast<RenderCommand*>(rawBuffer);
			cmdHeader->m_fn = fn;
			cmdHeader->m_totalSize = realSizeRequired;

			auto rawBufferAddr = reinterpret_cast<const uintptr_t>(rawBuffer);
			void* cmdDataPtr = rawBufferAddr + sizeof(RenderCommand);
			CommandData* newCommand = new(cmdDataPtr) CommandData(args);	// Forward arguments to CTOR
		}
	}
}