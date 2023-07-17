#include "BasicRivers.h"

that::river::BasicRivers::BasicRivers(unsigned int seed)
{
	// Reset the seed
	srand(seed);

	// Add octaves in the classic way (each octave gets multiplied by 1/index)
	for (int i{ 1 }; i <= m_Octaves; ++i)
	{
		m_Perlin.AddOctave(1.0f / i, m_Zoom);
	}
}

float that::river::BasicRivers::GetDepth(float x, float y)
{
	const float perlinValue{ m_Perlin.GetNoise(x, y) };

	if (perlinValue < m_RiverLevel - m_RiverSpread || perlinValue > m_RiverLevel + m_RiverSpread)
	{
		return 1.0f;
	}

	const float riverValue = abs(perlinValue - m_RiverLevel) / m_RiverSpread;

	return riverValue;
}

extern "C"
{
	THATWORLDS_API that::river::BasicRivers* that::river::BasicRivers_Create(unsigned int seed)
	{
		return new BasicRivers{ seed };
	}

	THATWORLDS_API void that::river::BasicRivers_Destroy(BasicRivers* pGenerator)
	{
		delete pGenerator;
	}

	THATWORLDS_API float that::river::BasicRivers_GetDepth(BasicRivers* pGenerator, float x, float y)
	{
		return pGenerator->GetDepth(x, y);
	}
}
