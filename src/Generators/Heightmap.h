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

		const int m_Octaves{ 6 };
		const float m_Zoom{ 250.0f };

		const float m_SeaLevel{ 0.5f };
		const float m_BeachLevel{ 0.04f };
	};
}

