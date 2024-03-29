#pragma once
#include "systembase.h"
#include "../util/transformer.h"

class MovementSystem : public SystemBase {
public:
	MovementSystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects){};
	void onUpdate(float deltaTime) override;
private:
	Transformer transformer;
};