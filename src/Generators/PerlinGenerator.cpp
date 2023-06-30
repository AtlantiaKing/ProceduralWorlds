#include "PerlinGenerator.h"

#include "../Renderer/SDLWrapper.h"
#include "../Perlin/Perlin.h"

that::gen::PerlinGenerator::PerlinGenerator(SDLWrapper& sdl)
{
	const auto& windowSize{ sdl.GetWindowSize() };

	that::Perlin perlin{ m_Octaves, m_Zoom };
	for (int x{}; x < windowSize.x; ++x)
	{
		for (int y{}; y < windowSize.y; ++y)
		{
			const float perlinValue{ perlin.GetNoise(x,y)};
			const unsigned int perlinColor{ static_cast<unsigned int>(perlinValue * 255) };

			sdl.DrawPixel({ x,y }, that::Color{ perlinColor, perlinColor, perlinColor });
		}
	}
}
