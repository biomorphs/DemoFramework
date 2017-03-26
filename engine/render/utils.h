/*
DemoFramework
Matt Hoyle
*/
#pragma once

#include <SDL.h>
#include <gl/glew.h>
#include <stdio.h>

namespace Render
{
	// Renderer utils (global error handling, etc)
	inline const char* TranslateGLError(uint32_t errorCode)
	{
		switch (errorCode)
		{
		case GL_INVALID_VALUE:
			return "Invalid value";
		case GL_INVALID_ENUM:
			return "Invalid enum";
		case GL_INVALID_OPERATION:
			return "Invalid operation";
		case GL_OUT_OF_MEMORY:
			return "Out of memory";
		default:
			return "No errors";
		}
		return nullptr;
	}
}

#define RENDER_ASSERT(condition, ...)					\
	if (!(condition))									\
	{													\
		printf("Assertion Failed: %s", #condition);		\
		const char* errorTxt = SDL_GetError();			\
		if (errorTxt != nullptr)						\
		{												\
			printf("SDL Error: %s", errorTxt);			\
		}												\
		__debugbreak();									\
	}													\
	

#define RENDER_PROCESS_GL_ERRORS(...)	\
	{\
		auto error = glGetError();	\
		while (error  != GL_NO_ERROR)	\
		{\
			printf("A GL Error Occured: %s returned %d (%s)", ##__VA_ARGS__, error, Render::TranslateGLError(error)); \
			error = glGetError();	\
		}\
	}

// Returns false if any errors occured
#define RENDER_PROCESS_GL_ERRORS_RET(...)	\
	{\
		bool shouldReturn = false;	\
		auto error = glGetError();	\
		while (error  != GL_NO_ERROR)	\
		{\
			RENDER_ASSERT(false, "A GL Error Occured: %s returned %d (%s)", ##__VA_ARGS__, error, Render::TranslateGLError(error)); \
			error = glGetError();	\
			shouldReturn = true;	\
		}\
		if ( shouldReturn )	\
		{\
			return false;\
		}\
	}