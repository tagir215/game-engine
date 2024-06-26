#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <vector>

class StaticMesh {
public:
	StaticMesh() {};
	StaticMesh(std::vector<float> vertices, std::vector<float> texCoords) : vertices(vertices), texCoords(texCoords) {};


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
	void setVertices(std::vector<float>vertices) {
		this->vertices = vertices;
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
