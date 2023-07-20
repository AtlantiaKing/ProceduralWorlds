using System;
using System.Runtime.InteropServices;

namespace that
{
    public class DynamicHeightMap : HeightMap
    {

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr HeightMap_Create();

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void HeightMap_Destroy(IntPtr graph);

        public DynamicHeightMap() : base(HeightMap_Create())
        {
        }

        ~DynamicHeightMap()
        {
            HeightMap_Destroy(Native);
        }
    }
}