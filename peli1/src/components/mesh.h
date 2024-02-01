#pragma once
#include <glad/gl.h>
#include <array>

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

	void updateTextureBuffer(std::array<float, 12>coords);

private:
	GLuint vao;
	GLuint positionsVbo;
	GLuint textureVbo;
	float color[4];
};