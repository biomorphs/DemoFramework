/*
DemoFramework
Matt Hoyle
*/
#include "window.h"
#include "utils.h"
#include <SDL.h>

namespace Render
{
	Window::Window(const char* title, glm::ivec2 dimensions, int creationFlags)
	{
		int windowPosX = SDL_WINDOWPOS_UNDEFINED;
		int windowPosY = SDL_WINDOWPOS_UNDEFINED;
		int windowFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL;	// Always start hidden, using opengl
		
		if (creationFlags & CreateFullscreen)
			windowFlags |= SDL_WINDOW_FULLSCREEN;
		else if (creationFlags & CreateFullscreenDesktop)
			windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		else
		{
			if (creationFlags & CreateResizable)
				windowFlags |= SDL_WINDOW_RESIZABLE;

			if (creationFlags & CreateMinimized)
				windowFlags |= SDL_WINDOW_MINIMIZED;
			else if (creationFlags & CreateResizable)
				windowFlags |= SDL_WINDOW_MAXIMIZED;
		}

		m_windowHandle = SDL_CreateWindow(title, windowPosX, windowPosY, dimensions.x, dimensions.y, windowFlags);
		RENDER_ASSERT(m_windowHandle);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_windowHandle);
		m_windowHandle = nullptr;
	}

	void Window::Show()
	{
		RENDER_ASSERT(m_windowHandle);
		SDL_ShowWindow(m_windowHandle);
	}

	void Window::Hide()
	{
		RENDER_ASSERT(m_windowHandle);
		SDL_HideWindow(m_windowHandle);
	}

	SDL_Window* Window::GetWindowHandle() 
	{
		return m_windowHandle;
	}
}