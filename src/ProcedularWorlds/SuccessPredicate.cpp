#include "SuccessPredicate.h"

that::SuccessPredicate::SuccessPredicate(std::function<bool(float, float)> predicate)
	: m_Predicate{ predicate }
{
}

bool that::SuccessPredicate::IsTrue(float height0, float height1) const
{
	return m_Predicate(height0, height1);
}

extern "C"
{
	THATWORLDS_API that::SuccessPredicate* that::SuccessPredicate_Create(bool(*pPredicate)(float, float))
	{
		return new SuccessPredicate{ pPredicate };
	}

	THATWORLDS_API void that::SuccessPredicate_Destroy(SuccessPredicate* pPredicate)
	{
		delete pPredicate;
	}
}
