#pragma once

namespace that::shape
{
	class WorldShape
	{
	public:
		WorldShape() = default;
		virtual ~WorldShape() = default;

		virtual float Transform(float size, float x, float y, float height) const = 0;
	};
}