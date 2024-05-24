#pragma once
#include <engine/systems/systembase.h>
#include "engine/core/scene.h"
#include "engine/graphics/texture.h"
#include "engine/graphics/texturemanager.h"

class KongSystem : public SystemBase {
public:
	KongSystem(std::vector<GameObject*>& gameObjects, Scene* scene) : SystemBase(gameObjects) {
		this->scene = scene;
		TextureManager textureManager;
		texture = textureManager.loadTextureFromPath("../../../../examples/kamkikong/assets/tt1.jpg");
	};
	~KongSystem() {
		delete texture;
	}
	void onUpdate(float deltaTime) override;
private:
	float cumilatedTime = 0;
	Scene* scene;
	TextureComponent* texture;
	float w = 0.077f;
	float x = 0.462f;
	float y = 1.0f - w;
	std::vector<float> texCoords = {
		x,   y,
		x+w, y,
		x+w, y-w,
		x,   y,
		x+w, y-w,
		x,   y-w
	};

};
