#pragma once
#include <glad/gl.h>
#include <array>
#include <glm/glm.hpp> 
#include <vector>

class Mesh {
public:
	Mesh();

	void setColor(float r, float g, float b, float w);

	GLuint getVao() {
		return vao;
	}

	float* getColor() {
		return color;
	}

	std::array<float, 18>getVertices() {
		return vertices;
	}

	void updateTextureBuffer(std::array<float, 12>coords);
	

private:
	float color[4];
	GLuint vao;
	GLuint positionsVbo;
	GLuint textureVbo;
	std::array<float, 18>vertices;
	std::array<float, 12>texCoords;
};
