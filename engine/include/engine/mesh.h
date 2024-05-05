#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <vector>

class StaticMesh {
public:
	StaticMesh();


	GLuint getVao() {
		return vao;
	}

	void setColor(float r, float g, float b, float w);
	float* getColor() {
		return color;
	}

	std::vector<float> getVertices() {
		return vertices;
	}

	void updateTextureBuffer(std::vector<float> coords);
	
	void initVertexArrays();


protected:
	float color[4] = {1,1,1,1};
	GLuint vao;
	GLuint positionsVbo;
	GLuint textureVbo;
	std::vector<float> vertices;
	std::vector<float> texCoords;
};
