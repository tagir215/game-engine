#include "engine/systems/gravitysystem.h"

void GravitySystem::onUpdate(float deltaTime){
	for (GameObject* object : gameObjects) {
		if (!object->getPhysicsComponent().gravity) {
			continue;
		}
		float newVelocity = GRAVITY_CONSTANT_THING * deltaTime + object->getVelocityComponent().linearVelocity.y;
		float newerVelocity = newVelocity - object->getVelocityComponent().linearVelocity.y;
		object->getVelocityComponent().linearVelocity.y += newerVelocity;
	}
}
