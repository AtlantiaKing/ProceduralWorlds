#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

namespace that::height
{
	class HeightmapGenerator
	{
	public:
		HeightmapGenerator() = default;
		virtual ~HeightmapGenerator() = default;

		virtual float GetHeight(float x, float y) const = 0;
	private:
	};

	extern "C" THATWORLDS_API float HeightmapGenerator_GetHeight(HeightmapGenerator* pGenerator, float x, float y);
}