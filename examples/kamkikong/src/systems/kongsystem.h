#pragma once
#include <engine/systems/systembase.h>
#include "engine/core/scene.h"

class KongSystem : public SystemBase {
public:
	KongSystem(std::vector<GameObject*>& gameObjects, Scene* scene) : SystemBase(gameObjects) {
		this->scene = scene;
	};
	void onUpdate(float deltaTime) override;
private:
	float cumilatedTime = 0;
	Scene* scene;
};
