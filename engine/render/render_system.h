/*
DemoFramework
Matt Hoyle
*/
#pragma once
#include <memory>
#include "core/system.h"
#include "platform/thread.h"
#include "platform/semaphore.h"
#include "platform/atomics.h"
#include "device.h"
#include "window.h"
#include "command_buffer.h"
#include "frame_context.h"

namespace Render
{
	class FrameContext;
	class RenderSystem : public Core::ISystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();

		bool Initialise() override;
		bool PostInit() override;
		bool Tick() override;
		void Shutdown() override;
	private:
		void PushFrameToRenderThread(FrameContext* fc);
		void DoFrame();

		static int32_t RenderThreadFn(RenderSystem& renderSystem);
		Platform::AtomicInt32 m_renderThreadShouldQuit;

		Platform::Semaphore m_renderDeviceCreated;	// Has the render thread created a device
		Platform::Semaphore m_frameContextReady;	// Has a frame been pushed
		Platform::Semaphore m_lastFrameFinished;	// Has the gpu finished the last frame

		std::unique_ptr<FrameContext> m_thisFrame;
		std::unique_ptr<Window> m_mainWindow;
		std::unique_ptr<Device> m_device;	// Created on render thread!
		std::unique_ptr<Platform::Thread> m_renderThread;
	};
}