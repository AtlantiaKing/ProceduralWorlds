using System;
using System.Runtime.InteropServices;

namespace that.shape
{
    public interface IWorldShape
    {
        IntPtr Native { get; }
    }

    public class CirclePeak : IWorldShape
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr CirclePeak_Create(float smoothPower);

        public IntPtr Native { get; private set; }

        /// <summary>
        /// Create a world shape that is a circle. The heightmap values are usually higher at the center.
        /// </summary>
        /// <param name="smoothPower">How quickly the heightmap values fade to 1 when nearing the center of the circle.</param>
        public CirclePeak(float smoothPower)
        {
            Native = CirclePeak_Create(smoothPower);
        }
    }

    public class SquarePeak : IWorldShape
    {
        [DllImport(ProcedularWorldsDll.DLL_NAME)]
        private static extern IntPtr SquarePeak_Create(float angularity, float smoothPower);

        public IntPtr Native { get; private set; }

        /// <summary>
        /// Create a world shape that is a rounded square. The heightmap values are usually higher at the center.
        /// </summary>
        /// <param name="angularity">Roundedness of the square. Higher value is less rounded. This number needs to be in steps of 2.</param>
        /// <param name="smoothPower">How quickly the heightmap values fade to 1 when nearing the center of the square.</param>
        public SquarePeak(float angularity, float smoothPower)
        {
            Native = SquarePeak_Create(angularity, smoothPower);
        }
    }
}