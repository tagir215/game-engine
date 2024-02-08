#pragma once
#include "texture.h"
#include <string>

class TextureManager {
public:
	TextureManager();
	Texture* loadTexture(const std::string& filename);

private:
	const std::string ROOT_DIR = "../assets/textures/";
};
