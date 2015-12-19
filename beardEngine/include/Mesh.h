#ifndef _MESH_H
#define _MESH_H

#include "Vertex.h"
#include "Common.h"

struct MeshData
{
	vector<Vertex> vertices;
	vector<int> indices;

	void create(Vertex * pverts, int numverts, int *pIndices, int numIndices);


	int getNumVerts()
	{
		return (int)vertices.size();
	};

	int getNumIndices()
	{
		return (int)indices.size();
	};

	vector<Vertex> getVertives()
	{
		return vertices;
	}

	MeshData();
	~MeshData();

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	int m_NoOfIndices;
	int m_NoOfVertices;

};

#endif