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

		/// <summary>
		/// <para>Add a node to the graph</para> 
		/// <para>x and y values need to be between [0,1]</para> 
		/// </summary>
		THATWORLDS_API void AddNode(float x, float y);

		/// <summary>
		/// <para>Returns the y-value on the graph [0,1] for a given x value</para> 
		/// <para>The given x value needs to be between [0,1]</para> 
		/// <para>A graph needs to have lower (x=0) and upper (x=1) bound nodes to succesfully get a value.</para> 
		/// </summary>
		THATWORLDS_API float GetValue(float x) const;

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
