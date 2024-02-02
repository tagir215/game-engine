#pragma once
#include "systembase.h"

class CollisionSystem : public SystemBase {
public:
	CollisionSystem(std::vector<GameObject*>gameObjects);
	void onUpdate(float deltaTime) override;
private:
};