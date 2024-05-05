#pragma once
#include "keyframes.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Texture {
public:
	Texture(int width, int height, int nrChannels, const GLubyte* data);
	~Texture();

	GLuint getTextureId() const;

	void setKeyframes(Keyframes* keyframes) {
		this->keyframes = keyframes;
	}
	void nextFrame();
	std::vector<float>getTextureCoords();

private:
	GLuint texId;  
	Keyframes* keyframes;
	int currentFrame = 0;
};
