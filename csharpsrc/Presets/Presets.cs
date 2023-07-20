using System;
using System.Runtime.InteropServices;

namespace that.preset
{
    public class Presets
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Presets_CreateDefaultTerrain(IntPtr generator, uint seed, float mapZoom);

        public static void CreateDefaultTerrain(Generator generator, uint seed, float mapZoom)
        {
            Presets_CreateDefaultTerrain(generator.Native, seed, mapZoom);
        }
    }
}