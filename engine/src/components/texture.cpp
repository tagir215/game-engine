#include "engine/graphics/texture.h"

TextureComponent::TextureComponent(int width, int height, int nrChannels, const GLubyte* data) {

	glGenTextures(1, &texId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLenum internalFormat;
	if (nrChannels == 3) {
		internalFormat = GL_RGB;
	}
	else if (nrChannels == 4) {
		internalFormat = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


}

TextureComponent::~TextureComponent() {
	glDeleteTextures(1, &texId);
}

GLuint TextureComponent::getTextureId() const {
	return texId;
}

void TextureComponent::nextFrame(){
	++currentFrame;
	if (currentFrame >= keyframes->frames.size()) {
		currentFrame = 0;
	}
}

std::vector<float> TextureComponent::getTextureCoords(){
	return keyframes->frames[currentFrame];
}


