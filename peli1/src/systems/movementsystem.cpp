#include "movementsystem.h"


void MovementSystem::onUpdate(float deltaTime) {
	for (GameObject* object : gameObjects) {
		if (!object->getVelocity().active) {
			continue;
		}
		Transform oldT = object->getTransform();
		transformer.translate(
			object->getTransform(), 
			object->getVelocity().x*deltaTime, 
			object->getVelocity().y*deltaTime, 
			object->getVelocity().z*deltaTime
		);
	}
}