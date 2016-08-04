#include "stdafx.h"
#include "MeshBuilder.h"
#include "Mesh.h"

namespace zro{


void MeshBuilder::AddVertex(vec3 v)
{
	vertices.push_back(v);
}

void MeshBuilder::AddFace(ixFace f)
{
	faces.push_back(f);
}

IMesh* MeshBuilder::FinalizeMesh()
{
	if (vertices.size() > 0xFF) {
		// Assumed to use GL_BYTE if GlMesh
		throw "TOO MUCH SHIT";
	}

	GLuint meshObject;
	{
		glGenVertexArrays(1, &meshObject);
	}
	{
		glBindVertexArray(meshObject);
		vector<float> verticeCoord;
		for (vec3&v : vertices)
		{
			verticeCoord.push_back(v.x);
			verticeCoord.push_back(v.y);
			verticeCoord.push_back(v.z);
		}
		GLuint vertexArray;
		glGenBuffers(1, &vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verticeCoord.size(), &verticeCoord[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, vertices.size(), GL_FLOAT, GL_FALSE, 0, (void*)0);
		// Work is done, unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &vertexArray);
	}
	GLsizei indexCount;
	{
		glBindVertexArray(meshObject);
		vector<uchar> indexes;
		indexes.reserve(faces.size() * 3);
		for (auto& f : faces) {
			indexes.push_back(f.i1);
			indexes.push_back(f.i2);
			indexes.push_back(f.i3);
		}

		indexCount = indexes.size();

		GLuint elemArray;
		glGenBuffers(1, &elemArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemArray);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uchar)*indexCount, &indexes[0], GL_STATIC_DRAW);
		//Leave bound for instant draw calls
		glBindVertexArray(0);
		// For the moment, delete ASAP and let the VAO manage lifetime.
		// If problematic, move to GlMesh? Maybe rename to GlObject?
		glDeleteBuffers(1, &elemArray);
	}

	return new GlMesh(meshObject, indexCount);

}
}