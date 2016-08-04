#include "stdafx.h"
#include "Mesh.h"
namespace zro {

GlMesh::GlMesh(GLuint VAO, GLsizei indexCount) :
	VAO(VAO),
	indexCount(indexCount) {}

GlMesh::~GlMesh()
{
	glDeleteVertexArrays(1, &VAO);
}

void GlMesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}

}