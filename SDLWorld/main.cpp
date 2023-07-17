// Third party wrappers
#include "Renderer/SDLWrapper.h"

// STD includes
#include <chrono>
#include <thread>
#include <iostream>
#include <map>
#include <string>

#include <Generator.h>
#include <Heightmap/BasicHeightmap.h>

float g_SeaLevel{ 0.5f };

float g_LowLevel{ 0.1f };
float g_MiddleLevel{ 0.2f };
float g_HighLevel{ 0.3f};

const sdlw::Color g_LowLandColor{ 138, 186, 125 };
const sdlw::Color g_MiddleLandColor{ 237, 230, 171 };
const sdlw::Color g_HighLandColor{ 166, 120, 112 };

sdlw::Color GetHeightColor(const that::Generator& generator, int x, int y)
{
	// Retrieve the perlin value
	const float perlinValue{ generator.GetHeight(static_cast<float>(x), static_cast<float>(y)) };

	// Draw nothing if this position is underneath sea level
	if (perlinValue < g_SeaLevel)
	{
		return {};
	}

	// Calculate the percentage above sealevel
	const float aboveSeaHeight{ 1.0f - g_SeaLevel };
	const float perlinContinental{ (perlinValue - g_SeaLevel) / aboveSeaHeight };

	// Return the appropriate color depending on the height of this position
	if (perlinContinental < g_LowLevel)
	{
		return g_LowLandColor;
	}
	else if (perlinContinental < g_MiddleLevel)
	{
		// Calculate the percentage where the perlin is between low level and middle level
		const float lowPerlin{ (perlinContinental - g_LowLevel) / (g_MiddleLevel - g_LowLevel) };

		// Lerp from low land color to middle land color
		return sdlw::Color
		{
			static_cast<unsigned int>(g_LowLandColor.r + (g_MiddleLandColor.r - g_LowLandColor.r) * lowPerlin),
			static_cast<unsigned int>(g_LowLandColor.g + (g_MiddleLandColor.g - g_LowLandColor.g) * lowPerlin),
			static_cast<unsigned int>(g_LowLandColor.b + (g_MiddleLandColor.b - g_LowLandColor.b) * lowPerlin)
		};
	}
	else
	{
		// Calculate the percentage where the perlin is between middle and high level
		//		and clamp the percentage at 100%
		const float highPerlin{ std::min((perlinContinental - g_MiddleLevel) / (g_HighLevel - g_MiddleLevel), 1.0f) };

		// Lerp from middle land color to high land color
		return sdlw::Color
		{
			static_cast<unsigned int>(g_MiddleLandColor.r + (g_HighLandColor.r - g_MiddleLandColor.r) * highPerlin),
			static_cast<unsigned int>(g_MiddleLandColor.g + (g_HighLandColor.g - g_MiddleLandColor.g) * highPerlin),
			static_cast<unsigned int>(g_MiddleLandColor.b + (g_HighLandColor.b - g_MiddleLandColor.b) * highPerlin)
		};
	}
}

int main()
{
	// Calculate a new seed
	const unsigned int seed{ static_cast<unsigned int>(time(nullptr)) };
	srand(seed);
	std::cout << "Current seed: " << seed << "\n";

	// Create an SDL object
	constexpr int width{ 640 };
	constexpr int height{ 480 };
	sdlw::SDLWrapper sdl{ width, height };

	// Create a generator
	that::Generator generator{};
	generator.SetScale(2.0f);
	generator.SetHeightmapGenerator(new that::height::BasicHeightmap{ seed });

	// Draw the world
	for (int x{}; x < width; ++x)
	{
		for (int y{}; y < height; ++y)
		{
			sdl.DrawPixel({ x,y }, GetHeightColor(generator, x, y));
		}
	}

	// While the close button of the window isn't pressed
	while (sdl.HandleEvent())
	{
		// SDL draw calls
		sdl.DrawClearColor();
		sdl.DrawTexture();

		// Draw the window
		sdl.SwapBuffer();

		// Don't overdo the CPU
		constexpr std::chrono::milliseconds threadSleepTime{ 50 };
		std::this_thread::sleep_for(threadSleepTime);
	}
}