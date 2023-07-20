#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "../Noise/NoiseMap.h"

#include <vector>

namespace that
{
	class HeightMap final
	{
	public:
		enum class BlendMode
		{
			Multiply,
			Add,
			Average
		};

		HeightMap() = default;
		~HeightMap() = default;

		THATWORLDS_API void AddNoiseMap(const NoiseMap& noiseMap);
		THATWORLDS_API void SetBlendMode(BlendMode blendMode);

		THATWORLDS_API float GetHeight(float x, float y) const;

	private:
		std::vector<NoiseMap> m_NoiseMaps{};

		BlendMode m_BlendMode{ BlendMode::Average };
	};

	extern "C"
	{
		THATWORLDS_API HeightMap* HeightMap_Create();
		THATWORLDS_API void HeightMap_Destroy(HeightMap* pHeightMap);
		THATWORLDS_API void HeightMap_AddNoiseMap(HeightMap* pHeightMap, NoiseMap* pNoiseMap);
		THATWORLDS_API void HeightMap_SetBlendMode(HeightMap* pHeightMap, int blendMode);
		THATWORLDS_API float HeightMap_GetHeight(HeightMap* pHeightMap, float x, float y);
	}
}

