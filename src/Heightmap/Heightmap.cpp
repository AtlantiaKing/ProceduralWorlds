#include "Heightmap.h"

#include "../Perlin/PerlinComposition.h"

#include <imgui.h>

that::height::Heightmap::Heightmap(unsigned int seed)
{
	// Reset the seed
	srand(seed);
	
	// Add octaves in the classic way (each octave gets multiplied by 1/index)
	for (int i{ 1 }; i <= m_Octaves; ++i)
	{
		m_Perlin.AddOctave(1.0f / i, m_Zoom);
	}
}

float that::height::Heightmap::GetHeight(float x, float y) const
{
	return m_Perlin.GetNoise(x, y);
}

extern "C"
{
	THATWORLDS_API that::height::Heightmap* that::height::Heightmap_Create(unsigned int seed)
	{
		return new Heightmap{ seed };
	}

	THATWORLDS_API void that::height::Heightmap_Destroy(Heightmap* pGenerator)
	{
		delete pGenerator;
	}

	THATWORLDS_API float that::height::Heightmap_GetHeight(Heightmap* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
