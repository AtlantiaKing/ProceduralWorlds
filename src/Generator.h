#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "Heightmap/HeightMap.h"

namespace that
{
	class Generator final
	{
	public:
		Generator() = default;
		~Generator() = default;

		THATWORLDS_API HeightMap& GetHeightMap();

		// Returns the heightmap value [0,1] for this coordinate
		THATWORLDS_API float GetHeight(float x, float y) const;

	private:
		HeightMap m_HeightMap{};
	};

	extern "C"
	{
		THATWORLDS_API Generator* Generator_Create();
		THATWORLDS_API void Generator_Destroy(Generator* pGenerator);
		THATWORLDS_API HeightMap* Generator_GetHeightMap(Generator* pGenerator);
		THATWORLDS_API float Generator_GetHeight(Generator* pGenerator, float x, float y);
	}
}