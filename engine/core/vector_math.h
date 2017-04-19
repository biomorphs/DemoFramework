/*
DemoFramework
Matt Hoyle
*/
#pragma once

// Always use this instead of including glm directly - debug mode is incredibly slow
// otherwise

#define GLM_FORCE_INLINE 
#define GLM_FORCE_SSE2

#pragma optimize("o2", on)

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#pragma optimize("", off)