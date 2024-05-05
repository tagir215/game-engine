#pragma once
#include "engine/mesh.h"

class Plane : public StaticMesh {
public:		
	Plane() {
		vertices = {
			-0.5f, -0.5f, 0.0f,    //left-bottom
			 0.5f, -0.5f, 0.0f,     //right-bottom
			 0.5f,  0.5f, 0.0f,     //right-top
			-0.5f, -0.5f, 0.0f,    //left-bottom
			 0.5f,  0.5f, 0.0f,     //right-top
			-0.5f,  0.5f, 0.0f      //left-top
		};

		texCoords = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};
		initVertexArrays();
	}
private:

};
