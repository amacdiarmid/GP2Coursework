#ifndef _MESH_H
#define _MESH_H

#include "Vertex.h"
#include "Common.h"

struct MeshData
{
	vector<Vertex> vertices;
	vector<int> indices;

	int getNumVerts()
	{
		return vertices.size();
	};

	int getNumIndices()
	{
		return indices.size();
	};

	vector<Vertex> getVertives()
	{
		return vertices;
	}

	~MeshData()
	{
		vertices.clear();
		indices.clear();
	}
};

#endif