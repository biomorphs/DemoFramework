/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include <stdint.h>

namespace Core
{
	class StringHashing
	{
	public:

		static const uint32_t EmptyHash = 5381;

		// djb2 hash
		static inline uint32_t GetHash(const char* str)
		{
			uint32_t hash = EmptyHash;

			int c = 0;
			while ((str != nullptr) && (c = *str++))
			{
				hash = ((hash << 5) + hash) + c;
			}

			return hash;
		}
	};
}