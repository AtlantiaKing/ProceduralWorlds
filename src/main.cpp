// Third party wrappers
#include "Renderer/SDLWrapper.h"
#include "ImGui/ImGuiWrapper.h"

#include <imgui.h>

// GENERATORS
#include "Generators/PerlinGenerator.h"
#include "Generators/Heightmap.h"

// STD includes
#include <chrono>
#include <thread>
#include <iostream>

int main()
{
	const unsigned int seed{ static_cast<unsigned int>(time(nullptr)) };
	srand(seed);
	std::cout << "Current seed: " << seed << "\n";

	// Create an SDL object
	constexpr int width{ 640 };
	constexpr int height{ 480 };
	that::SDLWrapper sdl{ width, height };
	that::ImGuiWrapper imgui{ sdl.GetWindow(), sdl.GetRenderer() };

	auto pGenerator{ std::make_unique<that::gen::Heightmap>(seed, sdl) };

	// While the close button of the window isn't pressed
	while (sdl.HandleEvent(imgui))
	{
		imgui.BeginDraw();

		// ImGui draw calls
		pGenerator->DrawImGui(sdl);
		imgui.Draw();

		// SDL draw calls
		sdl.DrawClearColor();
		sdl.DrawTexture();

		// Draw the window
		imgui.EndDraw();
		sdl.SwapBuffer();

		// Don't overdo the CPU
		constexpr std::chrono::milliseconds threadSleepTime{ 50 };
		std::this_thread::sleep_for(threadSleepTime);
	}
}