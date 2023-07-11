#pragma once

namespace that
{
	class SDLWrapper;
}

namespace that::gen
{
	class Generator
	{
	public:
		virtual ~Generator() = default;

		virtual void DrawImGui(SDLWrapper& sdl) = 0;
	};
}