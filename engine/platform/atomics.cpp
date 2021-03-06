/*
DemoFramework
Matt Hoyle
*/
#include "atomics.h"
#include <SDL_atomic.h>

namespace Platform
{
	struct AtomicInt32::SDLInternals
	{
		SDL_atomic_t m_atomic;
	};

	AtomicInt32::AtomicInt32()
	{
		static_assert(c_storageSize >= sizeof(SDLInternals), "c_storageSize not big enough for this platform");
		static_assert(c_storageAlign >= alignof(SDLInternals), "c_storageAlign not big enough for this platform");
		Set(0);
	}

	AtomicInt32::AtomicInt32(int32_t initialValue)
	{
		Set(initialValue);
	}

	AtomicInt32::~AtomicInt32()
	{
	}

	bool AtomicInt32::CAS(int32_t oldVal, int32_t newVal)
	{
		return SDL_AtomicCAS(&GetInternal().m_atomic, oldVal, newVal) != 0 ? true : false;
	}

	int32_t AtomicInt32::Add(int32_t v)
	{
		return SDL_AtomicAdd(&GetInternal().m_atomic, v);
	}

	int32_t AtomicInt32::Set(int32_t v)
	{
		return SDL_AtomicSet(&GetInternal().m_atomic, v);
	}

	int32_t AtomicInt32::Get() const
	{
		return SDL_AtomicGet(&const_cast< SDL_atomic_t& >( GetInternal().m_atomic ));
	}
}