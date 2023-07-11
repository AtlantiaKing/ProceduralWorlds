#pragma once

#include "Generator.h"

#include "../Structs/Color.h"

namespace that
{
	class SDLWrapper;
	class Perlin;
}

namespace that::gen
{
	class Heightmap final : public Generator
	{
	public:
		Heightmap(unsigned int seed);
		~Heightmap() = default;

		virtual void Activate(SDLWrapper& sdl) override;
		virtual void DrawImGui(SDLWrapper& sdl) override;

	private:
		void Draw(SDLWrapper& sdl) const;
		Color GetHeightColor(const Perlin& perlin, int x, int y) const;

		int m_Seed{};

		int m_Octaves{ 5 };
		float m_Zoom{ 50.0f };

		float m_SeaLevel{ 0.5f };

		// All these percentages are expressed in "amount above sea level"
		float m_LowLevel{ 0.1f }; // From what percentage does the color lerp to yellow
		float m_MiddleLevel{ 0.4f }; // This percentage is pure middle land color
		float m_HighLevel{ 0.45f }; // This percentage is pure high land color (is ceil level)

		const Color m_WaterColor{ 204, 243, 255 };
		const Color m_LowLandColor{ 138, 186, 125 };
		const Color m_MiddleLandColor{ 237, 230, 171 };
		const Color m_HighLandColor{ 166, 120, 112 };
	};
}

