/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <memory>
#include "core/system.h"
#include "platform/thread.h"
#include "platform/atomics.h"
#include "device.h"
#include "window.h"
#include "frame_context.h"

namespace Render
{
	class RenderSystem : public Core::ISystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();

		FrameContext& GetFrameContext();
		bool Initialise() override;
		bool PostInit() override;
		bool Tick() override;
		void Shutdown() override;
	private:
		static int32_t RenderThreadFn(RenderSystem& renderSystem);
		Platform::AtomicInt32 m_renderContextCreated;
		Platform::AtomicInt32 m_renderThreadShouldQuit;
		std::unique_ptr<Window> m_mainWindow;
		std::unique_ptr<Device> m_device;	// Created on render thread!
		std::unique_ptr<Platform::Thread> m_renderThread;
		std::unique_ptr<FrameContext> m_thisFrame;
	};
}