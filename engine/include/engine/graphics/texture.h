#pragma once
#include "keyframes.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class TextureComponent {
public:
	TextureComponent(int width, int height, int nrChannels, const GLubyte* data);
	~TextureComponent();

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
