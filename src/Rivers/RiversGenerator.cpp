#include "RiversGenerator.h"

extern "C" THATWORLDS_API float that::river::RiversGenerator_GetDepth(RiversGenerator * pGenerator, float x, float y)
{
    return pGenerator->GetDepth(x,y);
}
