/*
SDLEngine
Matt Hoyle
*/
#pragma once
#include <stdint.h>
#include <type_traits>

namespace Platform
{
	class AtomicInt32
	{
	public:
		AtomicInt32();
		AtomicInt32(int32_t initialValue);
		~AtomicInt32();

		int32_t Add(int32_t v);
		int32_t Set(int32_t v);
		bool CAS(int32_t oldVal, int32_t newVal);
		int32_t Get();

	private:
		// SDL stores atomics as structs, 
		// We do NOT want to expose SDL outside Platform, so use aligned_storage to hide the internals
		struct SDLInternals;	// This struct wraps the SDL_atomic_t object
		SDLInternals& GetInternal() { return reinterpret_cast<SDLInternals&>(m_storage); }
		const SDLInternals& GetInternal() const { return reinterpret_cast<const SDLInternals&>(m_storage); }
		static const size_t c_storageSize = 4;
		static const size_t c_storageAlign = 8;
		std::aligned_storage<c_storageSize, c_storageAlign>::type m_storage;
	};
}