#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

namespace that
{
	class Generator;

	namespace preset
	{
		class Presets
		{
		public:
			THATWORLDS_API static void CreateDefaultTerrain(Generator& generator, unsigned int seed, float mapZoom);
		};

		extern "C" THATWORLDS_API void Presets_CreateDefaultTerrain(Generator* pGenerator, unsigned int seed, float mapZoom);
	}
}

