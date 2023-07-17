#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "Heightmap/HeightmapGenerator.h"

#include <memory>

namespace that
{
	class Generator final
	{
	public:
		Generator() = default;
		~Generator() = default;

		void THATWORLDS_API SetScale(float scale);
		float THATWORLDS_API GetScale() const;

		void THATWORLDS_API SetHeightmapGenerator(height::HeightmapGenerator* pGenerator);

		// Returns the heightmap value [0,1] for this coordinate
		float THATWORLDS_API GetHeight(float x, float y) const;

	private:
		unsigned int m_Seed{};
		float m_Scale{ 1.0f };

		std::unique_ptr<height::HeightmapGenerator> m_pHeightGenerator{};
	};

	extern "C"
	{
		THATWORLDS_API Generator* Generator_Create();
		THATWORLDS_API void Generator_Destroy(Generator * pGenerator);
		THATWORLDS_API void Generator_SetScale(Generator* pGenerator, float scale);
		THATWORLDS_API float Generator_GetScale(Generator* pGenerator);
		THATWORLDS_API void Generator_SetHeightmapGenerator(Generator * pGenerator, height::HeightmapGenerator * pHeightmapGenerator);
		THATWORLDS_API float Generator_GetHeight(Generator * pGenerator, float x, float y);
	}
}