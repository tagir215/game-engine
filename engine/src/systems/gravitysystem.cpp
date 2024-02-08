#include "../include/engine/gravitysystem.h"

void GravitySystem::onUpdate(float deltaTime){
	for (GameObject* object : gameObjects) {
		if (!object->getPhysics().gravity) {
			continue;
		}
		float newVelocity = GRAVITY_CONSTANT_THING * deltaTime + object->getVelocity().y;
		float newerVelocity = newVelocity - object->getVelocity().y;
		object->getVelocity().y += newerVelocity;
	}
}
