#pragma once

#include <map>

#ifdef THATWORLDS_EXPORTS
#define THATWORLDS_API __declspec(dllexport)
#else
#define THATWORLDS_API __declspec(dllimport)
#endif

namespace that
{
	class Graph final
	{
	public:
		Graph() = default;
		~Graph() = default;

		void THATWORLDS_API AddNode(float x, float y);
		float THATWORLDS_API GetValue(float x);

	private:
		std::map<float, float> m_Nodes{};
	};

	extern "C"
	{
		THATWORLDS_API Graph* Graph_Create();
		THATWORLDS_API void Graph_Destroy(Graph* pGraph);
		THATWORLDS_API void Graph_AddNode(Graph* pGraph, float x, float y);
		THATWORLDS_API float Graph_GetValue(Graph* pGraph, float x);
	}
}
