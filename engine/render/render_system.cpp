/*
DemoFramework
Matt Hoyle
*/
#include "render_system.h"
#include "frame_context.h"

namespace Render
{
	RenderSystem::RenderSystem()
		: m_lastFrameFinished(0)
		, m_renderDeviceCreated(0)
		, m_frameContextReady(0)
	{

	}

	RenderSystem::~RenderSystem()
	{

	}

	void RenderSystem::DoFrame()
	{
		if(m_thisFrame != nullptr)
		{ 
			m_thisFrame->DrawFrame(*m_device);
		}
		m_device->Present();
	}

	int32_t RenderSystem::RenderThreadFn(RenderSystem& renderSystem)
	{
		// Create the GPU device now
		renderSystem.m_device = std::make_unique<Device>( *renderSystem.m_mainWindow.get() );
		renderSystem.m_renderDeviceCreated.Post();

		if (renderSystem.m_device == nullptr)
		{
			return -1;
		}
		else
		{
			
			while (renderSystem.m_renderThreadShouldQuit.Get() == 0)
			{
				renderSystem.m_frameContextReady.Wait();	// Wait for the next frame
				renderSystem.DoFrame();
				renderSystem.m_lastFrameFinished.Post();	// Signal the main thread that vsync finished
			}
		}

		// Destroy the device on this thread
		renderSystem.m_device = nullptr;

		return 0;
	}

	bool RenderSystem::Initialise()
	{
		m_mainWindow = std::make_unique<Window>("DemoFramework", glm::ivec2(1280, 720));
		m_renderThread = std::make_unique<Platform::Thread>();
		m_renderThread->Create("RenderThread", [this]() {
			return RenderThreadFn(*this);
		});

		m_renderDeviceCreated.Wait();

		// Push an empty frame to get the gpu thread rolling
		PushFrameToRenderThread(nullptr);

		return m_device != nullptr;
	}

	bool RenderSystem::PostInit()
	{ 
		m_mainWindow->Show();
		return true; 
	}

	bool RenderSystem::Tick()
	{
		// build the command buffer for the current frame
		auto newFrame = new FrameContext();
		newFrame->ClearScreen(glm::vec4(0.3f, 0.3f, 0.5f, 1.0f));

		// wait for the previous frame to finish
		m_lastFrameFinished.Wait();
		
		// push the new command buffer to the render thread
		PushFrameToRenderThread(newFrame);

		return true;
	}

	void RenderSystem::PushFrameToRenderThread(FrameContext* fc)
	{
		m_thisFrame.reset(fc);
		m_frameContextReady.Post();
	}

	void RenderSystem::Shutdown()
	{
		m_renderThreadShouldQuit.Set(1);
		m_renderThread->WaitForFinish();
		m_renderThread = nullptr;
		m_device = nullptr;
		m_mainWindow = nullptr;
	}
}