#include "Graph.h"

#include <stdexcept>

void that::Graph::AddNode(float x, float y)
{
	// Check bound limits
	if (x < 0.0f) throw std::runtime_error("No value should be mapped under 0");
	if (x > 1.0f) throw std::runtime_error("No value should be mapped above 1");
	if (y < 0.0f) throw std::runtime_error("A node cannot have an y under 0");
	if (y > 1.0f) throw std::runtime_error("A node cannot have an y above 1");

	m_Nodes.insert(std::make_pair(x, y));
}

float that::Graph::GetValue(float x) const
{
	// Check bound limits
	if (x < 0.0f) throw std::runtime_error("No value should be mapped under 0");
	if (x > 1.0f) throw std::runtime_error("No value should be mapped above 1");
	if (m_Nodes.find(0.0f) == end(m_Nodes)) throw std::runtime_error("No lower bound node (x = 0) is added.");
	if (m_Nodes.find(1.0f) == end(m_Nodes)) throw std::runtime_error("No upper bound node (x = 1) is added.");

	// Retrieve the first node greater (or equal) then the given value
	const auto greaterNode{ m_Nodes.lower_bound(x) };

	// If the given value is 0, we only need the first node
	if (x < FLT_EPSILON) return greaterNode->second;

	// Retrieve the first node smaller then the given value
	const auto smallerNode{ std::prev(greaterNode) };

	// Lerp between the two values
	const float percentage{ (x - smallerNode->first) / (greaterNode->first - smallerNode->first) };
	const float value{ smallerNode->second + (greaterNode->second - smallerNode->second) * percentage };
	return value;
}

extern "C"
{
	THATWORLDS_API that::Graph* that::Graph_Create()
	{
		return new that::Graph{};
	}

	THATWORLDS_API void that::Graph_Destroy(Graph* pGraph)
	{
		delete pGraph;
	}

	THATWORLDS_API void that::Graph_AddNode(Graph* pGraph, float x, float y)
	{
		pGraph->AddNode(x, y);
	}

	THATWORLDS_API float that::Graph_GetValue(Graph* pGraph, float x)
	{
		return pGraph->GetValue(x);
	}
}
