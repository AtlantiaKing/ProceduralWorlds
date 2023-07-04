#pragma once

#include "../Structs/Vector2.h"

#include <vector>

namespace that
{
	class Perlin final
	{
	public:
		Perlin(int nrOctaves = 5, float zoom = 10.0f);
		~Perlin() = default;

		void SetOctaves(int nrOctaves);
		void SetZoom(float zoom) { m_Zoom = zoom; }

		/*
		 Returns the noise value at x,y
		Noise value is always between 0 and 1
		*/
		float GetNoise(int x, int y) const;
		/*
		 Returns the noise value at x,y
		Noise value is always between 0 and 1
		*/
		float GetNoise(float x, float y) const;
	private:
		std::vector<Vector2Float> m_OctaveSeeds{};

		float GetOctaveNoise(float x, float y, int octave) const;
		Vector2Float GetRandomGradient(int ix, int iy) const;
		float Lerp(float a, float b, float t) const;
		float Dot(const Vector2Float& a, const Vector2Float& b) const;

		const float m_MiddleOfNoise{ 500'000 };
		const float m_MaxOctaveDisplacement{ 100'000 };

		int m_NrOctaves{};
		float m_MaxNoiseValue{};
		float m_Zoom{};
	};
}