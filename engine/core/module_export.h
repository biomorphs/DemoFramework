/*
DemoFramework
Matt Hoyle
*/
#pragma once

// Use this define when exporting function / class definitions from apps
// Only implemented for windows so far (sadface, c++ modules can't come fast enough)
#if defined (WIN32)
	#if defined (_MSC_VER)
		#pragma warning(disable: 4251)
	#endif
	#define  DEMO_EXPORT __declspec(dllexport)
	#define  DEMO_IMPORT __declspec(dllimport)
#else
	#define DEMO_EXPORT
#endif