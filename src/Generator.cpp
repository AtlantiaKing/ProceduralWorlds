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

void that::Generator::SetHeightmapGenerator(height::HeightmapGenerator* pGenerator)
{
	// Store the given pointer in a unique pointer
	std::unique_ptr<height::HeightmapGenerator> pUniqueGenerator{ pGenerator };
	m_pHeightGenerator = std::move(pUniqueGenerator);
}

float that::Generator::GetHeight(float x, float y) const
{
	return m_pHeightGenerator->GetHeight(x / m_Scale, y / m_Scale);
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

	void that::Generator_SetScale(Generator* pGenerator, float scale)
	{
		pGenerator->SetScale(scale);
	}

	float that::Generator_GetScale(Generator* pGenerator)
	{
		return pGenerator->GetScale();
	}

	THATWORLDS_API void that::Generator_SetHeightmapGenerator(Generator* pGenerator, height::HeightmapGenerator* pHeightmapGenerator)
	{
		return pGenerator->SetHeightmapGenerator(pHeightmapGenerator);
	}

	THATWORLDS_API float that::Generator_GetHeight(Generator* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
