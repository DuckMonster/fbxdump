# fbxdump
Simple utility to dump an FBX binary into a readable text document

## How do?
Just run `fbxdump.exe my_file.fbx` and it will spit out the file `my_file.fbx.dump` containing the human readable dump of the fbx. Thats it.

I've provided a pre-built exe with a test fbx file (just a default Blender scene with a cube and camera), so hopefully there shouldn't be much setup to get it working.

Here's an snippet of the output from the test fbx file:
```
...
'Geometry'
{
	(Long) 876144110
	(String) 'Cube.002'
	(String) 'Mesh'
}
	'Properties70'
	'GeometryVersion'
	{
		(Int) 124
	}
	'Vertices'
	{
		(Double[]) -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, 1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, 
	}
	'PolygonVertexIndex'
	{
		(Int[]) 0, 1, 3, -3, 2, 3, 7, -7, 6, 7, 5, -5, 4, 5, 1, -1, 2, 6, 4, -1, 7, 3, 1, -6, 
	}
	'Edges'
	{
		(Int[]) 0, 1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 15, 
	}
	'LayerElementNormal'
	{
		(Int) 0
	}
		'Version'
		{
			(Int) 101
		}
		'Name'
		{
			(String) ''
		}
		'MappingInformationType'
		{
			(String) 'ByPolygonVertex'
		}
		'ReferenceInformationType'
		{
			(String) 'Direct'
		}
		'Normals'
		{
			(Double[]) -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 
		}
	'LayerElementUV'
	{
		(Int) 0
	}
		'Version'
		{
			(Int) 101
		}
		'Name'
		{
			(String) 'UVMap'
		}
		'MappingInformationType'
		{
			(String) 'ByPolygonVertex'
		}
		'ReferenceInformationType'
		{
			(String) 'IndexToDirect'
		}
		'UV'
		{
			(Double[]) 0.625000, 1.000000, 0.375000, 0.250000, 0.375000, 1.000000, 0.125000, 0.500000, 0.625000, 0.250000, 0.875000, 0.500000, 0.375000, 0.000000, 0.125000, 0.750000, 0.625000, 0.000000, 0.875000, 0.750000, 0.375000, 0.500000, 0.625000, 0.500000, 0.375000, 0.750000, 0.625000, 0.750000, 
		}
		'UVIndex'
		{
			(Int[]) 6, 8, 4, 1, 1, 4, 11, 10, 10, 11, 13, 12, 12, 13, 0, 2, 3, 10, 12, 7, 11, 5, 9, 13, 
		}
...
```
