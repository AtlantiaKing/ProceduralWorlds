#include "PerlinGenerator.h"

#include "../Renderer/SDLWrapper.h"
#include "../Perlin/Perlin.h"

#include <imgui.h>

that::gen::PerlinGenerator::PerlinGenerator(unsigned int seed, SDLWrapper& sdl)
	: m_Seed{ static_cast<int>(seed) }
{
	Draw(sdl);
}

void that::gen::PerlinGenerator::DrawImGui(SDLWrapper& sdl)
{
	ImGui::Begin("Perlin Settings");
	if (ImGui::InputInt("Current seed", &m_Seed)) Draw(sdl);
	if (ImGui::InputInt("Nr Octaves", &m_Octaves)) Draw(sdl);
	if (ImGui::InputFloat("Zoom level", &m_Zoom)) Draw(sdl);
	ImGui::End();
}

void that::gen::PerlinGenerator::Draw(SDLWrapper& sdl) const
{
	srand(m_Seed);

	const auto& windowSize{ sdl.GetWindowSize() };
	that::Perlin perlin{ m_Octaves, m_Zoom };

	for (int x{}; x < windowSize.x; ++x)
	{
		for (int y{}; y < windowSize.y; ++y)
		{
			const float perlinValue{ perlin.GetNoise(x,y) };
			const unsigned int perlinColor{ static_cast<unsigned int>(perlinValue * UINT8_MAX) };

			sdl.DrawPixel({ x,y }, that::Color{ perlinColor, perlinColor, perlinColor });
		}
	}
}
