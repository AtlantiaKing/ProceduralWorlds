#include "PerlinComposition.h"

#include <SDL_stdinc.h>
#include <algorithm>

void that::PerlinComposition::AddOctave(float multiplier, float zoom)
{
	// Calculates the maximum value of noise a coordinate can have
	m_MaxNoiseValue += multiplier;

	// Create a new octave
	PerlinOctave octave{ multiplier, zoom };

	// Creates a new displacement for each octave
	const Vector2Float offset
	{
		(rand() / static_cast<float>(RAND_MAX)) * m_MaxOctaveDisplacement,
		(rand() / static_cast<float>(RAND_MAX)) * m_MaxOctaveDisplacement
	};
	octave.offset = offset;

	m_Octaves.emplace_back(octave);
}

float that::PerlinComposition::GetNoise(int x, int y) const
{
	return GetNoise(static_cast<float>(x), static_cast<float>(y));
}

float that::PerlinComposition::GetNoise(float x, float y) const
{
	// Calculate the noise at this point
	float noise{};
	for (const auto& octave : m_Octaves)
	{
		noise += GetOctaveNoise(x, y, octave);
	}

	// map -maxNoise -> maxNoise to 0 -> 1
	noise = (noise + m_MaxNoiseValue) / (2.0f * m_MaxNoiseValue);

	return noise;
}

float that::PerlinComposition::GetOctaveNoise(float x, float y, const PerlinOctave& octave) const
{	
	// Displace the current coordinate depending on the octave
	x += m_MiddleOfNoise + octave.offset.x;
	y += m_MiddleOfNoise + octave.offset.y;

	// Multiply the current coordinate depending on the octave and zoom
	x *= powf(2.0f, 1.0f / octave.multiplier - 1) / octave.zoom;
	y *= powf(2.0f, 1.0f / octave.multiplier - 1) / octave.zoom;

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

	return result * octave.multiplier;
}

that::Vector2Float that::PerlinComposition::GetRandomGradient(int ix, int iy) const
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

float that::PerlinComposition::Lerp(float a, float b, float t) const
{
	return a + t * (b - a);
}

float that::PerlinComposition::Dot(const Vector2Float& a, const Vector2Float& b) const
{
	return a.x * b.x + a.y * b.y;
}