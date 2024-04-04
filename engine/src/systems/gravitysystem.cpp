#include "../include/engine/gravitysystem.h"

void GravitySystem::onUpdate(float deltaTime){
	for (GameObject* object : gameObjects) {
		if (!object->getPhysics().gravity) {
			continue;
		}
		float newVelocity = GRAVITY_CONSTANT_THING * deltaTime + object->getVelocity().velocity.y;
		float newerVelocity = newVelocity - object->getVelocity().velocity.y;
		object->getVelocity().velocity.y += newerVelocity;
	}
}
