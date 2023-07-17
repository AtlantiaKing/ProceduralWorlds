#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "RiversGenerator.h"

#include "../Noise/PerlinComposition.h"

namespace that::river
{
	class BasicRivers final : public RiversGenerator
	{
	public:
		THATWORLDS_API BasicRivers(unsigned int seed);
		virtual ~BasicRivers() = default;

		virtual float THATWORLDS_API GetDepth(float x, float y) override;

	private:
		const int m_Octaves{ 3 };
		const float m_Zoom{ 30.0f };

		const float m_RiverLevel{ 0.5f };
		const float m_RiverSpread{ 0.05f };

		that::PerlinComposition m_Perlin{};
	};

	extern "C"
	{
		THATWORLDS_API BasicRivers* BasicRivers_Create(unsigned int seed);
		THATWORLDS_API void BasicRivers_Destroy(BasicRivers* pGenerator);
		THATWORLDS_API float BasicRivers_GetDepth(BasicRivers* pGenerator, float x, float y);
	}
}
