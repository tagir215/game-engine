#pragma once
#include <glad/gl.h>   
#include "keyframes.h"

class Texture {
public:
	Texture(int width, int height, int nrChannels, const GLubyte* data);
	~Texture();

	GLuint getTextureId() const;

	void setKeyframes(Keyframes* keyframes) {
		this->keyframes = keyframes;
	}
	void nextFrame();
	std::array<float, 12>getTextureCoords();

private:
	GLuint texId;  
	Keyframes* keyframes;
	int currentFrame = 0;
};
