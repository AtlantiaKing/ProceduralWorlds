// Third party wrappers
#include "Renderer/SDLWrapper.h"

// STD includes
#include <chrono>
#include <thread>
#include <iostream>
#include <map>
#include <string>

#include <Generator.h>
#include <Presets/Presets.h>

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

	that::Generator gen{};

	const float mapZoom{ 2.0f };
	that::preset::Presets::CreateDefaultTerrain(gen, mapZoom);

	// Draw world
	constexpr int mapSize{ 400 };
	for (int x{}; x < mapSize; ++x)
	{
		for (int y{}; y < mapSize; ++y)
		{
			const float noiseValue{ gen.GetHeight(static_cast<float>(x), static_cast<float>(y)) };

			const unsigned int colorValue{ static_cast<unsigned int>(noiseValue * UINT8_MAX) };

			sdl.DrawPixel({ x, y }, { colorValue, colorValue, colorValue });
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