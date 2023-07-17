#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "Heightmap/HeightmapGenerator.h"
#include "Rivers/RiversGenerator.h"

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

		/// <summary>
		/// Sets the deepest point a river can get.
		/// Needs to be a value between [0,1].
		/// </summary>
		void THATWORLDS_API SetRiverDepth(float depth);
		/// <summary>
		/// Set the strength of the smoothing between land and river.
		/// Needs to be an odd number.
		/// </summary>
		void THATWORLDS_API SetRiverSmoothing(float smoothPower);

		void THATWORLDS_API SetHeightmapGenerator(height::HeightmapGenerator* pGenerator);
		void THATWORLDS_API SetRiversGenerator(river::RiversGenerator* pGenerator);

		// Returns the heightmap value [0,1] for this coordinate
		float THATWORLDS_API GetHeight(float x, float y) const;

	private:
		unsigned int m_Seed{};
		float m_Scale{ 1.0f };

		// Mixer settings
		float m_RiverDepth{ 0.2f };
		float m_RiverSmoothStep{ 7.0f };

		std::unique_ptr<height::HeightmapGenerator> m_pHeightGenerator{};
		std::unique_ptr<river::RiversGenerator> m_pRiversGenerator{};
	};

	extern "C"
	{
		THATWORLDS_API Generator* Generator_Create();
		THATWORLDS_API void Generator_Destroy(Generator * pGenerator);
		THATWORLDS_API void Generator_SetScale(Generator* pGenerator, float scale);
		THATWORLDS_API float Generator_GetScale(Generator* pGenerator);
		THATWORLDS_API void Generator_SetRiverDepth(Generator* pGenerator, float depth);
		THATWORLDS_API void Generator_SetRiverSmoothing(Generator* pGenerator, float smoothPower);
		THATWORLDS_API void Generator_SetHeightmapGenerator(Generator* pGenerator, height::HeightmapGenerator* pHeightmapGenerator);
		THATWORLDS_API void Generator_SetRiversGenerator(Generator* pGenerator, river::RiversGenerator* pRiversGenerator);
		THATWORLDS_API float Generator_GetHeight(Generator * pGenerator, float x, float y);
	}
}