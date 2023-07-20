using System.Runtime.InteropServices;
using System;

namespace that
{
    public class DynamicPerlinComposition : PerlinComposition
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr PerlinComposition_Create();

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void PerlinComposition_Destroy(IntPtr generator);

        DynamicPerlinComposition() : base(PerlinComposition_Create())
        {
        }

        ~DynamicPerlinComposition()
        {
            PerlinComposition_Destroy(_native);
        }
    }
}
