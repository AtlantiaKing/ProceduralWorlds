#pragma once

#include <cstdint>

namespace that
{
	struct Color final
	{
		Color() = default;
		Color(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a)
			: r{ static_cast<uint8_t>(_r) }
			, g{ static_cast<uint8_t>(_g) }
			, b{ static_cast<uint8_t>(_b) }
			, a{ static_cast<uint8_t>(_a) }
		{
		}
		Color(unsigned int _r, unsigned int _g, unsigned int _b)
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