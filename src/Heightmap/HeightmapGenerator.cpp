#include "HeightmapGenerator.h"

extern "C" THATWORLDS_API float that::height::HeightmapGenerator_GetHeight(HeightmapGenerator * pGenerator, float x, float y)
{
	return pGenerator->GetHeight(x, y);
}
