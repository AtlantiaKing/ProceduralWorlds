#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

namespace that::river
{
	class RiversGenerator
	{
	public:
		RiversGenerator() = default;
		virtual ~RiversGenerator() = default;

		virtual float GetDepth(float x, float y) = 0;
	private:
	};

	extern "C" THATWORLDS_API float RiversGenerator_GetDepth(RiversGenerator* pGenerator, float x, float y);
}