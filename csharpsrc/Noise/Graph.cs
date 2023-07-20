using System.Runtime.InteropServices;
using System;

namespace that
{
    public class Graph
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Graph_AddNode(IntPtr graph, float x, float y);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern float Graph_GetValue(IntPtr graph, float x);

        protected IntPtr _native;

        public Graph(IntPtr native)
        {
            _native = native;
        }

        public void AddNode(float x, float y)
        {
            Graph_AddNode(_native, x, y);
        }

        public float GetValue(float x)
        {
            return Graph_GetValue(_native, x);
        }

        public IntPtr GetNative()
        {
            return  _native;
        }
    }
}