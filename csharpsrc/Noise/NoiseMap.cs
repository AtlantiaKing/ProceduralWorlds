using System.Runtime.InteropServices;
using System;

namespace that
{
    public class NoiseMap
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr NoiseMap_Create();

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void NoiseMap_Destroy(IntPtr noiseMap);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern float NoiseMap_GetNoise(IntPtr noiseMap, float x, float y);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr NoiseMap_GetPerlin(IntPtr noiseMap);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr NoiseMap_GetGraph(IntPtr noiseMap);

        public IntPtr Native { get; protected set; }

        public PerlinComposition Perlin
        {
            get { return new PerlinComposition(NoiseMap_GetPerlin(Native)); }
        }

        public Graph Graph
        {
            get { return new Graph(NoiseMap_GetGraph(Native)); }
        }

        public NoiseMap()
        {
            Native = NoiseMap_Create();
        }

        ~NoiseMap()
        {
            NoiseMap_Destroy(Native);
        }

        public float GetNoise(float x, float y)
        {
            return NoiseMap_GetNoise(Native, x, y);
        }
    }
}