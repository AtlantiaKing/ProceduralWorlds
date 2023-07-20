#include "NoiseMap.h"

float that::NoiseMap::GetNoise(float x, float y) const
{
	return m_Graph.GetValue(m_Perlin.GetNoise(x, y));
}

that::PerlinComposition& that::NoiseMap::GetPerlin()
{
	return m_Perlin;
}

that::Graph& that::NoiseMap::GetGraph()
{
	return m_Graph;
}

extern "C"
{
	THATWORLDS_API that::NoiseMap* that::NoiseMap_Create()
	{
		return new NoiseMap();
	}

	THATWORLDS_API void that::NoiseMap_Destroy(NoiseMap* pNoiseMap)
	{
		delete pNoiseMap;
	}

	THATWORLDS_API float that::NoiseMap_GetNoise(NoiseMap* pNoiseMap, float x, float y)
	{
		return pNoiseMap->GetNoise(x, y);
	}

	THATWORLDS_API that::PerlinComposition* that::NoiseMap_GetPerlin(NoiseMap* pNoiseMap)
	{
		return &pNoiseMap->GetPerlin();
	}

	THATWORLDS_API that::Graph* that::NoiseMap_GetGraph(NoiseMap* pNoiseMap)
	{
		return &pNoiseMap->GetGraph();
	}
}
