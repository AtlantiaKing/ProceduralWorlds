#pragma once

#include "Generator.h"

namespace that
{
	class SDLWrapper;
}

namespace that::gen
{
	class PerlinGenerator final : public Generator
	{
	public:
		PerlinGenerator(SDLWrapper& sdl);
		~PerlinGenerator() = default;

	private:
		const int m_Octaves{ 1 };
		const float m_Zoom{ 50.0f };
	};
}
