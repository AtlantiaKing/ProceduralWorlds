using UnityEngine;

public class WorldGenerator : MonoBehaviour
{
    [SerializeField] private uint _seed = 0;
    [SerializeField] private int _zoom = 10;

    [SerializeField] private float _seaLevel = 0.35f;

    [SerializeField] private float _smoothPower = 2.0f;
    [SerializeField] private float _angularity = 4.0f;

    private enum WorldShape
    {
        Infinite,
        Circle,
        Square
    }
    [SerializeField] private WorldShape _shape;

    private void Start()
    {
        Generate();
    }

    public void Generate()
    {
        // Retrieve terrain and its needed data
        Terrain t = GetComponent<Terrain>();
        int size = t.terrainData.heightmapResolution;
        float[,] heights = t.terrainData.GetHeights(0, 0, size, size);

        // Create a new generator
        that.Generator gen = new that.Generator();
        
        // Use the default preset to set up the heightmap
        that.preset.Presets.CreateDefaultTerrain(gen, _seed, _zoom);

        // Set up the size and shape of the generator
        gen.SetSize(size);
        if (_shape == WorldShape.Square)
        {
            gen.SetShape(new that.shape.SquarePeak(_angularity, _smoothPower));
        }
        else if (_shape == WorldShape.Circle)
        {
            gen.SetShape(new that.shape.CirclePeak(_smoothPower));
        }

        // Apply the world to the terrain
        for (int x = 0; x < size; x++)
        {
            for (int z = 0; z < size; z++)
            {
                float height = gen.GetHeight(transform.position.z/ 2.0f + x, transform.position.x / 2.0f+ z);

                if (height <= _seaLevel)
                {
                    height = _seaLevel;
                }

                height -= _seaLevel;

                heights[x, z] = height;
            }
        }
        t.terrainData.SetHeights(0, 0, heights);
    }

    public void RandomSeed()
    {
        _seed = (uint)(Random.value*uint.MaxValue);
    }
}
