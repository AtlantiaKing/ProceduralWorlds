#include "Generator.h"

#include "Heightmap/HeightmapGenerator.h"

void that::Generator::SetScale(float scale)
{
	m_Scale = scale;
}

float that::Generator::GetScale() const
{
	return m_Scale;
}

void that::Generator::SetRiverDepth(float depth)
{
	m_RiverDepth = depth;
}

void that::Generator::SetRiverSmoothing(float smoothStep)
{
	m_RiverSmoothStep = smoothStep;
}

void that::Generator::SetHeightmapGenerator(height::HeightmapGenerator* pGenerator)
{
	// Store the given pointer in a unique pointer
	std::unique_ptr<height::HeightmapGenerator> pUniqueGenerator{ pGenerator };
	m_pHeightGenerator = std::move(pUniqueGenerator);
}

void that::Generator::SetRiversGenerator(river::RiversGenerator* pGenerator)
{
	// Store the given pointer in a unique pointer
	std::unique_ptr<river::RiversGenerator> pUniqueGenerator{ pGenerator };
	m_pRiversGenerator = std::move(pUniqueGenerator);
}

float that::Generator::GetHeight(float x, float y) const
{
	x /= m_Scale;
	y /= m_Scale;

	const float heightmap{ m_pHeightGenerator->GetHeight(x, y) };
	const float rivermap{ m_pRiversGenerator->GetDepth(x, y) };

	// Use the formula (x-1)^t + 1 with t being m_RiverSmoothStep
	// This will create a better transition between land and rivers
	const float smoothedRivermap{ powf(rivermap - 1.0f, m_RiverSmoothStep) + 1.0f };

	return m_RiverDepth + (heightmap - m_RiverDepth) * smoothedRivermap;
}

extern "C"
{
	THATWORLDS_API that::Generator* that::Generator_Create()
	{
		return new that::Generator{};
	}

	THATWORLDS_API void that::Generator_Destroy(Generator* pGenerator)
	{
		delete pGenerator;
	}

	THATWORLDS_API void that::Generator_SetScale(Generator* pGenerator, float scale)
	{
		pGenerator->SetScale(scale);
	}

	THATWORLDS_API float that::Generator_GetScale(Generator* pGenerator)
	{
		return pGenerator->GetScale();
	}

	THATWORLDS_API void that::Generator_SetRiverDepth(Generator* pGenerator, float depth)
	{
		pGenerator->SetRiverDepth(depth);
	}

	THATWORLDS_API void that::Generator_SetRiverSmoothing(Generator* pGenerator, float smoothPower)
	{
		pGenerator->SetRiverSmoothing(smoothPower);
	}

	THATWORLDS_API void that::Generator_SetHeightmapGenerator(Generator* pGenerator, height::HeightmapGenerator* pHeightmapGenerator)
	{
		pGenerator->SetHeightmapGenerator(pHeightmapGenerator);
	}

	THATWORLDS_API void that::Generator_SetRiversGenerator(Generator* pGenerator, river::RiversGenerator* pRiversGenerator)
	{
		pGenerator->SetRiversGenerator(pRiversGenerator);
	}

	THATWORLDS_API float that::Generator_GetHeight(Generator* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
