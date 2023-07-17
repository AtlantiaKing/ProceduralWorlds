#include "BasicHeightmap.h"

#include "../Perlin/PerlinComposition.h"

that::height::BasicHeightmap::BasicHeightmap(unsigned int seed)
{
	// Reset the seed
	srand(seed);
	
	// Add octaves in the classic way (each octave gets multiplied by 1/index)
	for (int i{ 1 }; i <= m_Octaves; ++i)
	{
		m_Perlin.AddOctave(1.0f / i, m_Zoom);
	}
}

float that::height::BasicHeightmap::GetHeight(float x, float y) const
{
	return m_Perlin.GetNoise(x, y);
}

extern "C"
{
	THATWORLDS_API that::height::BasicHeightmap* that::height::BasicHeightmap_Create(unsigned int seed)
	{
		return new BasicHeightmap{ seed };
	}

	THATWORLDS_API void that::height::BasicHeightmap_Destroy(BasicHeightmap* pGenerator)
	{
		delete pGenerator;
	}

	THATWORLDS_API float that::height::BasicHeightmap_GetHeight(BasicHeightmap* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
