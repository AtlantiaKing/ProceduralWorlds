#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "HeightmapGenerator.h"

#include "../Perlin/PerlinComposition.h"

namespace that::height
{
	class Heightmap final : public HeightmapGenerator
	{
	public:
		THATWORLDS_API Heightmap(unsigned int seed);
		~Heightmap() = default;

		virtual float THATWORLDS_API GetHeight(float x, float y) const override;

	private:
		const int m_Octaves{ 5 };
		const float m_Zoom{ 50.0f };

		that::PerlinComposition m_Perlin{};
	};

	extern "C"
	{
		THATWORLDS_API Heightmap* Heightmap_Create(unsigned int seed);
		THATWORLDS_API void Heightmap_Destroy(Heightmap* pGenerator);
		THATWORLDS_API float Heightmap_GetHeight(Heightmap* pGenerator, float x, float y);
	}
}

