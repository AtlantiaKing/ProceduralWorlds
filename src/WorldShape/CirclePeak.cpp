#include "CirclePeak.h"

#include <math.h>
#include <algorithm>

that::shape::CirclePeak::CirclePeak(float smoothPower)
	: m_SmoothPower{ smoothPower }
{
}

float that::shape::CirclePeak::Transform(float size, float x, float y, float height) const
{
	const float radius{ size / 2.0f };

	// Calculate the distance from the center of the circle
	const float distanceFromCenter{ powf((x - radius) / radius, 2.0f) + powf((y - radius) / radius, 2.0f) };

	// Map the distance to the function f(x)=-x^power+1 so the value tends to go to 1 faster
	const float mappedDistance{ -powf(distanceFromCenter, m_SmoothPower) + 1 };

	// Return the height with the applied distance fade
	return height * std::max(mappedDistance, 0.0f);
}


extern "C" THATWORLDS_API that::shape::CirclePeak* that::shape::CirclePeak_Create(float smoothPower)
{
	return new CirclePeak{ smoothPower };
}
