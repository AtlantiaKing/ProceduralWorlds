#include "Heightmap.h"

#include "../Renderer/SDLWrapper.h"
#include "../Perlin/PerlinComposition.h"

#include <imgui.h>

that::gen::Heightmap::Heightmap(unsigned int seed)
	: m_Seed{ static_cast<int>(seed) }
{
}

void that::gen::Heightmap::Activate(SDLWrapper& sdl)
{
	Draw(sdl);
}

void that::gen::Heightmap::DrawImGui(SDLWrapper& sdl)
{
	bool openState{ false };
	ImGui::Begin("Heightmap Settings", &openState);
	ImGui::Text("Perlin Settings");
	if (ImGui::InputInt("Current seed", &m_Seed)) Draw(sdl);
	if (ImGui::InputInt("Nr Octaves", &m_Octaves)) Draw(sdl);
	if (ImGui::InputFloat("Zoom level", &m_Zoom)) Draw(sdl);
	ImGui::Text("Map Settings");
	if (ImGui::InputFloat("Sealevel", &m_SeaLevel)) Draw(sdl);
	if (ImGui::InputFloat("Lowlands level", &m_LowLevel)) Draw(sdl);
	if (ImGui::InputFloat("Middlelands level", &m_MiddleLevel)) Draw(sdl);
	if (ImGui::InputFloat("Highlands level", &m_HighLevel)) Draw(sdl);
	ImGui::End();
}

void that::gen::Heightmap::Draw(SDLWrapper& sdl) const
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
			const Color heightMapColor{ GetHeightColor(perlin, x,y) };

			sdl.DrawPixel({ x,y }, heightMapColor);
		}
	}
}

that::Color that::gen::Heightmap::GetHeightColor(const PerlinComposition& OctavedPerlin, int x, int y) const
{
	const float perlinValue{ OctavedPerlin.GetNoise(x, y) };

	if (perlinValue < m_SeaLevel)
	{
		return m_WaterColor;
	}

	// Calculate the percentage above sealevel
	const float aboveSeaHeight{ 1.0f - m_SeaLevel };
	const float perlinContinental{ (perlinValue - m_SeaLevel) / aboveSeaHeight };

	if (perlinContinental < m_LowLevel)
	{
		return m_LowLandColor;
	}
	else if (perlinContinental < m_MiddleLevel)
	{
		// Calculate the percentage where the perlin is between low level and middle level
		const float lowPerlin{ (perlinContinental - m_LowLevel) / (m_MiddleLevel - m_LowLevel) };

		// Lerp from low land color to middle land color
		return Color
		{
			static_cast<unsigned int>(m_LowLandColor.r + (m_MiddleLandColor.r - m_LowLandColor.r) * lowPerlin),
			static_cast<unsigned int>(m_LowLandColor.g + (m_MiddleLandColor.g - m_LowLandColor.g) * lowPerlin),
			static_cast<unsigned int>(m_LowLandColor.b + (m_MiddleLandColor.b - m_LowLandColor.b) * lowPerlin)
		};
	}
	else
	{
		// Calculate the percentage where the perlin is between middle and high level
		//		and clamp the percentage at 100%
		const float highPerlin{ std::min((perlinContinental - m_MiddleLevel) / (m_HighLevel - m_MiddleLevel), 1.0f) };

		// Lerp from middle land color to high land color
		return Color
		{
			static_cast<unsigned int>(m_MiddleLandColor.r + (m_HighLandColor.r - m_MiddleLandColor.r) * highPerlin),
			static_cast<unsigned int>(m_MiddleLandColor.g + (m_HighLandColor.g - m_MiddleLandColor.g) * highPerlin),
			static_cast<unsigned int>(m_MiddleLandColor.b + (m_HighLandColor.b - m_MiddleLandColor.b) * highPerlin)
		};
	}
}
