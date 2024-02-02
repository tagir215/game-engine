#pragma once
#include "texture.h"
#include <string>

class TextureFactory {
public:
	TextureFactory();
	Texture* getWalkTexture();

private:
	const std::string ROOT_DIR = "../../../../../peli1/assets/textures/";
};
