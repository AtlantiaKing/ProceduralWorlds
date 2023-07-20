using System.Runtime.InteropServices;
using System;

namespace that
{
    public class PerlinComposition
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void PerlinComposition_AddOctave(IntPtr generator, float multiplier, float zoom);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern float PerlinComposition_GetNoise(IntPtr generator, float x, float y);

        protected IntPtr _native;

        public PerlinComposition(IntPtr native)
        {
            _native = native;
        }

        public void AddOctave(float multiplier, float zoom)
        {
            PerlinComposition_AddOctave(_native, multiplier, zoom);
        }

        public float GetNoise(float x, float y)
        {
            return PerlinComposition_GetNoise(_native, x, y);
        }

        public IntPtr GetNative()
        {
            return _native;
        }
    }
}
