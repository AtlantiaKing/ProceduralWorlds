// Third party wrappers
#include "Renderer/SDLWrapper.h"

// STD includes
#include <chrono>
#include <thread>
#include <iostream>
#include <map>
#include <string>

#include <Noise/Graph.h>
#include <Noise/NoiseMap.h>

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

	that::NoiseMap noise{};

	that::PerlinComposition& perlin{ noise.GetPerlin() };
	const float zoom{ 400.0f };
	perlin.AddOctave(1.0f, zoom);
	perlin.AddOctave(0.5f, zoom);
	perlin.AddOctave(0.333f, zoom);
	perlin.AddOctave(0.25f, zoom);

	that::Graph& graph{ noise.GetGraph() };
	graph.AddNode(0.0f, 0.2f);
	graph.AddNode(0.6f, 0.5f);
	graph.AddNode(0.65f, 0.9f);
	graph.AddNode(1.0f, 1.0f);

	float lowest = 1.0f;
	float highest = 0.0f;

	const int mapSize{ 200 };
	const int distanceBetweenMaps{ 10 };

	for (int x{}; x < mapSize; ++x)
	{
		for (int y{}; y < mapSize; ++y)
		{
			const float perlinValue{ perlin.GetNoise(static_cast<float>(x), static_cast<float>(y)) };

			if (perlinValue < lowest) lowest = perlinValue;
			if (perlinValue > highest) highest = perlinValue;

			const unsigned int perlinColor{ static_cast<unsigned int>(perlinValue * UINT8_MAX) };

			sdl.DrawPixel({ x + mapSize + distanceBetweenMaps, y }, { perlinColor,perlinColor,perlinColor });

			const float noiseValue{ noise.GetNoise(static_cast<float>(x), static_cast<float>(y)) };

			const unsigned int color{ static_cast<unsigned int>(noiseValue * UINT8_MAX) };

			sdl.DrawPixel({ x, y }, { color,color,color });
		}
	}

	std::cout << "highest perlin = " << highest << "\n";
	std::cout << "lowest perlin = " << lowest << "\n";

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