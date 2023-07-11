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
		PerlinGenerator(unsigned int seed, SDLWrapper& sdl);
		~PerlinGenerator() = default;

		virtual void DrawImGui(SDLWrapper& sdl) override;

	private:
		void Draw(SDLWrapper& sdl) const;

		int m_Seed{};
		int m_Octaves{ 1 };
		float m_Zoom{ 50.0f };
	};
}
