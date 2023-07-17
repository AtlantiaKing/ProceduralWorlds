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
	class BasicHeightmap final : public HeightmapGenerator
	{
	public:
		THATWORLDS_API BasicHeightmap(unsigned int seed);
		~BasicHeightmap() = default;

		virtual float THATWORLDS_API GetHeight(float x, float y) const override;

	private:
		const int m_Octaves{ 5 };
		const float m_Zoom{ 50.0f };

		that::PerlinComposition m_Perlin{};
	};

	extern "C"
	{
		THATWORLDS_API BasicHeightmap* BasicHeightmap_Create(unsigned int seed);
		THATWORLDS_API void BasicHeightmap_Destroy(BasicHeightmap* pGenerator);
		THATWORLDS_API float BasicHeightmap_GetHeight(BasicHeightmap* pGenerator, float x, float y);
	}
}

