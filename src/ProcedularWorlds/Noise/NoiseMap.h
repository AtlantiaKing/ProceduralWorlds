#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "PerlinComposition.h"
#include "Graph.h"

namespace that
{
	class NoiseMap final
	{
	public:
		NoiseMap() = default;
		~NoiseMap() = default;

		THATWORLDS_API float GetNoise(float x, float y) const;

		THATWORLDS_API PerlinComposition& GetPerlin();
		THATWORLDS_API Graph& GetGraph();

	private:
		PerlinComposition m_Perlin{};
		Graph m_Graph{};
	};

	extern "C"
	{
		THATWORLDS_API NoiseMap* NoiseMap_Create();
		THATWORLDS_API void NoiseMap_Destroy(NoiseMap* pNoiseMap);
		THATWORLDS_API float NoiseMap_GetNoise(NoiseMap* pNoiseMap, float x, float y);
		THATWORLDS_API PerlinComposition* NoiseMap_GetPerlin(NoiseMap* pNoiseMap);
		THATWORLDS_API Graph* NoiseMap_GetGraph(NoiseMap* pNoiseMap);
	}
}