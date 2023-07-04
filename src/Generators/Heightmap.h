#pragma once

#include "Generator.h"

#include "../Structs/Color.h"

namespace that
{
	class SDLWrapper;
}

namespace that::gen
{
	class Heightmap final : public Generator
	{
	public:
		Heightmap(SDLWrapper& sdl);
		~Heightmap() = default;

	private:
		Color GetHeightColor(float perlinValue) const;

		const int m_Octaves{ 5 };
		const float m_Zoom{ 50.0f };

		const float m_SeaLevel{ 0.5f };

		// All these percentages are expressed in "amount above sea level"
		const float m_LowLevel{ 0.1f }; // From what percentage does the color lerp to yellow
		const float m_MiddleLevel{ 0.4f }; // This percentage is pure middle land color
		const float m_HighLevel{ 0.45f }; // This percentage is pure high land color (is ceil level)

		const Color m_WaterColor{ 204, 243, 255 };
		const Color m_LowLandColor{ 138, 186, 125 };
		const Color m_MiddleLandColor{ 237, 230, 171 };
		const Color m_HighLandColor{ 166, 120, 112 };
	};
}

