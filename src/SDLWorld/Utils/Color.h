#pragma once

#include <cstdint>

namespace sdlw
{
	struct Color final
	{
		constexpr Color() = default;
		constexpr Color(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a)
			: r{ static_cast<uint8_t>(_r) }
			, g{ static_cast<uint8_t>(_g) }
			, b{ static_cast<uint8_t>(_b) }
			, a{ static_cast<uint8_t>(_a) }
		{
		}
		constexpr Color(unsigned int _r, unsigned int _g, unsigned int _b)
			: r{ static_cast<uint8_t>(_r) }
			, g{ static_cast<uint8_t>(_g) }
			, b{ static_cast<uint8_t>(_b) }
			, a{ UINT8_MAX }
		{
		}

		uint8_t a{};
		uint8_t b{};
		uint8_t g{};
		uint8_t r{};
	};
}