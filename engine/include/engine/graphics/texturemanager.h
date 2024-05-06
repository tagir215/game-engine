#pragma once
#include "texture.h"
#include <string>

class TextureManager {
public:
	TextureManager();
	TextureComponent* loadTexture(const std::string& filename);
	TextureComponent* loadTextureFromPath(const std::string& path);

private:
	const std::string ROOT_DIR = "../../../engine/assets/textures/";
};
