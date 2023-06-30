#include "Perlin.h"

#include <SDL_stdinc.h>
#include <algorithm>

that::Perlin::Perlin(int nrOctaves, float zoom)
	: m_Zoom{ zoom }
{
	SetOctaves(nrOctaves);
}

void that::Perlin::SetOctaves(int nrOctaves)
{
	m_OctaveSeeds.clear();

	m_NrOctaves = nrOctaves;
	m_MaxNoiseValue = 0.0f;

	for (int i{ 1 }; i <= nrOctaves; ++i)
	{
		// Calculates the maximum value of noise a coordinate can have
		m_MaxNoiseValue += 1.0f / i;

		// Creates a new displacement for each octave
		const Vector2Int seed
		{
			static_cast<int>((rand() / static_cast<float>(RAND_MAX)) * m_MaxOctaveDisplacement),
			static_cast<int>((rand() / static_cast<float>(RAND_MAX)) * m_MaxOctaveDisplacement)
		};
		m_OctaveSeeds.emplace_back(seed);
	}
}

float that::Perlin::GetNoise(float x, float y) const
{
	float noise{};
	for (int i{ 1 }; i <= m_NrOctaves; ++i)
	{
		noise += GetOctaveNoise(x, y, i) / i;
	}
	noise /= (m_MaxNoiseValue / 2.0f);
	noise /= 2.0f;
	noise += 0.5f;

	return std::clamp(noise, 0.0f, 1.0f);
}

float that::Perlin::GetOctaveNoise(float x, float y, int octave) const
{
	// You can't have an octave that has an index lower than 0
	if (octave <= 0) return 0.0f;

	// Displace the current coordinate depending on the octave
	const size_t octaveIdx{ static_cast<size_t>(octave - 1) };
	x += m_MiddleOfNoise + m_OctaveSeeds[octaveIdx].x;
	y += m_MiddleOfNoise + m_OctaveSeeds[octaveIdx].y;

	// Multiply the current coordinate depending on the octave and zoom
	x *= powf(2.0f, static_cast<float>(octave - 1)) / m_Zoom;
	y *= powf(2.0f, static_cast<float>(octave - 1)) / m_Zoom;

	// Calculate the grid corners
	const int gridX0{ static_cast<int>(x) };
	const int gridX1{ gridX0 + 1 };
	const int gridY0{ static_cast<int>(y) };
	const int gridY1{ gridY0 + 1 };

	// Calculate the position in the current grid cell
	const float gridPosX{ x - gridX0 };
	const float gridPosY{ y - gridY0 };

	// Calculate the gradients for each grid corner
	const float dotGradient0{ Dot(GetRandomGradient(gridX0, gridY0), Vector2Float{ gridPosX, gridPosY }) };
	const float dotGradient1{ Dot(GetRandomGradient(gridX1, gridY0), Vector2Float{ gridPosX - 1.0f, gridPosY }) };
	const float dotGradient2{ Dot(GetRandomGradient(gridX0, gridY1), Vector2Float{ gridPosX, gridPosY - 1.0f }) };
	const float dotGradient3{ Dot(GetRandomGradient(gridX1, gridY1), Vector2Float{ gridPosX - 1.0f, gridPosY - 1.0f }) };

	// Interpolate between the gradients depending on the grid position
	// The interpolation is smoothed using the formula 3x^2 - 2x^3
	const float xEase{ 3.0f * powf(gridPosX, 2.0f) - 2.0f * powf(gridPosX, 3.0f) };
	const float yEase{ 3.0f * powf(gridPosY, 2.0f) - 2.0f * powf(gridPosY, 3.0f) };
	const float result{ Lerp(Lerp(dotGradient0, dotGradient1, xEase), Lerp(dotGradient2, dotGradient3, xEase), yEase) };

	return result;
}

that::Vector2Float that::Perlin::GetRandomGradient(int ix, int iy) const
{
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; // rotation width
	unsigned a = ix, b = iy;
	a *= 3284157443;
	b ^= (a << s) | (a >> (w - s));
	b *= 1911520717;
	a ^= (b << s) | (b >> (w - s));
	a *= 2048419325;
	const float random = static_cast<float>(a * (M_PI / ~(~0u >> 1))); // in [0, 2*Pi]
	const Vector2Float v
	{
		cosf(random),
		sinf(random)
	};
	return v;
}

float that::Perlin::Lerp(float a, float b, float t) const
{
	return a + t * (b - a);
}

float that::Perlin::Dot(const Vector2Float& a, const Vector2Float& b) const
{
	return a.x * b.x + a.y * b.y;
}
