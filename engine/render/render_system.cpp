/*
DemoFramework
Matt Hoyle
*/
#include "render_system.h"

namespace Render
{
	int32_t RenderSystem::RenderThreadFn(RenderSystem& renderSystem)
	{
		// Create the GPU device now
		renderSystem.m_device = std::make_unique<Device>( *renderSystem.m_mainWindow.get() );
		while (renderSystem.m_renderThreadShouldQuit.Get() == 0)
		{
			renderSystem.m_device->ClearColourDepthTarget(glm::vec4(0.0f));
			renderSystem.m_device->Present();
			_sleep(10);
		}
		return 0;
	}

	bool RenderSystem::Initialise()
	{
		m_mainWindow = std::make_unique<Window>("DemoFramework", glm::ivec2(1280, 720));
		m_renderThread = std::make_unique<Platform::Thread>();
		m_renderThread->Create("RenderThread", [this]() {
			return RenderThreadFn(*this);
		});

		return true;
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