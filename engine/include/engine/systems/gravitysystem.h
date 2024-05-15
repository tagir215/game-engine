#pragma once
#include "engine/systems/systembase.h"

class GravitySystem : public SystemBase {
public:
	GravitySystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects) {};
	void onUpdate(float deltaTime) override;
private:
	float GRAVITY_CONSTANT_THING = -9.81f * 10;
};