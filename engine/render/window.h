/*
DemoFramework
Matt Hoyle
*/
#pragma once

#include <glm.hpp>

struct SDL_Window;

// This is a wrapper for a render window. A device must be paired with the window
namespace Render
{
	class Window
	{
	public:
		enum CreationFlags
		{
			CreateFullscreen = (1 << 1),
			CreateFullscreenDesktop = (1 << 2),
			CreateResizable = (1 << 3),
			CreateMinimized = (1 << 4),
			CreateMaximized = (1 << 5)
		};
		Window(const char* title, glm::ivec2 dimensions = glm::ivec2(-1,-1), int creationFlags = 0);
		~Window();

		void Show();
		void Hide();

		SDL_Window* GetWindowHandle();

	private:
		SDL_Window* m_windowHandle;
	};
}