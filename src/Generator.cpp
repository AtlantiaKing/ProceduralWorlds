#include "Generator.h"

that::HeightMap& that::Generator::GetHeightMap()
{
	return m_HeightMap;
}

float that::Generator::GetHeight(float x, float y) const
{
	return m_HeightMap.GetHeight(x, y);
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

	THATWORLDS_API that::HeightMap* that::Generator_GetHeightMap(Generator* pGenerator)
	{
		return &pGenerator->GetHeightMap();
	}

	THATWORLDS_API float that::Generator_GetHeight(Generator* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
