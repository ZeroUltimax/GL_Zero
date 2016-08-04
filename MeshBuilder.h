#pragma once
#include "stdafx.h"

namespace zro {

	class IMesh;

	struct ixFace {
		uint i1, i2, i3;
	};

	class MeshBuilder
	{

		vector<vec3> vertices;
		vector<ixFace> faces;

	public:
		// Add a vertex to the mesh
		virtual void AddVertex(vec3);

		// Add a face connecting 3 vertexes
		virtual void AddFace(ixFace);
		
		// Compiles and returns a mesh
		virtual IMesh* FinalizeMesh();

	};
}

