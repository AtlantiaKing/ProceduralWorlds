using System.Runtime.InteropServices;
using System;

namespace that
{
    public class SuccessPredicate
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr SuccessPredicate_Create(Func<float, float, bool> predicate);

        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern void SuccessPredicate_Destroy(IntPtr predicate);

        public IntPtr Native { get; private set; }

        public SuccessPredicate(Func<float, float, bool> predicate)
        {
            Native = SuccessPredicate_Create(predicate);
        }

        ~SuccessPredicate()
        {
            SuccessPredicate_Destroy(Native);
        }
    }
}