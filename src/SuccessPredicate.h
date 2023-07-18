#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include <functional>

namespace that
{
	class SuccessPredicate final
	{
	public:
		THATWORLDS_API SuccessPredicate(std::function<bool(float, float)> predicate);
		~SuccessPredicate() = default;

		bool THATWORLDS_API IsTrue(float height0, float height1) const;

	private:
		std::function<bool(float, float)> m_Predicate;
	};

	extern "C" THATWORLDS_API SuccessPredicate* SuccessPredicate_Create(bool(*pPredicate)(float,float));
	extern "C" THATWORLDS_API void SuccessPredicate_Destroy(SuccessPredicate* pPredicate);
}
