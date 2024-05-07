#pragma once
#include "engine/systems/systembase.h"

class CharacterSystem : public SystemBase {
public:
	CharacterSystem(std::vector<GameObject*>& gameObjects);
	void onUpdate(float deltaTime) override;
private:
	const float MOVEMENT_SPEED = 300.0f;
};