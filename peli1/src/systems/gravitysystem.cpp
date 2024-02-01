#include "gravitysystem.h"

void GravitySystem::onUpdate(float deltaTime){
	for (GameObject* object : gameObjects) {
		float newVelocity = GRAVITY_CONSTANT_THING * deltaTime + object->getVelocity().y;
		object->getVelocity().y = newVelocity;
	}
}
