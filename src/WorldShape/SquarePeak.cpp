#include "SquarePeak.h"

#include <corecrt_math.h>
#include <algorithm>

that::shape::SquarePeak::SquarePeak(float angularity, float smoothPower)
	: m_Angularity{ angularity }
	, m_SmoothPower{ smoothPower }
{
}

float that::shape::SquarePeak::Transform(float size, float x, float y, float height) const
{
	const float radius{ size / 2.0f };

	// Calculate the distance from the center of the rounded square
	const float distanceFromCenter{ powf((x - radius) / radius, m_Angularity) + powf((y - radius) / radius, m_Angularity) };

	// Map the distance to the function f(x)=-x^power+1 so the value tends to go to 1 faster
	const float mappedDistance{ -powf(distanceFromCenter, m_SmoothPower) + 1 };

	// Return the height with the applied distance fade
	return height * std::max(mappedDistance, 0.0f);
}

extern "C" THATWORLDS_API that::shape::SquarePeak * that::shape::SquarePeak_Create(float angularity, float smoothPower)
{
	return new SquarePeak{ angularity, smoothPower };
}
