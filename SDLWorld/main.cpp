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
#include <Heightmap/HeightMap.h>

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

	// Create continental noise map
	that::NoiseMap continentalNoise{};

	that::PerlinComposition& continentalPerlin{ continentalNoise.GetPerlin() };
	const float continentalZoom{ 50.0f };
	continentalPerlin.AddOctave(1.0f, continentalZoom);
	continentalPerlin.AddOctave(0.5f, continentalZoom);
	continentalPerlin.AddOctave(0.333f, continentalZoom);
	continentalPerlin.AddOctave(0.25f, continentalZoom);

	that::Graph& continentalGraph{ continentalNoise.GetGraph() };
	continentalGraph.AddNode(0.0f, 1.0f);
	continentalGraph.AddNode(0.1f, 0.2f);
	continentalGraph.AddNode(0.4f, 0.25f);
	continentalGraph.AddNode(0.45f, 0.4f);
	continentalGraph.AddNode(0.55f, 0.45f);
	continentalGraph.AddNode(0.6f, 0.85f);
	continentalGraph.AddNode(1.0f, 1.0f);

	// Create erosion noise map
	that::NoiseMap erosionNoise{};

	that::PerlinComposition& erosionPerlin{ erosionNoise.GetPerlin() };
	const float erosionZoom{ 100.0f };
	erosionPerlin.AddOctave(1.0f, erosionZoom);
	erosionPerlin.AddOctave(0.5f, erosionZoom);

	that::Graph& erosionGraph{ erosionNoise.GetGraph() };
	erosionGraph.AddNode(0.0f, 1.0f);
	erosionGraph.AddNode(0.1f, 0.8f);
	erosionGraph.AddNode(0.25f, 0.5f);
	erosionGraph.AddNode(0.3f, 0.55f);
	erosionGraph.AddNode(0.5f, 0.25f);
	erosionGraph.AddNode(0.6f, 0.2f);
	erosionGraph.AddNode(0.63f, 0.4f);
	erosionGraph.AddNode(0.73f, 0.45f);
	erosionGraph.AddNode(0.76f, 0.2f);
	erosionGraph.AddNode(1.0f, 0.1f);

	// Create peaks and valleys noise map
	that::NoiseMap pvNoise{};

	that::PerlinComposition& pvPerlin{ pvNoise.GetPerlin() };
	const float pvZoom{ 20.0f };
	pvPerlin.AddOctave(1.0f, pvZoom);
	pvPerlin.AddOctave(0.5f, pvZoom);
	pvPerlin.AddOctave(0.333f, pvZoom);
	pvPerlin.AddOctave(0.25f, pvZoom);

	that::Graph& pvGraph{ pvNoise.GetGraph() };
	pvGraph.AddNode(0.0f, 0.0f);
	pvGraph.AddNode(0.2f, 0.2f);
	pvGraph.AddNode(0.4f, 0.35f);
	pvGraph.AddNode(0.5f, 0.4f);
	pvGraph.AddNode(0.6f, 0.7f);
	pvGraph.AddNode(0.75f, 0.85f);
	pvGraph.AddNode(0.9f, 0.7f);
	pvGraph.AddNode(1.0f, 0.7f);

	// Create heightmap
	that::HeightMap heightMap{};
	heightMap.AddNoiseMap(continentalNoise);
	heightMap.AddNoiseMap(erosionNoise);
	heightMap.AddNoiseMap(pvNoise);

	heightMap.SetBlendMode(that::HeightMap::BlendMode::Average);

	// Draw world
	constexpr int mapSize{ 400 };
	for (int x{}; x < mapSize; ++x)
	{
		for (int y{}; y < mapSize; ++y)
		{
			const float noiseValue{ heightMap.GetHeight(static_cast<float>(x), static_cast<float>(y)) };

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