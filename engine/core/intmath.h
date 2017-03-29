/*
DemoFramework
Matt Hoyle
*/
#pragma once

namespace Core
{
	template<class T>
	inline bool IsPowerOfTwo(const T v)
	{
		return v < 1 ? false : (v & (v - 1)) == 0;
	}

	// Alignment must be power-of-two
	template<class T>
	inline T AlignUp(const T value, const T alignment)
	{
		return (value + alignment - 1) & ~(alignment - 1);
	}

	template<class T>
	inline T Max(const T t0, const T t1)
	{
		return t0 > t1 ? t0 : t1;
	}

	template<class T>
	inline T Min(const T t0, const T t1)
	{
		return t0 < t1 ? t0 : t1;
	}
}