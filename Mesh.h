#pragma once
#include "stdafx.h"
namespace zro{
class IMesh
{
public:
	virtual void Draw() = 0;
};

class GlMesh :public IMesh {
	GLuint VAO;
	GLsizei indexCount;

public:

	GlMesh(GLuint VAO, GLsizei indexCount);
	
	~GlMesh();

	virtual void Draw();
};
}