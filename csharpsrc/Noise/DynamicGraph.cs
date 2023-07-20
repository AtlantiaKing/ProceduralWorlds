using System.Runtime.InteropServices;
using System;

namespace that
{
    public class DynamicGraph : Graph
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr Graph_Create();

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Graph_Destroy(IntPtr graph);

        public DynamicGraph() : base(Graph_Create())
        {
        }

        ~DynamicGraph()
        {
            Graph_Destroy(_native);
        }
    }
}