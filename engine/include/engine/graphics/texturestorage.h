#pragma once
#include "texture.h"
#include "texturefactory.h"

class TextureStorage{
public:
	TextureComponent* WALK_BASIC;
	static TextureStorage& getInstance() {
		static TextureStorage instance; 
		return instance;
	}
private:
	TextureFactory factory;
	TextureStorage()  {
		WALK_BASIC = factory.getWalkTexture();
	}
	~TextureStorage() {
		delete WALK_BASIC;
	}
};