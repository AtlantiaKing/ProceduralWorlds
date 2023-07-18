#pragma once

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

#include "Heightmap/HeightMap.h"
#include "SuccessPredicate.h"
#include "WorldShape/WorldShape.h"

#include <memory>

namespace that
{
	class Generator final
	{
	public:
		Generator() = default;
		~Generator() = default;

		THATWORLDS_API void SetSize(float size);
		THATWORLDS_API void AddPredicate(const SuccessPredicate& predicate);
		THATWORLDS_API void SetShape(std::unique_ptr<shape::WorldShape> pShape);

		THATWORLDS_API HeightMap& GetHeightMap();

		// Returns the heightmap value [0,1] for this coordinate
		THATWORLDS_API float GetHeight(float x, float y) const;
		THATWORLDS_API bool TryPredicates(int step);

	private:
		HeightMap m_HeightMap{};

		std::vector<SuccessPredicate> m_SuccessPredicates{};

		std::unique_ptr<shape::WorldShape> m_pShape{};

		float m_Size{ 100.0f };
	};

	extern "C"
	{
		THATWORLDS_API Generator* Generator_Create();
		THATWORLDS_API void Generator_Destroy(Generator* pGenerator);
		THATWORLDS_API void Generator_SetSize(Generator* pGenerator, float size);
		THATWORLDS_API void Generator_AddPredicate(Generator* pGenerator, SuccessPredicate* pPredicate);
		THATWORLDS_API void Generator_SetShape(Generator* pGenerator, shape::WorldShape* pPredicate);
		THATWORLDS_API HeightMap* Generator_GetHeightMap(Generator* pGenerator);
		THATWORLDS_API float Generator_GetHeight(Generator* pGenerator, float x, float y);
		THATWORLDS_API bool Generator_TryPredicates(Generator* pGenerator, int step);
	}
}