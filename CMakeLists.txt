cmake_minimum_required (VERSION 2.8)
project (DemoFramework)

# Project output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# GLM
set(GLM_ROOT_PATH "${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4/glm")
set(GLM_INCLUDE_DIR "${GLM_ROOT_PATH}/glm")

# GLEW
set(GLEW_ROOT_PATH "${CMAKE_SOURCE_DIR}/external/glew-2.0.0")
set(GLEW_INCLUDE_DIR "${GLEW_ROOT_PATH}/include")
set(GLEW_LIBRARY "${GLEW_ROOT_PATH}/lib/Release/Win32/glew32.lib")
set(GLEW_RUNTIME_LIBRARY "${GLEW_ROOT_PATH}/bin/Release/Win32/glew32.dll")

# SDL 2
set(SDL2_ROOT_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.0.4-VC/SDL2-2.0.4")
set(SDL2_INCLUDE_DIR "${SDL2_ROOT_PATH}/include")
set(SDL2_LIBRARY "${SDL2_ROOT_PATH}/lib/x86/SDL2.lib")
set(SDL2_LIBRARY_MAIN "${SDL2_ROOT_PATH}/lib/x86/SDL2main.lib")
set(SDL2_RUNTIME_LIBRARY "${SDL2_ROOT_PATH}/lib/x86/SDL2.dll")

# Engine root path
set(DEMOFRAMEWORK_ROOT_PATH "${CMAKE_SOURCE_DIR}/engine")

# Engine projects
add_subdirectory (${DEMOFRAMEWORK_ROOT_PATH}/platform)
add_subdirectory (${DEMOFRAMEWORK_ROOT_PATH}/core)
add_subdirectory (${DEMOFRAMEWORK_ROOT_PATH}/render)

# Launcher project
add_subdirectory (${CMAKE_SOURCE_DIR}/launcher)

# Tests project
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

# Apps
add_subdirectory (${CMAKE_SOURCE_DIR}/apps)




