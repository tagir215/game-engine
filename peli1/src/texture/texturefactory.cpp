#include "texturefactory.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureFactory::TextureFactory() {
	stbi_set_flip_vertically_on_load(true);
}

Texture* TextureFactory::getWalkTexture(){
	int x, y, n;
	std::string path = ROOT_DIR + "walk-basic.png";
	unsigned char* data = stbi_load(path.c_str(), &x, &y, &n, 0);
	Texture* texture = new Texture(x, y, n, data);
	return texture;
}

