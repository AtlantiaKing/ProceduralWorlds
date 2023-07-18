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

#include <WorldShape/CirclePeak.h>
#include <WorldShape/SquarePeak.h>

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

	// Create generator
	constexpr float mapSize{ 400.0f };
	const float mapZoom{ 2.0f };
	that::Generator gen{};
	gen.SetSize(mapSize);
	//gen.SetShape(std::make_unique<that::shape::CirclePeak>(4.0f));
	gen.SetShape(std::make_unique<that::shape::SquarePeak>(6.0f, 4.0f));
	that::preset::Presets::CreateDefaultTerrain(gen, seed, mapZoom);

	// Test if there is a jump of 0.15 in height somewhere in the map over steps of 5
	gen.AddPredicate(that::SuccessPredicate{ [](float height0, float height1) -> bool { return abs(height0 - height1) > 0.15f; } });
	std::cout << "Valid world: " << gen.TryPredicates(5) << "\n";

	// Draw world
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