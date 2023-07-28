using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(WorldGenerator))]
public class WorldGenerationEditor : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();

        WorldGenerator gen = (WorldGenerator)target;

        if (GUILayout.Button("Generate"))
        {
            gen.Generate();
        }

        if(GUILayout.Button("Random seed"))
        {
            gen.RandomSeed();
        }
    }
}
