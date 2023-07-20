using System;
using System.Runtime.InteropServices;

namespace that
{
    public enum HeightMapBlendMode
    {
        Multiply,
        Add,
        Average
    }

    public class HeightMap
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void HeightMap_AddNoiseMap(IntPtr heightMap, IntPtr noiseMap);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void HeightMap_SetBlendMode(IntPtr heightMap, int blendMode);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern float HeightMap_GetHeight(IntPtr heightMap, float x, float y);

        public IntPtr Native { get; protected set; }

        public HeightMap(IntPtr native)
        {
            Native = native;
        }

        public void AddNoiseMap(NoiseMap noiseMap) 
        {
            HeightMap_AddNoiseMap(Native, noiseMap.Native);
        }

        public void SetBlendMode(HeightMapBlendMode blendMode)
        {
            HeightMap_SetBlendMode(Native, (int)blendMode);
        }

        public float GetHeight(float x, float y)
        {
            return HeightMap_GetHeight(Native, x, y);
        }
    }
}