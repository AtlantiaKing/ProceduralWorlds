#include "Heightmap.h"

#include "../Renderer/SDLWrapper.h"
#include "../Perlin/Perlin.h"

that::gen::Heightmap::Heightmap(that::SDLWrapper& sdl)
{
	const auto& windowSize{ sdl.GetWindowSize() };

	that::Perlin perlin{ m_Octaves, m_Zoom };
	for (int x{}; x < windowSize.x; ++x)
	{
		for (int y{}; y < windowSize.y; ++y)
		{
			const float perlinValue{ perlin.GetNoise(x, y) };
			const Color heightMapColor{ GetHeightColor(perlinValue) };

			sdl.DrawPixel({ x,y }, heightMapColor);
		}
	}
}

that::Color that::gen::Heightmap::GetHeightColor(float perlinValue) const
{
	if (perlinValue < m_SeaLevel)
	{
		return Color{ 0, 0, static_cast<unsigned int>(perlinValue / m_SeaLevel * UINT8_MAX) };
	}
	
	const float beachHeight{ m_SeaLevel + m_BeachLevel };
	if (perlinValue < beachHeight)
	{
		return Color{ 200, 200, 0 };
	}

	const float aboveBeachHeight{ 1.0f - beachHeight };
	const float perlinContinental{ (perlinValue - beachHeight) / aboveBeachHeight };

	constexpr int greenBase{ 150 };
	return Color
	{
		0,
		static_cast<unsigned int>(greenBase - (UINT8_MAX - greenBase) * perlinContinental),
		0
	};
}
