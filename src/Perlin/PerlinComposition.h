#pragma once

#include "../Structs/Vector2.h"

#include <vector>

namespace that
{
	class PerlinComposition final
	{
	public:
		PerlinComposition() = default;
		~PerlinComposition() = default;

		void AddOctave(float multiplier, float zoom);

		float GetNoise(int x, int y) const;
		float GetNoise(float x, float y) const;

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

		const float m_MiddleOfNoise{ 500'000 };
		const float m_MaxOctaveDisplacement{ 100'000 };
	};
}
