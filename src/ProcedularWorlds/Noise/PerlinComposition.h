#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "../Structs/ThatVector2.h"

#include <vector>

namespace that
{
	class PerlinComposition final
	{
	public:
		PerlinComposition() = default;
		~PerlinComposition() = default;

		THATWORLDS_API void AddOctave(float multiplier, float zoom);

		THATWORLDS_API float GetNoise(int x, int y) const;
		THATWORLDS_API float GetNoise(float x, float y) const;

	private:
		struct PerlinOctave
		{
			float multiplier{};
			float zoom{};
			Vector2Float offset{};
		};

		float GetOctaveNoise(float x, float y, const PerlinOctave& octave) const;
		Vector2Float GetRandomGradient(int ix, int iy) const;
		float Lerp(float a, float b, float t) const;
		float Dot(const Vector2Float& a, const Vector2Float& b) const;

		float m_MaxNoiseValue{};
		std::vector<PerlinOctave> m_Octaves{};

		static const float m_MiddleOfNoise;
		static const float m_MaxOctaveDisplacement;
	};

	extern "C"
	{
		THATWORLDS_API PerlinComposition* PerlinComposition_Create();
		THATWORLDS_API void PerlinComposition_Destroy(PerlinComposition* pPerlin);
		THATWORLDS_API void PerlinComposition_AddOctave(PerlinComposition* pPerlin, float multiplier, float zoom);
		THATWORLDS_API float PerlinComposition_GetNoise(PerlinComposition* pPerlin, float x, float y);
	}
}
