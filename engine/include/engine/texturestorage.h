#pragma once
#include "engine/graphics/texturemanager.h"

class TextureStorage{
public:
	TextureComponent* WALK_BASIC;
	static TextureStorage& getInstance() {
		static TextureStorage instance; 
		return instance;
	}
private:
	TextureStorage()  {
	//	WALK_BASIC = factory.getWalkTexture();
	}
	~TextureStorage() {
	//	delete WALK_BASIC;
	}
};