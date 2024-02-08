#include "../include/engine/texturemanager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../ext/stb-master/stb_image.h"

TextureManager::TextureManager() {
	stbi_set_flip_vertically_on_load(true);
}

Texture* TextureManager::loadTexture(const std::string& filename){
	int x, y, n;
	std::string path = ROOT_DIR + filename;
	unsigned char* data = stbi_load(path.c_str(), &x, &y, &n, 0);
	Texture* texture = new Texture(x, y, n, data);
	return texture;
}

