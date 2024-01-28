#pragma once
#include "texture.h"
#include "texturefactory.h"

struct TextureStorage{
	Texture* WALK_BASIC;
	TextureFactory factory;

	TextureStorage()  {
		WALK_BASIC = factory.getWalkTexture();
	}
	~TextureStorage() {
		delete WALK_BASIC;
	}
};