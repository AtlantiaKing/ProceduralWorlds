#include "HeightMap.h"

void that::HeightMap::AddNoiseMap(const NoiseMap& noiseMap)
{
	m_NoiseMaps.push_back(noiseMap);
}

float that::HeightMap::GetHeight(float x, float y) const
{
	// The default height should be 1 if the blendmode is set to Multiply, 
	//	otherwise all multiplications will be ignored
	float height{ m_BlendMode == BlendMode::Multiply ? 1.0f : 0.0f };

	// Generate the height for this coordinate using the appropriate blend mode
	for (const NoiseMap& noiseMap : m_NoiseMaps)
	{
		const float noise{ noiseMap.GetNoise(x, y) };

		switch (m_BlendMode)
		{
		case BlendMode::Multiply:
			height *= noise;
			break;
		case BlendMode::Add:
		case BlendMode::Average:
			height += noise;
			break;
		}
	}

	// Calculate the average if all the noise maps if the BlendMode is set to Average
	if (m_BlendMode == BlendMode::Average)
	{
		height /= static_cast<int>(m_NoiseMaps.size());
	}

	return height;
}

extern "C"
{
	THATWORLDS_API void that::HeightMap::SetBlendMode(BlendMode blendMode)
	{
		m_BlendMode = blendMode;
	}

	THATWORLDS_API that::HeightMap* that::HeightMap_Create()
	{
		return new HeightMap{};
	}

	THATWORLDS_API void that::HeightMap_Destroy(HeightMap* pHeightMap)
	{
		delete pHeightMap;
	}

	THATWORLDS_API void that::HeightMap_AddNoiseMap(HeightMap* pHeightMap, NoiseMap* pNoiseMap)
	{
		pHeightMap->AddNoiseMap(*pNoiseMap);
	}

	THATWORLDS_API float that::HeightMap_GetHeight(HeightMap* pHeightMap, float x, float y)
	{
		return pHeightMap->GetHeight(x, y);
	}

	THATWORLDS_API void that::HeightMap_SetBlendMode(HeightMap* pHeightMap, int blendMode)
	{
		pHeightMap->SetBlendMode(static_cast<HeightMap::BlendMode>(blendMode));
	}
}
