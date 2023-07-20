using System.Runtime.InteropServices;
using System;

namespace that
{
    public class Generator
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr Generator_Create();

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Generator_Destroy(IntPtr generator);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Generator_SetSize(IntPtr generator, float size);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Generator_AddPredicate(IntPtr generator, IntPtr predicate);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void Generator_SetShape(IntPtr generator, IntPtr pPredicate);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr Generator_GetHeightMap(IntPtr generator);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern float Generator_GetHeight(IntPtr generator, float x, float y);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern bool Generator_TryPredicates(IntPtr generator, int step);

        public IntPtr Native { get; private set; }

        public HeightMap HeightMap
        {
            get { return new HeightMap(Generator_GetHeightMap(Native)); }
        }

        public Generator()
        {
            Native = Generator_Create();
        }

        ~Generator()
        {
            Generator_Destroy(Native);
        }

        public void SetSize(float size)
        {
            Generator_SetSize(Native, size);
        }

        public void AddPredicate(SuccessPredicate predicate)
        {
            Generator_AddPredicate(Native, predicate.Native);
        }

        public void SetShape(shape.IWorldShape shape)
        {
            Generator_SetShape(Native, shape.Native);
        }

        public float GetHeight(float x, float y)
        {
            return Generator_GetHeight(Native, x, y);
        }

        public bool TryPredicates(int step)
        {
            return Generator_TryPredicates(Native, step);
        }
    }
}
