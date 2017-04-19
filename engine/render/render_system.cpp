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
		m_device->Present();
	}

	int32_t RenderSystem::RenderThreadFn(RenderSystem& renderSystem)
	{
		// Create the GPU device now
		renderSystem.m_device = std::make_unique<Device>( *renderSystem.m_mainWindow.get() );
		if (renderSystem.m_device == nullptr)
		{
			return -1;
		}
		else
		{
			while (renderSystem.m_renderThreadShouldQuit.Get() == 0)
			{
				renderSystem.DoFrame();
			}
		}
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


	}

	bool RenderSystem::PostInit()
	{ 
		m_mainWindow->Show();
		return true; 
	}

	bool RenderSystem::Tick()
	{
		return true;
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