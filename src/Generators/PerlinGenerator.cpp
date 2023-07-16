#include "PerlinGenerator.h"

#include "../Renderer/SDLWrapper.h"
#include "../Perlin/PerlinComposition.h"

#include <imgui.h>

that::gen::PerlinGenerator::PerlinGenerator(unsigned int seed)
	: m_Seed{ static_cast<int>(seed) }
{
}

void that::gen::PerlinGenerator::Activate(SDLWrapper& sdl)
{
	Draw(sdl);
}

void that::gen::PerlinGenerator::DrawImGui(SDLWrapper& sdl)
{
	bool openState{ false };
	ImGui::Begin("Perlin Settings", &openState);
	if (ImGui::InputInt("Current seed", &m_Seed)) Draw(sdl);
	if (ImGui::InputInt("Nr Octaves", &m_Octaves)) Draw(sdl);
	if (ImGui::InputFloat("Zoom level", &m_Zoom)) Draw(sdl);
	ImGui::End();
}

void that::gen::PerlinGenerator::Draw(SDLWrapper& sdl) const
{
	srand(m_Seed);

	const auto& windowSize{ sdl.GetWindowSize() };
	that::PerlinComposition perlin{};
	for (int i{ 1 }; i <= m_Octaves; ++i)
	{
		perlin.AddOctave(1.0f / i, m_Zoom);
	}

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
