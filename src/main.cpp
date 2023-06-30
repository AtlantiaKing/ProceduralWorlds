#include "Renderer/SDLWrapper.h"

// GENERATORS
#include "Generators/PerlinGenerator.h"
#include "Generators/Heightmap.h"

#include <chrono>
#include <thread>

int main()
{
	// Create an SDL object
	constexpr int width{ 640 };
	constexpr int height{ 480 };
	that::SDLWrapper sdl{ width, height };

	auto m_pGenerator{ std::make_unique<that::gen::Heightmap>(sdl) };

	// While the close button of the window isn't pressed
	while (sdl.HandleEvent())
	{
		// Draw the window + texture
		sdl.Draw();

		// Don't overdo the CPU
		constexpr std::chrono::milliseconds threadSleepTime{ 50 };
		std::this_thread::sleep_for(threadSleepTime);
	}
}