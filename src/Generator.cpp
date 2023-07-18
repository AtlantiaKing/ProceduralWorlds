#include "Generator.h"

void that::Generator::SetSize(float size)
{
	m_Size = size;
}

void that::Generator::AddPredicate(const SuccessPredicate& predicate)
{
	m_SuccessPredicates.emplace_back(predicate);
}

that::HeightMap& that::Generator::GetHeightMap()
{
	return m_HeightMap;
}

float that::Generator::GetHeight(float x, float y) const
{
	return m_HeightMap.GetHeight(x, y);
}

bool that::Generator::TryPredicates(int step)
{
	if (m_SuccessPredicates.empty()) return true;

	std::vector<SuccessPredicate> predicatesCopy{ m_SuccessPredicates };

	for (int x{}; x < m_Size; x += step)
	{
		float prevHeight{ GetHeight(static_cast<float>(x), 0.0f)};

		for (int z{ 1 }; z < m_Size; z += step)
		{
			float height{ GetHeight(static_cast<float>(x), static_cast<float>(z)) };

			for (int i{ static_cast<int>(predicatesCopy.size()) - 1 }; i >= 0; --i)
			{
				const auto& predicate{ predicatesCopy[i] };

				if (predicate.IsTrue(height, prevHeight)) predicatesCopy.erase(begin(predicatesCopy) + i);
			}

			prevHeight = height;
		}
	}

	if (predicatesCopy.empty()) return true;

	for (int z{}; z < m_Size; z += step)
	{
		float prevHeight{ GetHeight(0.0f, static_cast<float>(z)) };

		for (int x{ 1 }; x < m_Size; x += step)
		{
			float height{ GetHeight(static_cast<float>(x), static_cast<float>(z)) };

			for (int i{ static_cast<int>(predicatesCopy.size()) - 1 }; i >= 0; --i)
			{
				const auto& predicate{ predicatesCopy[i] };

				if (predicate.IsTrue(height, prevHeight)) predicatesCopy.erase(begin(predicatesCopy) + i);
			}

			prevHeight = height;
		}
	}

	return predicatesCopy.empty();
}

extern "C"
{
	THATWORLDS_API that::Generator* that::Generator_Create()
	{
		return new that::Generator{};
	}

	THATWORLDS_API void that::Generator_Destroy(Generator* pGenerator)
	{
		delete pGenerator;
	}

	THATWORLDS_API that::HeightMap* that::Generator_GetHeightMap(Generator* pGenerator)
	{
		return &pGenerator->GetHeightMap();
	}

	THATWORLDS_API float that::Generator_GetHeight(Generator* pGenerator, float x, float y)
	{
		return pGenerator->GetHeight(x, y);
	}
}
